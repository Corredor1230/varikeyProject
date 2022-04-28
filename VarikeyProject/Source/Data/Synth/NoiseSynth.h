/* ------------------------------------------------------------
name: "NoiseSynth"
Code generated with Faust 2.37.3 (https://faust.grame.fr)
Compilation options: -lang cpp -es 1 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __NoiseSynth_H__
#define  __NoiseSynth_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

static float NoiseSynth_faustpower2_f(float value) {
	return (value * value);
}

#ifndef FAUSTCLASS 
#define FAUSTCLASS NoiseSynth
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class NoiseSynth : public dsp {
	
 private:
	
	FAUSTFLOAT fButton0;
	int fSampleRate;
	float fConst1;
	FAUSTFLOAT fVslider0;
	float fConst2;
	FAUSTFLOAT fVslider1;
	float fConst3;
	float fRec1[2];
	float fConst6;
	float fConst8;
	float fConst9;
	int iRec7[2];
	float fRec6[4];
	float fConst10;
	float fConst11;
	float fRec5[3];
	float fConst12;
	float fConst13;
	float fRec4[3];
	float fRec3[3];
	float fRec2[3];
	float fRec0[3];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.1");
		m->declare("compile_options", "-lang cpp -es 1 -single -ftz 0");
		m->declare("filename", "NoiseSynth.dsp");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/highpass:author", "Julius O. Smith III");
		m->declare("filters.lib/highpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1:author", "Julius O. Smith III");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/resonbp:author", "Julius O. Smith III");
		m->declare("filters.lib/resonbp:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/resonbp:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2s:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "0.3");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.3");
		m->declare("name", "NoiseSynth");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "0.1");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
	}

	virtual int getNumInputs() {
		return 0;
	}
	virtual int getNumOutputs() {
		return 2;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		float fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = (3.14159274f / fConst0);
		fConst2 = (44.0999985f / fConst0);
		fConst3 = (1.0f - fConst2);
		float fConst4 = std::tan((62.831852f / fConst0));
		float fConst5 = (1.0f / fConst4);
		fConst6 = (1.0f / (((fConst5 + 0.765366852f) / fConst4) + 1.0f));
		float fConst7 = NoiseSynth_faustpower2_f(fConst4);
		fConst8 = (1.0f / fConst7);
		fConst9 = (1.0f / (((fConst5 + 1.84775901f) / fConst4) + 1.0f));
		fConst10 = (((fConst5 + -1.84775901f) / fConst4) + 1.0f);
		fConst11 = (2.0f * (1.0f - fConst8));
		fConst12 = (0.0f - (2.0f / fConst7));
		fConst13 = (((fConst5 + -0.765366852f) / fConst4) + 1.0f);
	}
	
	virtual void instanceResetUserInterface() {
		fButton0 = FAUSTFLOAT(0.0f);
		fVslider0 = FAUSTFLOAT(220.0f);
		fVslider1 = FAUSTFLOAT(0.5f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec1[l0] = 0.0f;
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			iRec7[l1] = 0;
		}
		for (int l2 = 0; (l2 < 4); l2 = (l2 + 1)) {
			fRec6[l2] = 0.0f;
		}
		for (int l3 = 0; (l3 < 3); l3 = (l3 + 1)) {
			fRec5[l3] = 0.0f;
		}
		for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) {
			fRec4[l4] = 0.0f;
		}
		for (int l5 = 0; (l5 < 3); l5 = (l5 + 1)) {
			fRec3[l5] = 0.0f;
		}
		for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) {
			fRec2[l6] = 0.0f;
		}
		for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
			fRec0[l7] = 0.0f;
		}
	}
	
	virtual void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	virtual void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual NoiseSynth* clone() {
		return new NoiseSynth();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("NoiseSynth");
		ui_interface->addVerticalSlider("freq", &fVslider0, FAUSTFLOAT(220.0f), FAUSTFLOAT(20.0f), FAUSTFLOAT(20000.0f), FAUSTFLOAT(1.0f));
		ui_interface->addButton("gate", &fButton0);
		ui_interface->addVerticalSlider("tone", &fVslider1, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00999999978f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = (60.0f * float(fButton0));
		float fSlow1 = std::tan((fConst1 * float(fVslider0)));
		float fSlow2 = (1.0f / fSlow1);
		float fSlow3 = (fConst2 * float(fVslider1));
		float fSlow4 = (2.0f * (1.0f - (1.0f / NoiseSynth_faustpower2_f(fSlow1))));
		for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
			fRec1[0] = (fSlow3 + (fConst3 * fRec1[1]));
			float fTemp0 = (fRec1[0] + -1.0f);
			float fTemp1 = (1.0f / ((20.0f * std::pow(10.0f, (3.0f * fTemp0))) + 1.0f));
			float fTemp2 = ((fSlow2 * (fSlow2 + fTemp1)) + 1.0f);
			float fTemp3 = (0.0f - (fSlow2 / fTemp2));
			iRec7[0] = (((1103515245 * iRec7[1]) & 2147483647) + 12345);
			fRec6[0] = (((2.49495602f * fRec6[1]) + ((4.65661287e-10f * float(iRec7[0])) + (0.522189379f * fRec6[3]))) - (2.0172658f * fRec6[2]));
			fRec5[0] = (((0.0499220341f * fRec6[0]) + (0.0506126992f * fRec6[2])) - (((0.0959935337f * fRec6[1]) + (0.00440878607f * fRec6[3])) + (fConst9 * ((fConst10 * fRec5[2]) + (fConst11 * fRec5[1])))));
			fRec4[0] = ((fConst9 * (((fConst8 * fRec5[0]) + (fConst12 * fRec5[1])) + (fConst8 * fRec5[2]))) - (fConst6 * ((fConst13 * fRec4[2]) + (fConst11 * fRec4[1]))));
			float fTemp4 = ((fSlow2 * (fSlow2 - fTemp1)) + 1.0f);
			fRec3[0] = ((fConst6 * (((fConst8 * fRec4[0]) + (fConst12 * fRec4[1])) + (fConst8 * fRec4[2]))) - (((fRec3[2] * fTemp4) + (fSlow4 * fRec3[1])) / fTemp2));
			fRec2[0] = ((fRec3[2] * fTemp3) - ((((fTemp4 * fRec2[2]) + (fSlow4 * fRec2[1])) - (fSlow2 * fRec3[0])) / fTemp2));
			fRec0[0] = ((fTemp3 * fRec2[2]) - ((((fTemp4 * fRec0[2]) + (fSlow4 * fRec0[1])) - (fSlow2 * fRec2[0])) / fTemp2));
			float fTemp5 = (fSlow0 * ((((fSlow2 * (fRec0[0] / fTemp2)) + (fTemp3 * fRec0[2])) * std::pow(10.0f, (0.0500000007f * (0.0f - (60.0f * (fTemp0 + 1.0f)))))) * std::pow(10.0f, (0.0500000007f * (0.0f - (0.75f * std::fabs(((60.0f * fTemp0) + 30.0f))))))));
			output0[i0] = FAUSTFLOAT(fTemp5);
			output1[i0] = FAUSTFLOAT(fTemp5);
			fRec1[1] = fRec1[0];
			iRec7[1] = iRec7[0];
			for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				fRec6[j0] = fRec6[(j0 - 1)];
			}
			fRec5[2] = fRec5[1];
			fRec5[1] = fRec5[0];
			fRec4[2] = fRec4[1];
			fRec4[1] = fRec4[0];
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
		}
	}

};

#endif
