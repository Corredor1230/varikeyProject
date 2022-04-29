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

process = os.sawtooth(freq) * gate <:_,_;