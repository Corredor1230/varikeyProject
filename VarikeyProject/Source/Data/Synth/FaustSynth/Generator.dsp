import("stdfaust.lib");

freq = vslider("freq", 220, 20, 20000, 1);
gate = button("gate");
gain = vslider("gain", 1, 0, 1, 0.01);
globalGain = 1.0;
waveShape = hslider("shape", 0, 0, 3, 1);

synth(frequency) = (saw + square + sine + triangle) / 8.5
with{
    saw = os.sawtooth(frequency) * (waveShape == 0);
    square = os.square(frequency) * (waveShape == 1) * 0.75;
    sine = os.osc(frequency) * (waveShape == 2) * 1.25;
    triangle = os.triangle(frequency) * (waveShape == 3) * 1.25;
};

process = synth(freq) * gate *globalGain <: _,_;