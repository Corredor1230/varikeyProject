import("stdfaust.lib");

freq = vslider("freq", 220, 20, 20000, 1);
gate = button("gate");
gain = vslider("gain", 1, 0, 1, 0.01);
globalGain = 1.0;

noise = no.pink_noise : fi.highpass(4, 20);

tone = vslider("tone", -30, -60, 0, 0.1) : si.smoo;
/*These calculations are done to normalize
the level with increase or decrease of tone slider*/
invTone = (tone + 60) * (-1);
linearTone = ba.db2linear(tone);
linearInvTone = ba.db2linear(invTone);

noiseShape = hslider("shape", 0, 0, 1, 1);

synth(frequency) = (noise : fi.resonbp(frequency, synthTone, 1) : fi.resonbp(frequency, synthTone, 1) : fi.resonbp(frequency, synthTone, 1)) * linearInvTone * normalization * 60
with{
    reduction = 0.9;
    absToneDiff =(tone + 30) : abs;
    toneNorm = (-absToneDiff) * 0.75;
    normalization = 1 * ba.db2linear(toneNorm);
    synthTone = (linearTone * 20) + 1;
};

process = synth(freq) * gate * globalGain <: _,_;