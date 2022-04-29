/* ------------------------------------------------------------
name: "Generator"
Code generated with Faust 2.37.3 (https://faust.grame.fr)
Compilation options: -lang cpp -es 1 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __Generator_H__
#define  __Generator_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

class GeneratorSIG0 {
	
  private:
	
	int iVec3[2];
	int iRec3[2];
	
  public:
	
	int getNumInputsGeneratorSIG0() {
		return 0;
	}
	int getNumOutputsGeneratorSIG0() {
		return 1;
	}
	
	void instanceInitGeneratorSIG0(int sample_rate) {
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			iVec3[l5] = 0;
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			iRec3[l6] = 0;
		}
	}
	
	void fillGeneratorSIG0(int count, float* table) {
		for (int i1 = 0; (i1 < count); i1 = (i1 + 1)) {
			iVec3[0] = 1;
			iRec3[0] = ((iVec3[1] + iRec3[1]) % 65536);
			table[i1] = std::sin((9.58738019e-05f * float(iRec3[0])));
			iVec3[1] = iVec3[0];
			iRec3[1] = iRec3[0];
		}
	}

};

static GeneratorSIG0* newGeneratorSIG0() { return (GeneratorSIG0*)new GeneratorSIG0(); }
static void deleteGeneratorSIG0(GeneratorSIG0* dsp) { delete dsp; }

static float Generator_faustpower2_f(float value) {
	return (value * value);
}
static float ftbl0GeneratorSIG0[65536];

#ifndef FAUSTCLASS 
#define FAUSTCLASS Generator
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class Generator : public dsp {
	
 private:
	
	FAUSTFLOAT fButton0;
	FAUSTFLOAT fHslider0;
	int fSampleRate;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fVslider0;
	int iVec0[2];
	float fRec0[2];
	float fConst2;
	float fRec2[2];
	float fVec1[2];
	int IOTA;
	float fVec2[4096];
	float fConst3;
	float fRec4[2];
	float fConst4;
	float fRec5[2];
	float fConst7;
	float fConst9;
	float fConst10;
	float fConst11;
	FAUSTFLOAT fHslider1;
	int iRec9[2];
	float fRec10[4];
	float fConst12;
	FAUSTFLOAT fVslider1;
	float fConst13;
	float fRec11[2];
	float fConst14;
	float fConst15;
	float fConst16;
	float fRec8[3];
	float fConst17;
	float fRec7[3];
	float fConst18;
	float fRec6[3];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.1");
		m->declare("compile_options", "-lang cpp -es 1 -single -ftz 0");
		m->declare("filename", "Generator.dsp");
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
		m->declare("name", "Generator");
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
		GeneratorSIG0* sig0 = newGeneratorSIG0();
		sig0->instanceInitGeneratorSIG0(sample_rate);
		sig0->fillGeneratorSIG0(65536, ftbl0GeneratorSIG0);
		deleteGeneratorSIG0(sig0);
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = (1.0f / fConst0);
		fConst2 = (0.25f * fConst0);
		fConst3 = (0.5f * fConst0);
		fConst4 = (5.0f / fConst0);
		float fConst5 = std::tan((125.663704f / fConst0));
		float fConst6 = (1.0f / fConst5);
		fConst7 = (1.0f / (((fConst6 + 0.517638087f) / fConst5) + 1.0f));
		float fConst8 = Generator_faustpower2_f(fConst5);
		fConst9 = (0.0f - (2.0f / fConst8));
		fConst10 = (1.0f / (((fConst6 + 1.41421354f) / fConst5) + 1.0f));
		fConst11 = (1.0f / (((fConst6 + 1.93185163f) / fConst5) + 1.0f));
		fConst12 = (44.0999985f / fConst0);
		fConst13 = (1.0f - fConst12);
		fConst14 = (((fConst6 + -1.93185163f) / fConst5) + 1.0f);
		fConst15 = (1.0f / fConst8);
		fConst16 = (2.0f * (1.0f - fConst15));
		fConst17 = (((fConst6 + -1.41421354f) / fConst5) + 1.0f);
		fConst18 = (((fConst6 + -0.517638087f) / fConst5) + 1.0f);
	}
	
	virtual void instanceResetUserInterface() {
		fButton0 = FAUSTFLOAT(0.0f);
		fHslider0 = FAUSTFLOAT(0.0f);
		fVslider0 = FAUSTFLOAT(220.0f);
		fHslider1 = FAUSTFLOAT(0.0f);
		fVslider1 = FAUSTFLOAT(0.0f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec0[l1] = 0.0f;
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec2[l2] = 0.0f;
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fVec1[l3] = 0.0f;
		}
		IOTA = 0;
		for (int l4 = 0; (l4 < 4096); l4 = (l4 + 1)) {
			fVec2[l4] = 0.0f;
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec4[l7] = 0.0f;
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec5[l8] = 0.0f;
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			iRec9[l9] = 0;
		}
		for (int l10 = 0; (l10 < 4); l10 = (l10 + 1)) {
			fRec10[l10] = 0.0f;
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec11[l11] = 0.0f;
		}
		for (int l12 = 0; (l12 < 3); l12 = (l12 + 1)) {
			fRec8[l12] = 0.0f;
		}
		for (int l13 = 0; (l13 < 3); l13 = (l13 + 1)) {
			fRec7[l13] = 0.0f;
		}
		for (int l14 = 0; (l14 < 3); l14 = (l14 + 1)) {
			fRec6[l14] = 0.0f;
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
	
	virtual Generator* clone() {
		return new Generator();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("Generator");
		ui_interface->addVerticalSlider("freq", &fVslider0, FAUSTFLOAT(220.0f), FAUSTFLOAT(20.0f), FAUSTFLOAT(20000.0f), FAUSTFLOAT(1.0f));
		ui_interface->addButton("gate", &fButton0);
		ui_interface->addVerticalSlider("noiseLevel", &fVslider1, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00100000005f));
		ui_interface->addHorizontalSlider("noiseShape", &fHslider1, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(1.0f));
		ui_interface->addHorizontalSlider("shape", &fHslider0, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(3.0f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = float(fButton0);
		float fSlow1 = float(fHslider0);
		float fSlow2 = float((fSlow1 == 0.0f));
		float fSlow3 = float(fVslider0);
		float fSlow4 = std::max<float>(1.1920929e-07f, std::fabs(fSlow3));
		float fSlow5 = (fConst1 * fSlow4);
		float fSlow6 = (1.0f - (fConst0 / fSlow4));
		float fSlow7 = (0.75f * float((fSlow1 == 1.0f)));
		float fSlow8 = std::max<float>(fSlow3, 23.4489498f);
		float fSlow9 = std::max<float>(20.0f, std::fabs(fSlow8));
		float fSlow10 = (fConst2 / fSlow9);
		float fSlow11 = (fConst1 * fSlow9);
		float fSlow12 = std::max<float>(0.0f, std::min<float>(2047.0f, (fConst3 / fSlow8)));
		float fSlow13 = std::floor(fSlow12);
		float fSlow14 = (fSlow13 + (1.0f - fSlow12));
		int iSlow15 = int(fSlow12);
		float fSlow16 = (fSlow12 - fSlow13);
		int iSlow17 = (iSlow15 + 1);
		float fSlow18 = (1.25f * float((fSlow1 == 2.0f)));
		float fSlow19 = (fConst1 * fSlow3);
		float fSlow20 = (fConst4 * (fSlow3 * float((fSlow1 == 3.0f))));
		float fSlow21 = float(fHslider1);
		float fSlow22 = (4.65661294e-11f * float((fSlow21 == 0.0f)));
		float fSlow23 = (2.0f * float((fSlow21 == 1.0f)));
		float fSlow24 = (fConst12 * float(fVslider1));
		for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
			iVec0[0] = 1;
			float fTemp0 = (fSlow5 + (fRec0[1] + -1.0f));
			int iTemp1 = (fTemp0 < 0.0f);
			float fTemp2 = (fSlow5 + fRec0[1]);
			fRec0[0] = (iTemp1 ? fTemp2 : fTemp0);
			float fThen1 = (fSlow5 + (fRec0[1] + (fSlow6 * fTemp0)));
			float fRec1 = (iTemp1 ? fTemp2 : fThen1);
			fRec2[0] = (fSlow11 + (fRec2[1] - std::floor((fSlow11 + fRec2[1]))));
			float fTemp3 = Generator_faustpower2_f(((2.0f * fRec2[0]) + -1.0f));
			fVec1[0] = fTemp3;
			float fTemp4 = (fSlow10 * (float(iVec0[1]) * (fTemp3 - fVec1[1])));
			fVec2[(IOTA & 4095)] = fTemp4;
			float fTemp5 = ((fSlow14 * fVec2[((IOTA - iSlow15) & 4095)]) + (fSlow16 * fVec2[((IOTA - iSlow17) & 4095)]));
			fRec4[0] = (fSlow19 + (fRec4[1] - std::floor((fSlow19 + fRec4[1]))));
			fRec5[0] = ((fTemp4 + (0.999000013f * fRec5[1])) - fTemp5);
			iRec9[0] = (((1103515245 * iRec9[1]) & 2147483647) + 12345);
			float fTemp6 = float(iRec9[0]);
			fRec10[0] = (((0.522189379f * fRec10[3]) + ((4.65661287e-10f * fTemp6) + (2.49495602f * fRec10[1]))) - (2.0172658f * fRec10[2]));
			fRec11[0] = (fSlow24 + (fConst13 * fRec11[1]));
			fRec8[0] = ((0.75f * (((fSlow22 * fTemp6) + (fSlow23 * (((0.0499220341f * fRec10[0]) + (0.0506126992f * fRec10[2])) - ((0.0959935337f * fRec10[1]) + (0.00440878607f * fRec10[3]))))) * std::pow(10.0f, (2.0f * (fRec11[0] + -1.0f))))) - (fConst11 * ((fConst14 * fRec8[2]) + (fConst16 * fRec8[1]))));
			fRec7[0] = ((fConst11 * (((fConst9 * fRec8[1]) + (fConst15 * fRec8[0])) + (fConst15 * fRec8[2]))) - (fConst10 * ((fConst17 * fRec7[2]) + (fConst16 * fRec7[1]))));
			fRec6[0] = ((fConst10 * (((fConst9 * fRec7[1]) + (fConst15 * fRec7[0])) + (fConst15 * fRec7[2]))) - (fConst7 * ((fConst18 * fRec6[2]) + (fConst16 * fRec6[1]))));
			float fTemp7 = (fSlow0 * ((0.117647059f * ((((fSlow2 * ((2.0f * fRec1) + -1.0f)) + (fSlow7 * (fTemp4 - fTemp5))) + (fSlow18 * ftbl0GeneratorSIG0[int((65536.0f * fRec4[0]))])) + (fSlow20 * fRec5[0]))) + (fConst7 * (((fConst9 * fRec6[1]) + (fConst15 * fRec6[0])) + (fConst15 * fRec6[2])))));
			output0[i0] = FAUSTFLOAT(fTemp7);
			output1[i0] = FAUSTFLOAT(fTemp7);
			iVec0[1] = iVec0[0];
			fRec0[1] = fRec0[0];
			fRec2[1] = fRec2[0];
			fVec1[1] = fVec1[0];
			IOTA = (IOTA + 1);
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			iRec9[1] = iRec9[0];
			for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				fRec10[j0] = fRec10[(j0 - 1)];
			}
			fRec11[1] = fRec11[0];
			fRec8[2] = fRec8[1];
			fRec8[1] = fRec8[0];
			fRec7[2] = fRec7[1];
			fRec7[1] = fRec7[0];
			fRec6[2] = fRec6[1];
			fRec6[1] = fRec6[0];
		}
	}

};

#endif
