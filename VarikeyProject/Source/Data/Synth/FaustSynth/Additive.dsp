import("stdfaust.lib");

freq = nentry("freq",500,200,1000,0.01) : max(20);
gain = vslider("gain",0.5,0,1,0.001) : si.smoo;
gate = button("gate");
globalGain = 1.0;

// first = vslider("first", 1, 0, 1, 0.01) : si.smoo;
// second = vslider("second", 0, 0, 1, 0.01) : si.smoo;
// third = vslider("third", 0, 0, 1, 0.01) : si.smoo;
// fourth = vslider("fourth", 0, 0, 1, 0.01) : si.smoo;
// fifth = vslider("fifth", 0, 0, 1, 0.01) : si.smoo;
// sixth = vslider("sixth", 0, 0, 1, 0.01) : si.smoo;
// seventh = vslider("seventh", 0, 0, 1, 0.01) : si.smoo;
// eighth = vslider("eigth", 0, 0, 1, 0.01) : si.smoo;

first = vslider("first", 8, 0, 8, 1) / 8 : si.smoo;
second = vslider("second", 0, 0, 8, 1) / 8 : si.smoo;
third = vslider("third", 0, 0, 8, 1) / 8 : si.smoo;
fourth = vslider("fourth", 0, 0, 8, 1) / 8 : si.smoo;
fifth = vslider("fifth", 0, 0, 8, 1) / 8 : si.smoo;
sixth = vslider("sixth", 0, 0, 8, 1) / 8 : si.smoo;
seventh = vslider("seventh", 0, 0, 8, 1) / 8 : si.smoo;
eighth = vslider("eigth", 0, 0, 8, 1) / 8 : si.smoo;

additiveSliders = hgroup("Harmonics", first, second, third, fourth, fifth, sixth, seventh, eighth);

synth(frequency) = additiveSliders : par(i, 8, _ * os.osc(frequency * (i + 1))) :> _ * 0.4 / normalizeLevel
with {
    normalizeLevel = additiveSliders :> _ + 1;
};

process = synth(freq) * gate * globalGain <: _,_;