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

class KarplusSIG0 {
	
  private:
	
	int iVec1[2];
	int iRec3[2];
	
  public:
	
	int getNumInputsKarplusSIG0() {
		return 0;
	}
	int getNumOutputsKarplusSIG0() {
		return 1;
	}
	
	void instanceInitKarplusSIG0(int sample_rate) {
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			iVec1[l3] = 0;
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			iRec3[l4] = 0;
		}
	}
	
	void fillKarplusSIG0(int count, float* table) {
		for (int i1 = 0; (i1 < count); i1 = (i1 + 1)) {
			iVec1[0] = 1;
			iRec3[0] = ((iVec1[1] + iRec3[1]) % 65536);
			table[i1] = std::sin((9.58738019e-05f * float(iRec3[0])));
			iVec1[1] = iVec1[0];
			iRec3[1] = iRec3[0];
		}
	}

};

static KarplusSIG0* newKarplusSIG0() { return (KarplusSIG0*)new KarplusSIG0(); }
static void deleteKarplusSIG0(KarplusSIG0* dsp) { delete dsp; }

static float ftbl0KarplusSIG0[65536];
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
	
	FAUSTFLOAT fVslider0;
	int fSampleRate;
	float fConst0;
	FAUSTFLOAT fEntry0;
	float fConst1;
	float fConst2;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fButton0;
	float fVec0[2];
	float fRec1[2];
	FAUSTFLOAT fVslider2;
	int iRec2[2];
	FAUSTFLOAT fHslider0;
	float fConst3;
	FAUSTFLOAT fVslider3;
	float fConst4;
	float fRec5[2];
	FAUSTFLOAT fVslider4;
	float fRec6[2];
	float fRec4[2];
	float fConst8;
	float fConst10;
	float fConst11;
	float fConst12;
	float fConst13;
	int iRec10[2];
	float fConst14;
	float fConst15;
	float fRec9[3];
	float fConst16;
	float fRec8[3];
	float fConst17;
	float fConst18;
	float fRec7[3];
	float fConst19;
	float fRec14[4];
	float fRec13[3];
	float fRec12[3];
	float fRec11[3];
	int IOTA;
	float fRec0[1024];
	
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
		KarplusSIG0* sig0 = newKarplusSIG0();
		sig0->instanceInitKarplusSIG0(sample_rate);
		sig0->fillKarplusSIG0(65536, ftbl0KarplusSIG0);
		deleteKarplusSIG0(sig0);
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = (fConst0 + 1.0f);
		fConst2 = (1.0f / fConst0);
		fConst3 = (44.0999985f / fConst0);
		fConst4 = (1.0f - fConst3);
		float fConst5 = std::tan((62.831852f / fConst0));
		float fConst6 = (1.0f / fConst5);
		float fConst7 = (((fConst6 + 0.517638087f) / fConst5) + 1.0f);
		fConst8 = (0.400000006f / fConst7);
		float fConst9 = Karplus_faustpower2_f(fConst5);
		fConst10 = (0.0f - (2.0f / fConst9));
		fConst11 = (1.0f / (((fConst6 + 1.41421354f) / fConst5) + 1.0f));
		fConst12 = (1.0f / fConst9);
		fConst13 = (1.0f / (((fConst6 + 1.93185163f) / fConst5) + 1.0f));
		fConst14 = (((fConst6 + -1.93185163f) / fConst5) + 1.0f);
		fConst15 = (2.0f * (1.0f - fConst12));
		fConst16 = (((fConst6 + -1.41421354f) / fConst5) + 1.0f);
		fConst17 = (1.0f / fConst7);
		fConst18 = (((fConst6 + -0.517638087f) / fConst5) + 1.0f);
		fConst19 = (2.25f / fConst7);
	}
	
	virtual void instanceResetUserInterface() {
		fVslider0 = FAUSTFLOAT(0.5f);
		fEntry0 = FAUSTFLOAT(500.0f);
		fVslider1 = FAUSTFLOAT(1.0f);
		fButton0 = FAUSTFLOAT(0.0f);
		fVslider2 = FAUSTFLOAT(10.0f);
		fHslider0 = FAUSTFLOAT(1.0f);
		fVslider3 = FAUSTFLOAT(500.0f);
		fVslider4 = FAUSTFLOAT(2.0f);
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
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec5[l5] = 0.0f;
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec6[l6] = 0.0f;
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec4[l7] = 0.0f;
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			iRec10[l8] = 0;
		}
		for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) {
			fRec9[l9] = 0.0f;
		}
		for (int l10 = 0; (l10 < 3); l10 = (l10 + 1)) {
			fRec8[l10] = 0.0f;
		}
		for (int l11 = 0; (l11 < 3); l11 = (l11 + 1)) {
			fRec7[l11] = 0.0f;
		}
		for (int l12 = 0; (l12 < 4); l12 = (l12 + 1)) {
			fRec14[l12] = 0.0f;
		}
		for (int l13 = 0; (l13 < 3); l13 = (l13 + 1)) {
			fRec13[l13] = 0.0f;
		}
		for (int l14 = 0; (l14 < 3); l14 = (l14 + 1)) {
			fRec12[l14] = 0.0f;
		}
		for (int l15 = 0; (l15 < 3); l15 = (l15 + 1)) {
			fRec11[l15] = 0.0f;
		}
		IOTA = 0;
		for (int l16 = 0; (l16 < 1024); l16 = (l16 + 1)) {
			fRec0[l16] = 0.0f;
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
		ui_interface->declare(&fVslider3, "scale", "log");
		ui_interface->addVerticalSlider("fmDepth", &fVslider3, FAUSTFLOAT(500.0f), FAUSTFLOAT(100.0f), FAUSTFLOAT(8000.0f), FAUSTFLOAT(1.0f));
		ui_interface->addVerticalSlider("fmIndex", &fVslider4, FAUSTFLOAT(2.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(8.0f), FAUSTFLOAT(1.0f));
		ui_interface->addNumEntry("freq", &fEntry0, FAUSTFLOAT(500.0f), FAUSTFLOAT(200.0f), FAUSTFLOAT(1000.0f), FAUSTFLOAT(0.00999999978f));
		ui_interface->addButton("gate", &fButton0);
		ui_interface->declare(&fVslider1, "scale", "log");
		ui_interface->addVerticalSlider("kAtt", &fVslider1, FAUSTFLOAT(1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(48000.0f), FAUSTFLOAT(1.0f));
		ui_interface->addVerticalSlider("kFeed", &fVslider0, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00100000005f));
		ui_interface->declare(&fVslider2, "scale", "log");
		ui_interface->addVerticalSlider("kRel", &fVslider2, FAUSTFLOAT(10.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(48000.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider0, "style", "knob");
		ui_interface->addHorizontalSlider("kSwitch", &fHslider0, FAUSTFLOAT(1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(3.0f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = ((0.200000003f * float(fVslider0)) + 0.799000025f);
		float fSlow1 = std::max<float>(20.0f, float(fEntry0));
		float fSlow2 = (fConst0 / fSlow1);
		float fSlow3 = std::floor(fSlow2);
		float fSlow4 = (fSlow3 + (1.0f - fSlow2));
		int iSlow5 = int(fSlow2);
		int iSlow6 = (int(std::min<float>(fConst1, float(std::max<int>(0, iSlow5)))) + 1);
		float fSlow7 = (fSlow2 - fSlow3);
		int iSlow8 = (int(std::min<float>(fConst1, float(std::max<int>(0, (iSlow5 + 1))))) + 1);
		float fSlow9 = float(fVslider1);
		float fSlow10 = std::max<float>(1.0f, (fConst0 * std::max<float>(0.00100000005f, (fConst2 * fSlow9))));
		float fSlow11 = (1.0f / fSlow10);
		float fSlow12 = float(fButton0);
		float fSlow13 = (1.0f / std::max<float>(1.0f, (fConst0 * std::max<float>(0.00100000005f, (fConst2 * float(fVslider2))))));
		int iSlow14 = (fSlow12 == 0.0f);
		float fSlow15 = float(fHslider0);
		float fSlow16 = (fSlow9 + -1.0f);
		float fSlow17 = (0.03125f * (float((fSlow15 == 2.0f)) * std::max<float>(1.0f, (0.0f - (4.0f * fSlow16)))));
		float fSlow18 = (fConst3 * float(fVslider3));
		float fSlow19 = (fConst2 * (fSlow1 * float(fVslider4)));
		float fSlow20 = std::max<float>(1.0f, (0.0f - (2.0f * fSlow16)));
		float fSlow21 = (fConst8 * (float((fSlow15 == 1.0f)) * fSlow20));
		float fSlow22 = (fConst19 * (float((fSlow15 == 3.0f)) * fSlow20));
		for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
			fVec0[0] = fSlow12;
			fRec1[0] = (fSlow12 + (fRec1[1] * float((fVec0[1] >= fSlow12))));
			iRec2[0] = (iSlow14 * (iRec2[1] + 1));
			fRec5[0] = (fSlow18 + (fConst4 * fRec5[1]));
			fRec6[0] = (fSlow19 + (fRec6[1] - std::floor((fSlow19 + fRec6[1]))));
			float fTemp0 = (fRec4[1] + (fConst2 * std::min<float>(18000.0f, (fSlow1 + (std::max<float>(100.0f, fRec5[0]) * ftbl0KarplusSIG0[int((65536.0f * fRec6[0]))])))));
			fRec4[0] = (fTemp0 - std::floor(fTemp0));
			iRec10[0] = (((1103515245 * iRec10[1]) & 2147483647) + 12345);
			float fTemp1 = (4.65661287e-10f * float(iRec10[0]));
			fRec9[0] = (fTemp1 - (fConst13 * ((fConst14 * fRec9[2]) + (fConst15 * fRec9[1]))));
			fRec8[0] = ((fConst13 * (((fConst12 * fRec9[0]) + (fConst10 * fRec9[1])) + (fConst12 * fRec9[2]))) - (fConst11 * ((fConst16 * fRec8[2]) + (fConst15 * fRec8[1]))));
			fRec7[0] = ((fConst11 * (((fConst12 * fRec8[0]) + (fConst10 * fRec8[1])) + (fConst12 * fRec8[2]))) - (fConst17 * ((fConst18 * fRec7[2]) + (fConst15 * fRec7[1]))));
			fRec14[0] = (((2.49495602f * fRec14[1]) + (fTemp1 + (0.522189379f * fRec14[3]))) - (2.0172658f * fRec14[2]));
			fRec13[0] = (((0.0499220341f * fRec14[0]) + (0.0506126992f * fRec14[2])) - (((0.0959935337f * fRec14[1]) + (0.00440878607f * fRec14[3])) + (fConst13 * ((fConst14 * fRec13[2]) + (fConst15 * fRec13[1])))));
			fRec12[0] = ((fConst13 * (((fConst10 * fRec13[1]) + (fConst12 * fRec13[0])) + (fConst12 * fRec13[2]))) - (fConst11 * ((fConst16 * fRec12[2]) + (fConst15 * fRec12[1]))));
			fRec11[0] = ((fConst11 * (((fConst12 * fRec12[0]) + (fConst10 * fRec12[1])) + (fConst12 * fRec12[2]))) - (fConst17 * ((fConst18 * fRec11[2]) + (fConst15 * fRec11[1]))));
			fRec0[(IOTA & 1023)] = ((fSlow0 * ((fSlow4 * fRec0[((IOTA - iSlow6) & 1023)]) + (fSlow7 * fRec0[((IOTA - iSlow8) & 1023)]))) + (std::max<float>(0.0f, (std::min<float>((fSlow11 * fRec1[0]), std::max<float>(((fSlow13 * (fSlow10 - fRec1[0])) + 1.0f), 0.0f)) * (1.0f - float(iRec2[0])))) * (((fSlow17 * ftbl0KarplusSIG0[int((65536.0f * fRec4[0]))]) + (fSlow21 * (((fConst10 * fRec7[1]) + (fConst12 * fRec7[0])) + (fConst12 * fRec7[2])))) + (fSlow22 * (((fConst10 * fRec11[1]) + (fConst12 * fRec11[0])) + (fConst12 * fRec11[2]))))));
			float fTemp2 = (0.5f * fRec0[((IOTA - 0) & 1023)]);
			output0[i0] = FAUSTFLOAT(fTemp2);
			output1[i0] = FAUSTFLOAT(fTemp2);
			fVec0[1] = fVec0[0];
			fRec1[1] = fRec1[0];
			iRec2[1] = iRec2[0];
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			fRec4[1] = fRec4[0];
			iRec10[1] = iRec10[0];
			fRec9[2] = fRec9[1];
			fRec9[1] = fRec9[0];
			fRec8[2] = fRec8[1];
			fRec8[1] = fRec8[0];
			fRec7[2] = fRec7[1];
			fRec7[1] = fRec7[0];
			for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				fRec14[j0] = fRec14[(j0 - 1)];
			}
			fRec13[2] = fRec13[1];
			fRec13[1] = fRec13[0];
			fRec12[2] = fRec12[1];
			fRec12[1] = fRec12[0];
			fRec11[2] = fRec11[1];
			fRec11[1] = fRec11[0];
			IOTA = (IOTA + 1);
		}
	}

};

#endif
