import("stdfaust.lib");

freq = vslider("freq", 220, 20, 20000, 1);
gate = button("gate");
gain = vslider("gain", 1, 0, 1, 0.01);
globalGain = 1.0;
waveShape = hslider("shape", 0, 0, 3, 1);
noiseLevel = vslider("noiseLevel", 0, 0, 1, 0.001):si.smoo;
noiseShape = hslider("noiseShape", 0, 0, 1, 1);
noiseDb = (noiseLevel - 1) * 40;
noiseLog = ba.db2linear(noiseDb);

//saw, square, sine, triangle :¨selector(4, waveShape) :¨

synth(frequency) = (saw + square + sine + triangle) / 8.5
with{
    saw = os.sawtooth(frequency) * (waveShape == 0);
    square = os.square(frequency) * (waveShape == 1) * 0.75;
    sine = os.osc(frequency) * (waveShape == 2) * 1.25;
    triangle = os.triangle(frequency) * (waveShape == 3) * 1.25;
};

noise = (((no.noise * (noiseShape == 0) * 0.1) + (no.pink_noise * (noiseShape == 1) * 2)) * noiseLog * 0.75) : fi.highpass(6, 40);

process = (synth(freq) + noise) * gate *globalGain <: _,_;