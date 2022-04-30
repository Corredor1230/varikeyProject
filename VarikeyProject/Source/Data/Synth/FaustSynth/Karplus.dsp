import("stdfaust.lib");

freq = nentry("freq",500,200,1000,0.01) : max(20);
gain = vslider("gain",0.5,0,1,0.001) : si.smoo;
gate = button("gate");
globalGain = 1.0;

kAtt = vslider("kAtt", 0.001, 0.0001, 1, 0.0001);
kFeed = vslider("kFeed", 0.5, 0, 1, 0.001);
kRel = vslider("kRel", 0.001, 0.0001, 1, 0.0001);
kSwitch = hslider("kSwitch[style:knob]", 0, 0, 1, 1);

/*These calculations are done to create
an inverted logarithmic relationship
for the feedback slider, since most
noticeable change occurs within the
very last portion of the slider.*/
fbInv = (kFeed - 1) * (-1);
fbInvDb = (fbInv - 1) * 60;
kFeedInv = ba.db2linear(fbInvDb); 
kLinearFeed = (kFeedInv - 1) * (-1);

kRelInv = ((kRel - 1) * (-1)) - 1;
kRelDb = kRelInv * 5;
normalizeRel = ba.db2linear(kRelDb);
 


envelope(att, dec, sus, rel, gate) = _ * en.adsr(attack, decay, sustain, release, gate) with{
    attack = att : _ / ma.SR : max (0.001);
    decay = dec : _ / ma.SR : max (0.001);
    sustain = sus : max (0) : min (1);
    release = rel : _ / ma.SR : max (0);
};

synth(thisFreq) = (karplusSource : + ~ de.fdelay(ma.SR, del) * kLinearFeed) * normalizeRel / 2 with{
    fixedClose = envelope(kAtt*ma.SR, kRel*ma.SR, 0, 0, gate);

    noiseGen = ((no.noise : fi.highpass(6, 20)): fixedClose) * correction / 4 with {
        correction = (((kAtt*ma.SR) - 1)*(-2)):max(1);
    };

    pinkGen = ((no.pink_noise : fi.highpass(6, 20)): fixedClose) * 2.25 * correction with{
        correction = (((kAtt*ma.SR) - 1)*(-2)):max(1);
    };

    karplusSource = 
        noiseGen * (kSwitch == 0) + 
        pinkGen * (kSwitch == 1);

    /*These values change SR and freq calculations 
    for delay to prevent >1000sample bug from occuring*/
    isBelowThousandth = (ba.hz2midikey(freq) < 31) + 1;
    isBelowNineteen = (ba.hz2midikey(freq) < 19) + 1;
    del = (isBelowNineteen * isBelowThousandth * ma.SR) / 
    ((isBelowNineteen * isBelowThousandth * thisFreq) : max (20)); 
};


process = synth(freq) * globalGain <: _,_;