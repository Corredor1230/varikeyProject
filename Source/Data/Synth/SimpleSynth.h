/* ------------------------------------------------------------
name: "Karplus"
Code generated with Faust 2.37.3 (https://faust.grame.fr)
Compilation options: -lang cpp -es 1 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __SimpleSynth_H__
#define  __SimpleSynth_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

class SimpleSynthSIG0 {
	
  private:
	
	int iVec1[2];
	int iRec4[2];
	
  public:
	
	int getNumInputsSimpleSynthSIG0() {
		return 0;
	}
	int getNumOutputsSimpleSynthSIG0() {
		return 1;
	}
	
	void instanceInitSimpleSynthSIG0(int sample_rate) {
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			iVec1[l4] = 0;
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			iRec4[l5] = 0;
		}
	}
	
	void fillSimpleSynthSIG0(int count, float* table) {
		for (int i1 = 0; (i1 < count); i1 = (i1 + 1)) {
			iVec1[0] = 1;
			iRec4[0] = ((iVec1[1] + iRec4[1]) % 65536);
			table[i1] = std::sin((9.58738019e-05f * float(iRec4[0])));
			iVec1[1] = iVec1[0];
			iRec4[1] = iRec4[0];
		}
	}

};

static SimpleSynthSIG0* newSimpleSynthSIG0() { return (SimpleSynthSIG0*)new SimpleSynthSIG0(); }
static void deleteSimpleSynthSIG0(SimpleSynthSIG0* dsp) { delete dsp; }

static float ftbl0SimpleSynthSIG0[65536];

#ifndef FAUSTCLASS 
#define FAUSTCLASS SimpleSynth
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class SimpleSynth : public dsp{
	
 private:
	
	FAUSTFLOAT fVslider0;
	int fSampleRate;
	float fConst0;
	FAUSTFLOAT fEntry0;
	float fConst1;
	float fConst2;
	FAUSTFLOAT fButton0;
	float fVec0[2];
	float fRec1[2];
	FAUSTFLOAT fVslider1;
	float fConst3;
	int iRec2[2];
	FAUSTFLOAT fHslider0;
	int iRec3[2];
	float fConst4;
	float fConst5;
	float fRec6[2];
	float fRec5[2];
	float fRec7[4];
	int IOTA;
	float fRec0[1024];
	float fConst6;
	float fConst7;
	float fConst8;
	float fConst9;
	float fConst10;
	FAUSTFLOAT fVslider2;
	float fConst11;
	float fRec8[2];
	
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
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.3");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.3");
		m->declare("name", "Karplus");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.1");
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
		SimpleSynthSIG0* sig0 = newSimpleSynthSIG0();
		sig0->instanceInitSimpleSynthSIG0(sample_rate);
		sig0->fillSimpleSynthSIG0(65536, ftbl0SimpleSynthSIG0);
		deleteSimpleSynthSIG0(sig0);
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = std::max<float>(1.0f, (9.99999975e-05f * fConst0));
		fConst2 = (1.0f / fConst1);
		fConst3 = (1.0f / std::max<float>(1.0f, (0.0500000007f * fConst0)));
		fConst4 = (1.0f / fConst0);
		fConst5 = (3.0f / fConst0);
		fConst6 = std::max<float>(1.0f, (0.00999999978f * fConst0));
		fConst7 = (1.0f / fConst6);
		fConst8 = (0.5f / std::max<float>(1.0f, (0.0399999991f * fConst0)));
		fConst9 = (1.0f / std::max<float>(1.0f, (0.200000003f * fConst0)));
		fConst10 = (44.0999985f / fConst0);
		fConst11 = (1.0f - fConst10);
	}
	
	virtual void instanceResetUserInterface() {
		fVslider0 = FAUSTFLOAT(0.5f);
		fEntry0 = FAUSTFLOAT(500.0f);
		fButton0 = FAUSTFLOAT(0.0f);
		fVslider1 = FAUSTFLOAT(1.0f);
		fHslider0 = FAUSTFLOAT(1.0f);
		fVslider2 = FAUSTFLOAT(-20.0f);
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
			iRec3[l3] = 0;
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec6[l6] = 0.0f;
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec5[l7] = 0.0f;
		}
		for (int l8 = 0; (l8 < 4); l8 = (l8 + 1)) {
			fRec7[l8] = 0.0f;
		}
		IOTA = 0;
		for (int l9 = 0; (l9 < 1024); l9 = (l9 + 1)) {
			fRec0[l9] = 0.0f;
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec8[l10] = 0.0f;
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
	
	virtual SimpleSynth* clone() {
		return new SimpleSynth();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("Karplus");
		ui_interface->addNumEntry("freq", &fEntry0, FAUSTFLOAT(500.0f), FAUSTFLOAT(200.0f), FAUSTFLOAT(1000.0f), FAUSTFLOAT(0.00999999978f));
		ui_interface->addButton("gate", &fButton0);
		ui_interface->declare(&fVslider1, "scale", "log");
		ui_interface->addVerticalSlider("kAtt", &fVslider1, FAUSTFLOAT(1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(20000.0f), FAUSTFLOAT(1.0f));
		ui_interface->addVerticalSlider("kFeed", &fVslider0, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00999999978f));
		ui_interface->declare(&fHslider0, "style", "knob");
		ui_interface->addHorizontalSlider("kSwitch", &fHslider0, FAUSTFLOAT(1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(3.0f), FAUSTFLOAT(1.0f));
		ui_interface->addVerticalSlider("volume", &fVslider2, FAUSTFLOAT(-10.0f), FAUSTFLOAT(-60.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = ((0.200000003f * float(fVslider0)) + 0.790000021f);
		float fSlow1 = std::max<float>(20.0f, float(fEntry0));
		int iSlow2 = (int(std::min<float>(fConst0, std::max<float>(0.0f, (fConst0 / fSlow1)))) + 1);
		float fSlow3 = float(fButton0);
		float fSlow4 = (1.0f / std::max<float>(1.0f, (fConst0 * std::max<float>(0.0f, (0.00100000005f * float(fVslider1))))));
		int iSlow5 = (fSlow3 == 0.0f);
		float fSlow6 = float(fHslider0);
		float fSlow7 = (2.32830644e-10f * float((fSlow6 == 1.0f)));
		float fSlow8 = (0.0416666679f * float((fSlow6 == 2.0f)));
		float fSlow9 = (fConst5 * fSlow1);
		float fSlow10 = (3.5f * float((fSlow6 == 3.0f)));
		float fSlow11 = (fConst10 * float(fVslider2));
		for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
			fVec0[0] = fSlow3;
			fRec1[0] = (fSlow3 + (fRec1[1] * float((fVec0[1] >= fSlow3))));
			iRec2[0] = (iSlow5 * (iRec2[1] + 1));
			float fTemp0 = float(iRec2[0]);
			iRec3[0] = (((1103515245 * iRec3[1]) & 2147483647) + 12345);
			float fTemp1 = float(iRec3[0]);
			fRec6[0] = (fSlow9 + (fRec6[1] - std::floor((fSlow9 + fRec6[1]))));
			float fTemp2 = (fRec5[1] + (fConst4 * std::min<float>(18000.0f, (fSlow1 + (1000.0f * ftbl0SimpleSynthSIG0[int((65536.0f * fRec6[0]))])))));
			fRec5[0] = (fTemp2 - std::floor(fTemp2));
			fRec7[0] = (((0.522189379f * fRec7[3]) + ((4.65661287e-10f * fTemp1) + (2.49495602f * fRec7[1]))) - (2.0172658f * fRec7[2]));
			fRec0[(IOTA & 1023)] = ((fSlow0 * fRec0[((IOTA - iSlow2) & 1023)]) + (std::max<float>(0.0f, (std::min<float>((fConst2 * fRec1[0]), std::max<float>(((fSlow4 * (fConst1 - fRec1[0])) + 1.0f), 0.0f)) * (1.0f - (fConst3 * fTemp0)))) * (((fSlow7 * fTemp1) + (fSlow8 * ftbl0SimpleSynthSIG0[int((65536.0f * fRec5[0]))])) + (fSlow10 * (((0.0499220341f * fRec7[0]) + (0.0506126992f * fRec7[2])) - ((0.0959935337f * fRec7[1]) + (0.00440878607f * fRec7[3])))))));
			fRec8[0] = (fSlow11 + (fConst11 * fRec8[1]));
			float fTemp3 = (0.181818187f * ((fRec0[((IOTA - 0) & 1023)] * std::max<float>(0.0f, (std::min<float>((fConst7 * fRec1[0]), std::max<float>(((fConst8 * (fConst6 - fRec1[0])) + 1.0f), 0.5f)) * (1.0f - (fConst9 * fTemp0))))) * std::pow(10.0f, (0.0500000007f * fRec8[0]))));
			output0[i0] = FAUSTFLOAT(fTemp3);
			output1[i0] = FAUSTFLOAT(fTemp3);
			fVec0[1] = fVec0[0];
			fRec1[1] = fRec1[0];
			iRec2[1] = iRec2[0];
			iRec3[1] = iRec3[0];
			fRec6[1] = fRec6[0];
			fRec5[1] = fRec5[0];
			for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				fRec7[j0] = fRec7[(j0 - 1)];
			}
			IOTA = (IOTA + 1);
			fRec8[1] = fRec8[0];
		}
	}

};

#endif
