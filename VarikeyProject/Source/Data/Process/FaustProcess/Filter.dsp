import ("stdfaust.lib");

freq = vslider("freq[scale:log]", 100, 20, 20000, 1);
gate = button("gate");

lopCutoff = vslider("lopCutoff[scale:log]", 20000, 20, 20000, 1):si.smoo:max(20);
hipCutoff = vslider("hipCutoff[scale:log]", 20, 20, 20000, 1):si.smoo:max(20);
lopQ = vslider("q", 1, 1, 10, 0.1):si.smoo;
hipQ = vslider("hipQ", 1, 1, 10, 0.1):si.smoo;

size = 10;
qReduction = 0.3;

lopQLinear = (lopQ - 1) / 9; 
lopQDb = (lopQLinear - 1) * size;
loPQDbInv = (lopQDb * (-1)) - size;
lopQInvLinear = ((lopQLinear * qReduction) - 1) * (-1);

hipQLinear = (hipQ - 1) / 9;
hipQDb = (hipQLinear - 1) * size;
hipQDbInv = (hipQDb * (-1)) - size;
hipQInvLinear = ((hipQLinear * qReduction) - 1) * (-1);

distGain = vslider("distGain", 0.1, 0, 1, 0.01);

//0.1 or less recommended to avoid clipping
//even under the most extreme circumstances.
distOut = vslider("distOut", 0.22, 0, 1, 0.01);

distoffset = vslider("offset", 0.1, -1.0, 1.0, 0.01);

filterChain = _ 
: ef.cubicnl(distGain, distoffset) 
: _ * distOut
: fi.resonlp(lopCutoff, lopQ, normalLevel)
: _ * lopQInvLinear
with{
    absQRef = (lopQDb + 30) : abs;
    qNorm = (-absQRef) * 0.35;
    normalLevel = 1 * ba.db2linear(qNorm);
}
;

hiPChain = _ 
: ef.cubicnl(distGain, distoffset) 
: _ * distOut
: fi.resonhp(hipCutoff, hipQ, normalLevel)
: _ * hipQInvLinear
with{
    absQRef = (hipQDb + 30) : abs;
    qNorm = (-absQRef) * 0.35;
    normalLevel = 1 * ba.db2linear(qNorm);
}
;

process = _, _ <:

par(i, 2, filterChain
: _ * 2
: co.compressor_mono(3, -16, 0.001, 0.007)
), 
par(i, 2, hiPChain
: _ * 2
: co.compressor_mono(3, -16, 0.001, 0.007)
) 
:> par(i, 2, fi.lowpass(1, lopCutoff) : fi.highpass(1, hipCutoff))
: _ / 3.5, _ / 3.5
;