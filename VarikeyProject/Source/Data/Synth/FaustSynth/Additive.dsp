import("stdfaust.lib");

freq = nentry("freq",500,200,1000,0.01) : max(20);
gain = vslider("gain",0.5,0,1,0.001) : si.smoo;
gate = button("gate");
globalGain = 1.0;
sliderDbRange = 60;

first = vslider("first", 8, 0, 8, 1) : si.smoo;
firstDb = ((first / 8) - 1) * sliderDbRange;
firstLin = ba.db2linear(firstDb);

second = vslider("second", 0, 0, 8, 1) : si.smoo;
secondDb = ((second / 8 ) - 1) * sliderDbRange;
secondLin = ba.db2linear(secondDb);

third = vslider("third", 0, 0, 8, 1) : si.smoo;
thirdDb = ((third / 8 ) - 1) * sliderDbRange;
thirdLin = ba.db2linear(thirdDb);

fourth = vslider("fourth", 0, 0, 8, 1) : si.smoo;
fourthDb = ((fourth / 8 ) - 1) * sliderDbRange;
fourthLin = ba.db2linear(fourthDb);

fifth = vslider("fifth", 0, 0, 8, 1) : si.smoo;
fifthDb = ((fifth / 8 ) - 1) * sliderDbRange;
fifthLin = ba.db2linear(fifthDb);

sixth = vslider("sixth", 0, 0, 8, 1) : si.smoo;
sixthDb = ((sixth / 8 ) - 1) * sliderDbRange;
sixthLin = ba.db2linear(sixthDb);

seventh = vslider("seventh", 0, 0, 8, 1) : si.smoo;
seventhDb = ((seventh / 8 ) - 1) * sliderDbRange;
seventhLin = ba.db2linear(seventhDb);

eighth = vslider("eigth", 0, 0, 8, 1) : si.smoo;
eighthDb = ((eighth / 8 ) - 1) * sliderDbRange;
eighthLin = ba.db2linear(eighthDb);


additiveSliders = hgroup("Harmonics", firstLin, secondLin, thirdLin, fourthLin, fifthLin, sixthLin, seventhLin, eighthLin);

synth(frequency) = additiveSliders : par(i, 8, _ * os.osc(frequency * (i + 1))) :> _ * 0.4 / normalizeLevel
with {
    normalizeLevel = additiveSliders :> _ + 1;
};

process = synth(freq) * gate * globalGain <: _,_;