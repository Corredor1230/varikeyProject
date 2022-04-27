/* ------------------------------------------------------------
name: "Karplus"
Code generated with Faust 2.37.3 (https://faust.grame.fr)
Compilation options: -lang cpp -es 1 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __Karplus_H__
#define  __Karplus_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

static float Karplus_faustpower2_f(float value) {
	return (value * value);
}

#ifndef FAUSTCLASS 
#define FAUSTCLASS Karplus
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class Karplus : public dsp {
	
 private:
	
	FAUSTFLOAT fButton0;
	float fVec0[2];
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT fVslider1;
	int fSampleRate;
	float fConst0;
	FAUSTFLOAT fEntry0;
	float fConst1;
	float fConst4;
	FAUSTFLOAT fVslider2;
	float fRec1[2];
	int iRec2[2];
	FAUSTFLOAT fHslider0;
	float fConst6;
	float fConst7;
	float fConst8;
	int iRec6[2];
	float fConst9;
	float fConst10;
	float fRec5[3];
	float fConst11;
	float fConst12;
	float fRec4[3];
	float fConst13;
	float fRec3[3];
	float fRec10[4];
	float fRec9[3];
	float fRec8[3];
	float fRec7[3];
	int IOTA;
	float fRec0[4096];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.1");
		m->declare("compile_options", "-lang cpp -es 1 -single -ftz 0");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.1");
		m->declare("envelopes.lib/adsr:author", "Yann Orlarey and Andrey Bundin");
		m->declare("envelopes.lib/author", "GRAME");
		m->declare("envelopes.lib/copyright", "GRAME");
		m->declare("envelopes.lib/license", "LGPL with exception");
		m->declare("envelopes.lib/name", "Faust Envelope Library");
		m->declare("envelopes.lib/version", "0.1");
		m->declare("filename", "Karplus.dsp");
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
		m->declare("name", "Karplus");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "0.1");
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
		fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = (fConst0 + 1.0f);
		float fConst2 = std::tan((62.831852f / fConst0));
		float fConst3 = (1.0f / fConst2);
		fConst4 = (1.0f / (((fConst3 + 0.517638087f) / fConst2) + 1.0f));
		float fConst5 = Karplus_faustpower2_f(fConst2);
		fConst6 = (1.0f / fConst5);
		fConst7 = (1.0f / (((fConst3 + 1.41421354f) / fConst2) + 1.0f));
		fConst8 = (1.0f / (((fConst3 + 1.93185163f) / fConst2) + 1.0f));
		fConst9 = (((fConst3 + -1.93185163f) / fConst2) + 1.0f);
		fConst10 = (2.0f * (1.0f - fConst6));
		fConst11 = (0.0f - (2.0f / fConst5));
		fConst12 = (((fConst3 + -1.41421354f) / fConst2) + 1.0f);
		fConst13 = (((fConst3 + -0.517638087f) / fConst2) + 1.0f);
	}
	
	virtual void instanceResetUserInterface() {
		fButton0 = FAUSTFLOAT(0.0f);
		fVslider0 = FAUSTFLOAT(0.001f);
		fVslider1 = FAUSTFLOAT(0.5f);
		fEntry0 = FAUSTFLOAT(500.0f);
		fVslider2 = FAUSTFLOAT(0.001f);
		fHslider0 = FAUSTFLOAT(0.0f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fVec0[l0] = 0.0f;
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec1[l1] = 0.0f;
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			iRec2[l2] = 0;
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			iRec6[l3] = 0;
		}
		for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) {
			fRec5[l4] = 0.0f;
		}
		for (int l5 = 0; (l5 < 3); l5 = (l5 + 1)) {
			fRec4[l5] = 0.0f;
		}
		for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) {
			fRec3[l6] = 0.0f;
		}
		for (int l7 = 0; (l7 < 4); l7 = (l7 + 1)) {
			fRec10[l7] = 0.0f;
		}
		for (int l8 = 0; (l8 < 3); l8 = (l8 + 1)) {
			fRec9[l8] = 0.0f;
		}
		for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) {
			fRec8[l9] = 0.0f;
		}
		for (int l10 = 0; (l10 < 3); l10 = (l10 + 1)) {
			fRec7[l10] = 0.0f;
		}
		IOTA = 0;
		for (int l11 = 0; (l11 < 4096); l11 = (l11 + 1)) {
			fRec0[l11] = 0.0f;
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
	
	virtual Karplus* clone() {
		return new Karplus();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("Karplus");
		ui_interface->addNumEntry("freq", &fEntry0, FAUSTFLOAT(500.0f), FAUSTFLOAT(200.0f), FAUSTFLOAT(1000.0f), FAUSTFLOAT(0.00999999978f));
		ui_interface->addButton("gate", &fButton0);
		ui_interface->addVerticalSlider("kAtt", &fVslider2, FAUSTFLOAT(0.00100000005f), FAUSTFLOAT(9.99999975e-05f), FAUSTFLOAT(1.0f), FAUSTFLOAT(9.99999975e-05f));
		ui_interface->addVerticalSlider("kFeed", &fVslider1, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00100000005f));
		ui_interface->addVerticalSlider("kRel", &fVslider0, FAUSTFLOAT(0.00100000005f), FAUSTFLOAT(9.99999975e-05f), FAUSTFLOAT(1.0f), FAUSTFLOAT(9.99999975e-05f));
		ui_interface->declare(&fHslider0, "style", "knob");
		ui_interface->addHorizontalSlider("kSwitch", &fHslider0, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = float(fButton0);
		float fSlow1 = float(fVslider0);
		float fSlow2 = (0.5f * (fSlow0 * std::pow(10.0f, (0.25f * (0.0f - fSlow1)))));
		float fSlow3 = (0.0f - (std::pow(10.0f, (3.0f * (0.0f - float(fVslider1)))) + -1.0f));
		float fSlow4 = std::max<float>(20.0f, float(fEntry0));
		float fSlow5 = ((17.3123398f * std::log((0.0022727272f * fSlow4))) + 69.0f);
		float fSlow6 = float((((fSlow5 < 19.0f) + 1) * ((fSlow5 < 31.0f) + 1)));
		float fSlow7 = (fConst0 * (fSlow6 / std::max<float>(20.0f, (fSlow4 * fSlow6))));
		float fSlow8 = std::floor(fSlow7);
		float fSlow9 = (fSlow8 + (1.0f - fSlow7));
		int iSlow10 = int(fSlow7);
		int iSlow11 = (int(std::min<float>(fConst1, float(std::max<int>(0, int(iSlow10))))) + 1);
		float fSlow12 = (fSlow7 - fSlow8);
		int iSlow13 = (int(std::min<float>(fConst1, float(std::max<int>(0, int((iSlow10 + 1)))))) + 1);
		float fSlow14 = float(fVslider2);
		float fSlow15 = (fConst4 * std::max<float>(1.0f, (0.0f - (2.0f * ((fConst0 * fSlow14) + -1.0f)))));
		float fSlow16 = std::max<float>(1.0f, (fConst0 * std::max<float>(0.00100000005f, fSlow14)));
		float fSlow17 = (1.0f / fSlow16);
		float fSlow18 = (1.0f / std::max<float>(1.0f, (fConst0 * std::max<float>(0.00100000005f, fSlow1))));
		int iSlow19 = (fSlow0 == 0.0f);
		float fSlow20 = float(fHslider0);
		float fSlow21 = (0.25f * float((fSlow20 == 0.0f)));
		float fSlow22 = (2.25f * float((fSlow20 == 1.0f)));
		for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
			fVec0[0] = fSlow0;
			fRec1[0] = (fSlow0 + (fRec1[1] * float((fVec0[1] >= fSlow0))));
			iRec2[0] = (iSlow19 * (iRec2[1] + 1));
			iRec6[0] = (((1103515245 * iRec6[1]) & 2147483647) + 12345);
			float fTemp0 = (4.65661287e-10f * float(iRec6[0]));
			fRec5[0] = (fTemp0 - (fConst8 * ((fConst9 * fRec5[2]) + (fConst10 * fRec5[1]))));
			fRec4[0] = ((fConst8 * (((fConst6 * fRec5[0]) + (fConst11 * fRec5[1])) + (fConst6 * fRec5[2]))) - (fConst7 * ((fConst12 * fRec4[2]) + (fConst10 * fRec4[1]))));
			fRec3[0] = ((fConst7 * (((fConst6 * fRec4[0]) + (fConst11 * fRec4[1])) + (fConst6 * fRec4[2]))) - (fConst4 * ((fConst13 * fRec3[2]) + (fConst10 * fRec3[1]))));
			fRec10[0] = (((0.522189379f * fRec10[3]) + (fTemp0 + (2.49495602f * fRec10[1]))) - (2.0172658f * fRec10[2]));
			fRec9[0] = (((0.0499220341f * fRec10[0]) + (0.0506126992f * fRec10[2])) - (((0.0959935337f * fRec10[1]) + (0.00440878607f * fRec10[3])) + (fConst8 * ((fConst9 * fRec9[2]) + (fConst10 * fRec9[1])))));
			fRec8[0] = ((fConst8 * (((fConst6 * fRec9[0]) + (fConst11 * fRec9[1])) + (fConst6 * fRec9[2]))) - (fConst7 * ((fConst12 * fRec8[2]) + (fConst10 * fRec8[1]))));
			fRec7[0] = ((fConst7 * (((fConst11 * fRec8[1]) + (fConst6 * fRec8[0])) + (fConst6 * fRec8[2]))) - (fConst4 * ((fConst13 * fRec7[2]) + (fConst10 * fRec7[1]))));
			fRec0[(IOTA & 4095)] = ((fSlow3 * ((fSlow9 * fRec0[((IOTA - iSlow11) & 4095)]) + (fSlow12 * fRec0[((IOTA - iSlow13) & 4095)]))) + (fSlow15 * (std::max<float>(0.0f, (std::min<float>((fSlow17 * fRec1[0]), std::max<float>((1.0f - (fSlow18 * (fRec1[0] - fSlow16))), 0.0f)) * (1.0f - float(iRec2[0])))) * ((fSlow21 * (((fConst6 * fRec3[0]) + (fConst11 * fRec3[1])) + (fConst6 * fRec3[2]))) + (fSlow22 * (((fConst6 * fRec7[0]) + (fConst11 * fRec7[1])) + (fConst6 * fRec7[2])))))));
			float fTemp1 = (fSlow2 * fRec0[((IOTA - 0) & 4095)]);
			output0[i0] = FAUSTFLOAT(fTemp1);
			output1[i0] = FAUSTFLOAT(fTemp1);
			fVec0[1] = fVec0[0];
			fRec1[1] = fRec1[0];
			iRec2[1] = iRec2[0];
			iRec6[1] = iRec6[0];
			fRec5[2] = fRec5[1];
			fRec5[1] = fRec5[0];
			fRec4[2] = fRec4[1];
			fRec4[1] = fRec4[0];
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				fRec10[j0] = fRec10[(j0 - 1)];
			}
			fRec9[2] = fRec9[1];
			fRec9[1] = fRec9[0];
			fRec8[2] = fRec8[1];
			fRec8[1] = fRec8[0];
			fRec7[2] = fRec7[1];
			fRec7[1] = fRec7[0];
			IOTA = (IOTA + 1);
		}
	}

};

#endif
