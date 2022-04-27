import ("stdfaust.lib");

freq = vslider("freq[scale:log]", 100, 20, 20000, 1);
gate = button("gate");
lopOnOff = checkbox("lopOnOff");
hipOnOff = checkbox("hipOnOff");
allSwitchesOff = 1 * (lopOnOff == 0) * (hipOnOff == 0);
allSwitchesOn = 1 * (lopOnOff == 1) * (hipOnOff == 1);

lopCutoff = vslider("lopCutoff[scale:log]", 20000, 20, 20000, 1):si.smoo:max(20);
hipCutoff = vslider("hipCutoff[scale:log]", 20, 20, 20000, 1):si.smoo:max(20);
lopQ = vslider("lopQ", 1, 1, 10, 0.1):si.smoo;
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
distOut = vslider("distOut", 0.1, 0, 1, 0.01);

distoffset = vslider("offset", 0.1, -1.0, 1.0, 0.01);

gainCompensation = 17;

filtDist = _ 
: ef.cubicnl(distGain, distoffset) 
: _ * distOut;

filtComp = _ 
: co.compressor_mono(3, -16, 0.001, 0.007)
: _ * gainCompensation;
//: _ * gainCompensation
//: co.compressor_mono(2, -10, 0.001, 0.007);

lopChain = _ 
: fi.resonlp(lopCutoff, lopQ, normalLevel)
: _ * lopQInvLinear
with{
    absQRef = (lopQDb + 30) : abs;
    qNorm = (-absQRef) * 0.35;
    normalLevel = 1 * ba.db2linear(qNorm);
};

hipChain = _ 
: fi.resonhp(hipCutoff, hipQ, normalLevel)
: _ * hipQInvLinear
with{
    absQRef = (hipQDb + 30) : abs;
    qNorm = (-absQRef) * 0.35;
    normalLevel = 1 * ba.db2linear(qNorm);
};



process = _,_<: 
(_ * allSwitchesOff, _ * allSwitchesOff,
_ * lopOnOff * (allSwitchesOn == 0), _ * lopOnOff * (allSwitchesOn == 0),
_ * hipOnOff * (allSwitchesOn == 0), _ * hipOnOff * (allSwitchesOn == 0),
_ * allSwitchesOn, _ * allSwitchesOn) 
: (_ * 1, _ * 1,
(filtDist:lopChain:filtComp), (filtDist:lopChain:filtComp),
(filtDist:hipChain:filtComp), (filtDist:hipChain:filtComp),
(filtDist:lopChain:hipChain:filtComp * 2.3), (filtDist:lopChain:hipChain:filtComp * 2.3) 
)
:> _,_
;