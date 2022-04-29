/* ------------------------------------------------------------
name: "Additive"
Code generated with Faust 2.37.3 (https://faust.grame.fr)
Compilation options: -lang cpp -es 1 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __Additive_H__
#define  __Additive_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

class AdditiveSIG0 {
	
  private:
	
	int iVec0[2];
	int iRec1[2];
	
  public:
	
	int getNumInputsAdditiveSIG0() {
		return 0;
	}
	int getNumOutputsAdditiveSIG0() {
		return 1;
	}
	
	void instanceInitAdditiveSIG0(int sample_rate) {
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			iVec0[l1] = 0;
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			iRec1[l2] = 0;
		}
	}
	
	void fillAdditiveSIG0(int count, float* table) {
		for (int i1 = 0; (i1 < count); i1 = (i1 + 1)) {
			iVec0[0] = 1;
			iRec1[0] = ((iVec0[1] + iRec1[1]) % 65536);
			table[i1] = std::sin((9.58738019e-05f * float(iRec1[0])));
			iVec0[1] = iVec0[0];
			iRec1[1] = iRec1[0];
		}
	}

};

static AdditiveSIG0* newAdditiveSIG0() { return (AdditiveSIG0*)new AdditiveSIG0(); }
static void deleteAdditiveSIG0(AdditiveSIG0* dsp) { delete dsp; }

static float ftbl0AdditiveSIG0[65536];

#ifndef FAUSTCLASS 
#define FAUSTCLASS Additive
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class Additive : public dsp {
	
 private:
	
	FAUSTFLOAT fButton0;
	int fSampleRate;
	float fConst1;
	FAUSTFLOAT fVslider0;
	float fConst2;
	float fRec0[2];
	float fConst3;
	FAUSTFLOAT fEntry0;
	float fRec2[2];
	FAUSTFLOAT fVslider1;
	float fRec3[2];
	float fConst4;
	float fRec4[2];
	FAUSTFLOAT fVslider2;
	float fRec5[2];
	float fConst5;
	float fRec6[2];
	FAUSTFLOAT fVslider3;
	float fRec7[2];
	float fConst6;
	float fRec8[2];
	FAUSTFLOAT fVslider4;
	float fRec9[2];
	float fConst7;
	float fRec10[2];
	FAUSTFLOAT fVslider5;
	float fRec11[2];
	float fConst8;
	float fRec12[2];
	FAUSTFLOAT fVslider6;
	float fRec13[2];
	float fConst9;
	float fRec14[2];
	FAUSTFLOAT fVslider7;
	float fRec15[2];
	float fConst10;
	float fRec16[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.1");
		m->declare("compile_options", "-lang cpp -es 1 -single -ftz 0");
		m->declare("filename", "Additive.dsp");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.3");
		m->declare("name", "Additive");
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
		AdditiveSIG0* sig0 = newAdditiveSIG0();
		sig0->instanceInitAdditiveSIG0(sample_rate);
		sig0->fillAdditiveSIG0(65536, ftbl0AdditiveSIG0);
		deleteAdditiveSIG0(sig0);
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		float fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = (44.0999985f / fConst0);
		fConst2 = (1.0f - fConst1);
		fConst3 = (3.0f / fConst0);
		fConst4 = (4.0f / fConst0);
		fConst5 = (1.0f / fConst0);
		fConst6 = (2.0f / fConst0);
		fConst7 = (5.0f / fConst0);
		fConst8 = (6.0f / fConst0);
		fConst9 = (7.0f / fConst0);
		fConst10 = (8.0f / fConst0);
	}
	
	virtual void instanceResetUserInterface() {
		fButton0 = FAUSTFLOAT(0.0f);
		fVslider0 = FAUSTFLOAT(0.0f);
		fEntry0 = FAUSTFLOAT(500.0f);
		fVslider1 = FAUSTFLOAT(0.0f);
		fVslider2 = FAUSTFLOAT(8.0f);
		fVslider3 = FAUSTFLOAT(0.0f);
		fVslider4 = FAUSTFLOAT(0.0f);
		fVslider5 = FAUSTFLOAT(0.0f);
		fVslider6 = FAUSTFLOAT(0.0f);
		fVslider7 = FAUSTFLOAT(0.0f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec0[l0] = 0.0f;
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec2[l3] = 0.0f;
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec3[l4] = 0.0f;
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec4[l5] = 0.0f;
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec5[l6] = 0.0f;
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec6[l7] = 0.0f;
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec7[l8] = 0.0f;
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec8[l9] = 0.0f;
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec9[l10] = 0.0f;
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec10[l11] = 0.0f;
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec11[l12] = 0.0f;
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec12[l13] = 0.0f;
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec13[l14] = 0.0f;
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec14[l15] = 0.0f;
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fRec15[l16] = 0.0f;
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec16[l17] = 0.0f;
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
	
	virtual Additive* clone() {
		return new Additive();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("Additive");
		ui_interface->openHorizontalBox("Harmonics");
		ui_interface->addVerticalSlider("eigth", &fVslider7, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(8.0f), FAUSTFLOAT(1.0f));
		ui_interface->addVerticalSlider("fifth", &fVslider4, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(8.0f), FAUSTFLOAT(1.0f));
		ui_interface->addVerticalSlider("first", &fVslider2, FAUSTFLOAT(8.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(8.0f), FAUSTFLOAT(1.0f));
		ui_interface->addVerticalSlider("fourth", &fVslider1, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(8.0f), FAUSTFLOAT(1.0f));
		ui_interface->addVerticalSlider("second", &fVslider3, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(8.0f), FAUSTFLOAT(1.0f));
		ui_interface->addVerticalSlider("seventh", &fVslider6, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(8.0f), FAUSTFLOAT(1.0f));
		ui_interface->addVerticalSlider("sixth", &fVslider5, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(8.0f), FAUSTFLOAT(1.0f));
		ui_interface->addVerticalSlider("third", &fVslider0, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(8.0f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
		ui_interface->addNumEntry("freq", &fEntry0, FAUSTFLOAT(500.0f), FAUSTFLOAT(200.0f), FAUSTFLOAT(1000.0f), FAUSTFLOAT(0.00999999978f));
		ui_interface->addButton("gate", &fButton0);
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = (0.400000006f * float(fButton0));
		float fSlow1 = (fConst1 * float(fVslider0));
		float fSlow2 = std::max<float>(20.0f, float(fEntry0));
		float fSlow3 = (fConst3 * fSlow2);
		float fSlow4 = (fConst1 * float(fVslider1));
		float fSlow5 = (fConst4 * fSlow2);
		float fSlow6 = (fConst1 * float(fVslider2));
		float fSlow7 = (fConst5 * fSlow2);
		float fSlow8 = (fConst1 * float(fVslider3));
		float fSlow9 = (fConst6 * fSlow2);
		float fSlow10 = (fConst1 * float(fVslider4));
		float fSlow11 = (fConst7 * fSlow2);
		float fSlow12 = (fConst1 * float(fVslider5));
		float fSlow13 = (fConst8 * fSlow2);
		float fSlow14 = (fConst1 * float(fVslider6));
		float fSlow15 = (fConst9 * fSlow2);
		float fSlow16 = (fConst1 * float(fVslider7));
		float fSlow17 = (fConst10 * fSlow2);
		for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
			fRec0[0] = (fSlow1 + (fConst2 * fRec0[1]));
			float fTemp0 = std::pow(10.0f, (3.0f * ((0.125f * fRec0[0]) + -1.0f)));
			fRec2[0] = (fSlow3 + (fRec2[1] - std::floor((fSlow3 + fRec2[1]))));
			fRec3[0] = (fSlow4 + (fConst2 * fRec3[1]));
			float fTemp1 = std::pow(10.0f, (3.0f * ((0.125f * fRec3[0]) + -1.0f)));
			fRec4[0] = (fSlow5 + (fRec4[1] - std::floor((fSlow5 + fRec4[1]))));
			fRec5[0] = (fSlow6 + (fConst2 * fRec5[1]));
			float fTemp2 = std::pow(10.0f, (3.0f * ((0.125f * fRec5[0]) + -1.0f)));
			fRec6[0] = (fSlow7 + (fRec6[1] - std::floor((fSlow7 + fRec6[1]))));
			fRec7[0] = (fSlow8 + (fConst2 * fRec7[1]));
			float fTemp3 = std::pow(10.0f, (3.0f * ((0.125f * fRec7[0]) + -1.0f)));
			fRec8[0] = (fSlow9 + (fRec8[1] - std::floor((fSlow9 + fRec8[1]))));
			fRec9[0] = (fSlow10 + (fConst2 * fRec9[1]));
			float fTemp4 = std::pow(10.0f, (3.0f * ((0.125f * fRec9[0]) + -1.0f)));
			fRec10[0] = (fSlow11 + (fRec10[1] - std::floor((fSlow11 + fRec10[1]))));
			fRec11[0] = (fSlow12 + (fConst2 * fRec11[1]));
			float fTemp5 = std::pow(10.0f, (3.0f * ((0.125f * fRec11[0]) + -1.0f)));
			fRec12[0] = (fSlow13 + (fRec12[1] - std::floor((fSlow13 + fRec12[1]))));
			fRec13[0] = (fSlow14 + (fConst2 * fRec13[1]));
			float fTemp6 = std::pow(10.0f, (3.0f * ((0.125f * fRec13[0]) + -1.0f)));
			fRec14[0] = (fSlow15 + (fRec14[1] - std::floor((fSlow15 + fRec14[1]))));
			fRec15[0] = (fSlow16 + (fConst2 * fRec15[1]));
			float fTemp7 = std::pow(10.0f, (3.0f * ((0.125f * fRec15[0]) + -1.0f)));
			fRec16[0] = (fSlow17 + (fRec16[1] - std::floor((fSlow17 + fRec16[1]))));
			float fTemp8 = (fSlow0 * (((((fTemp0 * ftbl0AdditiveSIG0[int((65536.0f * fRec2[0]))]) + ((fTemp1 * ftbl0AdditiveSIG0[int((65536.0f * fRec4[0]))]) + ((fTemp2 * ftbl0AdditiveSIG0[int((65536.0f * fRec6[0]))]) + ((fTemp3 * ftbl0AdditiveSIG0[int((65536.0f * fRec8[0]))]) + ((fTemp4 * ftbl0AdditiveSIG0[int((65536.0f * fRec10[0]))]) + (fTemp5 * ftbl0AdditiveSIG0[int((65536.0f * fRec12[0]))])))))) + (fTemp6 * ftbl0AdditiveSIG0[int((65536.0f * fRec14[0]))])) + (fTemp7 * ftbl0AdditiveSIG0[int((65536.0f * fRec16[0]))])) / ((fTemp7 + (fTemp6 + (fTemp1 + (fTemp3 + (fTemp0 + (fTemp2 + (fTemp4 + fTemp5))))))) + 1.0f)));
			output0[i0] = FAUSTFLOAT(fTemp8);
			output1[i0] = FAUSTFLOAT(fTemp8);
			fRec0[1] = fRec0[0];
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			fRec7[1] = fRec7[0];
			fRec8[1] = fRec8[0];
			fRec9[1] = fRec9[0];
			fRec10[1] = fRec10[0];
			fRec11[1] = fRec11[0];
			fRec12[1] = fRec12[0];
			fRec13[1] = fRec13[0];
			fRec14[1] = fRec14[0];
			fRec15[1] = fRec15[0];
			fRec16[1] = fRec16[0];
		}
	}

};

#endif
