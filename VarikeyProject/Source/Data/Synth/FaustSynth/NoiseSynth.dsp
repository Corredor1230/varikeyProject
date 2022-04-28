import("stdfaust.lib");

freq = vslider("freq", 220, 20, 20000, 1);
gate = button("gate");
gain = vslider("gain", 1, 0, 1, 0.01);
globalGain = 1.0;

noise = no.pink_noise : fi.highpass(4, 20);

tone = vslider("tone", 0.5, 0.0, 1.0, 0.01) : si.smoo;
dbTone = (tone - 1) * 60;
/*These calculations are done to normalize
the level with increase or decrease of tone slider*/
invTone = (dbTone + 60) * (-1);
linearTone = ba.db2linear(dbTone);
linearInvTone = ba.db2linear(invTone);

noiseShape = hslider("shape", 0, 0, 1, 1);

synth(frequency) = (noise : fi.resonbp(frequency, synthTone, 1) : fi.resonbp(frequency, synthTone, 1) : fi.resonbp(frequency, synthTone, 1)) * linearInvTone * normalization * 60
with{
    reduction = 0.9;
    absToneDiff =(dbTone + 30) : abs;
    toneNorm = (-absToneDiff) * 0.75;
    normalization = 1 * ba.db2linear(toneNorm);
    synthTone = (linearTone * 20) + 1;
};

process = synth(freq) * gate * globalGain <: _,_;