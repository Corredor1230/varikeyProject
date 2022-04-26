import ("stdfaust.lib");

cutoff = vslider("cutoff[scale:log]", 1000, 20, 20000, 1):si.smoo:max(20);
q = vslider("q", 1, 1, 10, 0.1):si.smoo;
distGain = vslider("distGain", 0.1, 0, 1, 0.01);
distOut = vslider("distOut", 0.22, 0, 1, 0.01);

filterChain = _ 
: ef.cubicnl(distGain, -0.25) 
: fi.highpass(3, 20) 
: fi.resonlp(cutoff, q, 1 / ((q / 5) : max(1))) 
: fi.dcblocker * distOut;

process = _ , _: par(i,2, _ : filterChain);