import("stdfaust.lib");

freq = nentry("freq",500,200,1000,0.01) : max(20);
gain = vslider("gain",0.5,0,1,0.001) : si.smoo;
gate = button("gate");
vol = vslider("volume", -20, -60, 0, 1) : si.smoo : ba.db2linear;
att = 10;
fmDepth = vslider("fmDepth[scale:log]",500,100,8000,1):si.smoo:max(100);
fmIndex = vslider("fmIndex",2,1,8,1);


kAtt = vslider("kAtt[scale:log]", 1, 1, 48000, 1);
kFeed = (vslider("kFeed", 0.5, 0, 1, 0.001) / 5) + 0.799;
kRel = vslider("kRel[scale:log]", 10, 1, 48000, 1);
kSwitch = hslider("kSwitch[style:knob]", 1, 1, 3, 1);

envelope(att, dec, sus, rel, gate) = _ * en.adsr(attack, decay, sustain, release, gate) with{
    attack = att : _ / ma.SR : max (0.001);
    decay = dec : _ / ma.SR : max (0.001);
    sustain = sus : max (0) : min (1);
    release = rel : _ / ma.SR : max (0);
};

karplus(thisFreq) = karplusSource : + ~ de.fdelay(ma.SR, del) * kFeed with{
    fixedClose = envelope(kAtt, kRel, 0, 0, gate);

    noiseGen = ((no.noise : fi.highpass(6, 20)): fixedClose) * correction / 2.5 with {
        correction = ((kAtt - 1)*(-2)):max(1);
    };
    fmGen = os.osc(fmFreq) : fixedClose * correction / 32 with {
        fmFreq = thisFreq+os.osc(thisFreq*fmIndex)*fmDepth:min(18000);
        correction = ((kAtt - 1)*(-4)):max(1); 
    };
    pinkGen = ((no.pink_noise : fi.highpass(6, 20)): fixedClose) * 2.25 * correction with{
        correction = ((kAtt - 1)*(-2)):max(1);
    };

    karplusSource = 
        noiseGen * (kSwitch == 1) + 
        fmGen * (kSwitch == 2) + 
        pinkGen * (kSwitch == 3);

    del = (ma.SR) / thisFreq; 
};



masterGain(gain) = _ , _: par(i,2, _*gain/13);

process = 
		karplus(freq) <:
		_ / 2,_ / 2;