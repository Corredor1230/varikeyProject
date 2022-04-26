/* ------------------------------------------------------------
name: "Filter"
Code generated with Faust 2.37.3 (https://faust.grame.fr)
Compilation options: -lang cpp -es 1 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __Filter_H__
#define  __Filter_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

static float Filter_faustpower2_f(float value) {
	return (value * value);
}

#ifndef FAUSTCLASS 
#define FAUSTCLASS Filter
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class Filter : public dsp {
	
 private:
	
	FAUSTFLOAT fVslider0;
	int fSampleRate;
	float fConst2;
	float fConst3;
	float fConst5;
	float fConst7;
	FAUSTFLOAT fVslider1;
	float fVec0[2];
	float fConst8;
	float fConst9;
	float fRec3[2];
	float fConst10;
	float fConst11;
	float fRec2[3];
	float fConst12;
	float fConst13;
	FAUSTFLOAT fVslider2;
	float fConst14;
	float fRec4[2];
	float fConst15;
	FAUSTFLOAT fVslider3;
	float fRec5[2];
	float fRec1[3];
	float fVec1[2];
	float fRec0[2];
	float fVec2[2];
	float fRec9[2];
	float fRec8[3];
	float fRec7[3];
	float fVec3[2];
	float fRec6[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-lang cpp -es 1 -single -ftz 0");
		m->declare("filename", "Filter.dsp");
		m->declare("filters.lib/dcblocker:author", "Julius O. Smith III");
		m->declare("filters.lib/dcblocker:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/dcblocker:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/highpass:author", "Julius O. Smith III");
		m->declare("filters.lib/highpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass0_highpass1:author", "Julius O. Smith III");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/pole:author", "Julius O. Smith III");
		m->declare("filters.lib/pole:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/pole:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/resonlp:author", "Julius O. Smith III");
		m->declare("filters.lib/resonlp:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/resonlp:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf1:author", "Julius O. Smith III");
		m->declare("filters.lib/tf1:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf1:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf1s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf1s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf1s:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2s:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "0.3");
		m->declare("filters.lib/zero:author", "Julius O. Smith III");
		m->declare("filters.lib/zero:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/zero:license", "MIT-style STK-4.3 license");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.3");
		m->declare("misceffects.lib/name", "Misc Effects Library");
		m->declare("misceffects.lib/version", "2.0");
		m->declare("name", "Filter");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "0.1");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
	}

	virtual int getNumInputs() {
		return 2;
	}
	virtual int getNumOutputs() {
		return 2;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		float fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate)));
		float fConst1 = std::tan((62.831852f / fConst0));
		fConst2 = (1.0f / fConst1);
		fConst3 = (1.0f / (((fConst2 + 1.0f) / fConst1) + 1.0f));
		float fConst4 = Filter_faustpower2_f(fConst1);
		fConst5 = (1.0f / fConst4);
		float fConst6 = (fConst2 + 1.0f);
		fConst7 = (0.0f - (1.0f / (fConst1 * fConst6)));
		fConst8 = (1.0f / fConst6);
		fConst9 = (1.0f - fConst2);
		fConst10 = (((fConst2 + -1.0f) / fConst1) + 1.0f);
		fConst11 = (2.0f * (1.0f - fConst5));
		fConst12 = (0.0f - (2.0f / fConst4));
		fConst13 = (44.0999985f / fConst0);
		fConst14 = (1.0f - fConst13);
		fConst15 = (3.14159274f / fConst0);
	}
	
	virtual void instanceResetUserInterface() {
		fVslider0 = FAUSTFLOAT(0.22f);
		fVslider1 = FAUSTFLOAT(0.10000000000000001f);
		fVslider2 = FAUSTFLOAT(1.0f);
		fVslider3 = FAUSTFLOAT(1000.0f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fVec0[l0] = 0.0f;
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec3[l1] = 0.0f;
		}
		for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) {
			fRec2[l2] = 0.0f;
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec4[l3] = 0.0f;
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec5[l4] = 0.0f;
		}
		for (int l5 = 0; (l5 < 3); l5 = (l5 + 1)) {
			fRec1[l5] = 0.0f;
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fVec1[l6] = 0.0f;
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec0[l7] = 0.0f;
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fVec2[l8] = 0.0f;
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec9[l9] = 0.0f;
		}
		for (int l10 = 0; (l10 < 3); l10 = (l10 + 1)) {
			fRec8[l10] = 0.0f;
		}
		for (int l11 = 0; (l11 < 3); l11 = (l11 + 1)) {
			fRec7[l11] = 0.0f;
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fVec3[l12] = 0.0f;
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec6[l13] = 0.0f;
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
	
	virtual Filter* clone() {
		return new Filter();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("Filter");
		ui_interface->declare(&fVslider3, "scale", "log");
		ui_interface->addVerticalSlider("cutoff", &fVslider3, FAUSTFLOAT(1000.0f), FAUSTFLOAT(20.0f), FAUSTFLOAT(20000.0f), FAUSTFLOAT(1.0f));
		ui_interface->addVerticalSlider("distGain", &fVslider1, FAUSTFLOAT(0.100000001f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00999999978f));
		ui_interface->addVerticalSlider("distOut", &fVslider0, FAUSTFLOAT(0.219999999f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00999999978f));
		ui_interface->addVerticalSlider("q", &fVslider2, FAUSTFLOAT(1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(10.0f), FAUSTFLOAT(0.100000001f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = float(fVslider0);
		float fSlow1 = std::pow(10.0f, (2.0f * float(fVslider1)));
		float fSlow2 = (fConst13 * float(fVslider2));
		float fSlow3 = (fConst13 * float(fVslider3));
		for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
			float fTemp0 = std::max<float>(-1.0f, std::min<float>(1.0f, ((fSlow1 * float(input0[i0])) + -0.25f)));
			float fTemp1 = (fTemp0 * (1.0f - (0.333333343f * Filter_faustpower2_f(fTemp0))));
			fVec0[0] = fTemp1;
			fRec3[0] = ((fConst7 * fVec0[1]) - (fConst8 * ((fConst9 * fRec3[1]) - (fConst2 * fTemp1))));
			fRec2[0] = (fRec3[0] - (fConst3 * ((fConst10 * fRec2[2]) + (fConst11 * fRec2[1]))));
			fRec4[0] = (fSlow2 + (fConst14 * fRec4[1]));
			float fTemp2 = (1.0f / fRec4[0]);
			fRec5[0] = (fSlow3 + (fConst14 * fRec5[1]));
			float fTemp3 = std::tan((fConst15 * std::max<float>(20.0f, fRec5[0])));
			float fTemp4 = (1.0f / fTemp3);
			float fTemp5 = (1.0f - ((fTemp2 - fTemp4) / fTemp3));
			float fTemp6 = (1.0f - (1.0f / Filter_faustpower2_f(fTemp3)));
			float fTemp7 = (((fTemp2 + fTemp4) / fTemp3) + 1.0f);
			fRec1[0] = ((fConst3 * (((fConst5 * fRec2[0]) + (fConst12 * fRec2[1])) + (fConst5 * fRec2[2]))) - (((fRec1[2] * fTemp5) + (2.0f * (fRec1[1] * fTemp6))) / fTemp7));
			float fTemp8 = (fTemp7 * std::max<float>(1.0f, (0.200000003f * fRec4[0])));
			float fTemp9 = ((fRec1[2] + (fRec1[0] + (2.0f * fRec1[1]))) / fTemp8);
			fVec1[0] = fTemp9;
			fRec0[0] = (((0.995000005f * fRec0[1]) + fTemp9) - fVec1[1]);
			output0[i0] = FAUSTFLOAT((fSlow0 * fRec0[0]));
			float fTemp10 = std::max<float>(-1.0f, std::min<float>(1.0f, ((fSlow1 * float(input1[i0])) + -0.25f)));
			float fTemp11 = (fTemp10 * (1.0f - (0.333333343f * Filter_faustpower2_f(fTemp10))));
			fVec2[0] = fTemp11;
			fRec9[0] = ((fConst7 * fVec2[1]) - (fConst8 * ((fConst9 * fRec9[1]) - (fConst2 * fTemp11))));
			fRec8[0] = (fRec9[0] - (fConst3 * ((fConst10 * fRec8[2]) + (fConst11 * fRec8[1]))));
			fRec7[0] = ((fConst3 * (((fConst12 * fRec8[1]) + (fConst5 * fRec8[0])) + (fConst5 * fRec8[2]))) - (((fTemp5 * fRec7[2]) + (2.0f * (fTemp6 * fRec7[1]))) / fTemp7));
			float fTemp12 = ((fRec7[2] + (fRec7[0] + (2.0f * fRec7[1]))) / fTemp8);
			fVec3[0] = fTemp12;
			fRec6[0] = (((0.995000005f * fRec6[1]) + fTemp12) - fVec3[1]);
			output1[i0] = FAUSTFLOAT((fSlow0 * fRec6[0]));
			fVec0[1] = fVec0[0];
			fRec3[1] = fRec3[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fVec1[1] = fVec1[0];
			fRec0[1] = fRec0[0];
			fVec2[1] = fVec2[0];
			fRec9[1] = fRec9[0];
			fRec8[2] = fRec8[1];
			fRec8[1] = fRec8[0];
			fRec7[2] = fRec7[1];
			fRec7[1] = fRec7[0];
			fVec3[1] = fVec3[0];
			fRec6[1] = fRec6[0];
		}
	}

};

#endif
