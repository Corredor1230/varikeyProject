/* ------------------------------------------------------------
name: "Filter"
Code generated with Faust 2.37.3 (https://faust.grame.fr)
Compilation options: -lang cpp -es 1 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __HipLopFilter_H__
#define  __HipLopFilter_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

static float HipLopFilter_faustpower2_f(float value) {
	return (value * value);
}

#ifndef FAUSTCLASS 
#define FAUSTCLASS HipLopFilter
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class HipLopFilter : public dsp {
	
 private:
	
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fCheckbox1;
	int fSampleRate;
	float fConst1;
	FAUSTFLOAT fVslider0;
	float fConst2;
	float fRec0[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT fVslider3;
	float fConst3;
	FAUSTFLOAT fVslider4;
	float fRec2[2];
	float fRec1[3];
	float fConst4;
	float fConst5;
	float fConst6;
	float fConst7;
	float fRec5[2];
	float fRec4[2];
	float fRec3[2];
	FAUSTFLOAT fVslider5;
	float fRec6[2];
	FAUSTFLOAT fVslider6;
	float fRec8[2];
	float fRec7[3];
	float fRec11[2];
	float fRec10[2];
	float fRec9[2];
	float fRec13[3];
	float fRec12[3];
	float fRec16[2];
	float fRec15[2];
	float fRec14[2];
	float fRec17[3];
	float fRec20[2];
	float fRec19[2];
	float fRec18[2];
	float fRec21[3];
	float fRec24[2];
	float fRec23[2];
	float fRec22[2];
	float fRec25[3];
	float fRec26[3];
	float fRec29[2];
	float fRec28[2];
	float fRec27[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "0.1");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.1");
		m->declare("compile_options", "-lang cpp -es 1 -single -ftz 0");
		m->declare("compressors.lib/compression_gain_mono:author", "Julius O. Smith III");
		m->declare("compressors.lib/compression_gain_mono:copyright", "Copyright (C) 2014-2020 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("compressors.lib/compression_gain_mono:license", "MIT-style STK-4.3 license");
		m->declare("compressors.lib/compressor_lad_mono:author", "Julius O. Smith III");
		m->declare("compressors.lib/compressor_lad_mono:copyright", "Copyright (C) 2014-2020 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("compressors.lib/compressor_lad_mono:license", "MIT-style STK-4.3 license");
		m->declare("compressors.lib/compressor_mono:author", "Julius O. Smith III");
		m->declare("compressors.lib/compressor_mono:copyright", "Copyright (C) 2014-2020 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("compressors.lib/compressor_mono:license", "MIT-style STK-4.3 license");
		m->declare("compressors.lib/name", "Faust Compressor Effect Library");
		m->declare("compressors.lib/version", "0.1");
		m->declare("filename", "Filter.dsp");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/resonhp:author", "Julius O. Smith III");
		m->declare("filters.lib/resonhp:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/resonhp:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/resonlp:author", "Julius O. Smith III");
		m->declare("filters.lib/resonlp:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/resonlp:license", "MIT-style STK-4.3 license");
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
		fConst1 = (44.0999985f / fConst0);
		fConst2 = (1.0f - fConst1);
		fConst3 = (3.14159274f / fConst0);
		fConst4 = std::exp((0.0f - (2000.0f / fConst0)));
		fConst5 = (1.0f - fConst4);
		fConst6 = std::exp((0.0f - (1000.0f / fConst0)));
		fConst7 = std::exp((0.0f - (142.857147f / fConst0)));
	}
	
	virtual void instanceResetUserInterface() {
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fCheckbox1 = FAUSTFLOAT(0.0f);
		fVslider0 = FAUSTFLOAT(1.0f);
		fVslider1 = FAUSTFLOAT(0.10000000000000001f);
		fVslider2 = FAUSTFLOAT(0.10000000000000001f);
		fVslider3 = FAUSTFLOAT(0.10000000000000001f);
		fVslider4 = FAUSTFLOAT(20000.0f);
		fVslider5 = FAUSTFLOAT(1.0f);
		fVslider6 = FAUSTFLOAT(20.0f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec0[l0] = 0.0f;
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec2[l1] = 0.0f;
		}
		for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) {
			fRec1[l2] = 0.0f;
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec5[l3] = 0.0f;
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec4[l4] = 0.0f;
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec3[l5] = 0.0f;
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec6[l6] = 0.0f;
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec8[l7] = 0.0f;
		}
		for (int l8 = 0; (l8 < 3); l8 = (l8 + 1)) {
			fRec7[l8] = 0.0f;
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec11[l9] = 0.0f;
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec10[l10] = 0.0f;
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec9[l11] = 0.0f;
		}
		for (int l12 = 0; (l12 < 3); l12 = (l12 + 1)) {
			fRec13[l12] = 0.0f;
		}
		for (int l13 = 0; (l13 < 3); l13 = (l13 + 1)) {
			fRec12[l13] = 0.0f;
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec16[l14] = 0.0f;
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec15[l15] = 0.0f;
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fRec14[l16] = 0.0f;
		}
		for (int l17 = 0; (l17 < 3); l17 = (l17 + 1)) {
			fRec17[l17] = 0.0f;
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fRec20[l18] = 0.0f;
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec19[l19] = 0.0f;
		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fRec18[l20] = 0.0f;
		}
		for (int l21 = 0; (l21 < 3); l21 = (l21 + 1)) {
			fRec21[l21] = 0.0f;
		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fRec24[l22] = 0.0f;
		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fRec23[l23] = 0.0f;
		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fRec22[l24] = 0.0f;
		}
		for (int l25 = 0; (l25 < 3); l25 = (l25 + 1)) {
			fRec25[l25] = 0.0f;
		}
		for (int l26 = 0; (l26 < 3); l26 = (l26 + 1)) {
			fRec26[l26] = 0.0f;
		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			fRec29[l27] = 0.0f;
		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			fRec28[l28] = 0.0f;
		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fRec27[l29] = 0.0f;
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
	
	virtual HipLopFilter* clone() {
		return new HipLopFilter();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("Filter");
		ui_interface->addVerticalSlider("distGain", &fVslider3, FAUSTFLOAT(0.100000001f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00999999978f));
		ui_interface->addVerticalSlider("distOut", &fVslider1, FAUSTFLOAT(0.100000001f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00999999978f));
		ui_interface->declare(&fVslider6, "scale", "log");
		ui_interface->addVerticalSlider("hipCutoff", &fVslider6, FAUSTFLOAT(20.0f), FAUSTFLOAT(20.0f), FAUSTFLOAT(20000.0f), FAUSTFLOAT(1.0f));
		ui_interface->addCheckButton("hipOnOff", &fCheckbox0);
		ui_interface->addVerticalSlider("hipQ", &fVslider5, FAUSTFLOAT(1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(10.0f), FAUSTFLOAT(0.100000001f));
		ui_interface->declare(&fVslider4, "scale", "log");
		ui_interface->addVerticalSlider("lopCutoff", &fVslider4, FAUSTFLOAT(20000.0f), FAUSTFLOAT(20.0f), FAUSTFLOAT(20000.0f), FAUSTFLOAT(1.0f));
		ui_interface->addCheckButton("lopOnOff", &fCheckbox1);
		ui_interface->addVerticalSlider("lopQ", &fVslider0, FAUSTFLOAT(1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(10.0f), FAUSTFLOAT(0.100000001f));
		ui_interface->addVerticalSlider("offset", &fVslider2, FAUSTFLOAT(0.100000001f), FAUSTFLOAT(-1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00999999978f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = float(fCheckbox0);
		float fSlow1 = float(fCheckbox1);
		float fSlow2 = float(((fSlow0 == 0.0f) * (fSlow1 == 0.0f)));
		float fSlow3 = (fConst1 * float(fVslider0));
		float fSlow4 = float(fVslider1);
		float fSlow5 = float(fVslider2);
		float fSlow6 = std::pow(10.0f, (2.0f * float(fVslider3)));
		int iSlow7 = ((fSlow0 == 1.0f) * (fSlow1 == 1.0f));
		float fSlow8 = float((iSlow7 == 0));
		float fSlow9 = ((fSlow1 * fSlow6) * fSlow8);
		float fSlow10 = (fConst1 * float(fVslider4));
		float fSlow11 = (fConst1 * float(fVslider5));
		float fSlow12 = ((fSlow0 * fSlow6) * fSlow8);
		float fSlow13 = (fConst1 * float(fVslider6));
		float fSlow14 = (fSlow6 * float(iSlow7));
		for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
			float fTemp0 = float(input0[i0]);
			fRec0[0] = (fSlow3 + (fConst2 * fRec0[1]));
			float fTemp1 = (fRec0[0] + -1.0f);
			float fTemp2 = std::pow(10.0f, (0.0500000007f * (0.0f - (0.349999994f * std::fabs(((10.0f * ((0.111111112f * fTemp1) + -1.0f)) + 30.0f))))));
			float fTemp3 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow5 + (fSlow9 * fTemp0))));
			fRec2[0] = (fSlow10 + (fConst2 * fRec2[1]));
			float fTemp4 = std::tan((fConst3 * std::max<float>(20.0f, fRec2[0])));
			float fTemp5 = (1.0f / fTemp4);
			float fTemp6 = (1.0f / fRec0[0]);
			float fTemp7 = (((fTemp5 - fTemp6) / fTemp4) + 1.0f);
			float fTemp8 = (1.0f - (1.0f / HipLopFilter_faustpower2_f(fTemp4)));
			float fTemp9 = (((fTemp6 + fTemp5) / fTemp4) + 1.0f);
			fRec1[0] = ((fSlow4 * (fTemp3 * (1.0f - (0.333333343f * HipLopFilter_faustpower2_f(fTemp3))))) - (((fRec1[2] * fTemp7) + (2.0f * (fRec1[1] * fTemp8))) / fTemp9));
			float fTemp10 = (0.0f - ((0.0333333351f * fTemp1) + -1.0f));
			float fTemp11 = ((fTemp2 * (fRec1[2] + (fRec1[0] + (2.0f * fRec1[1])))) * fTemp10);
			float fTemp12 = std::fabs((fTemp11 / fTemp9));
			float fTemp13 = ((fRec4[1] > fTemp12) ? fConst7 : fConst6);
			fRec5[0] = ((fRec5[1] * fTemp13) + (fTemp12 * (1.0f - fTemp13)));
			fRec4[0] = fRec5[0];
			fRec3[0] = ((fConst4 * fRec3[1]) + (fConst5 * (0.0f - (0.666666687f * std::max<float>(((20.0f * std::log10(fRec4[0])) + 16.0f), 0.0f)))));
			fRec6[0] = (fSlow11 + (fConst2 * fRec6[1]));
			float fTemp14 = (fRec6[0] + -1.0f);
			float fTemp15 = std::pow(10.0f, (0.0500000007f * (0.0f - (0.349999994f * std::fabs(((10.0f * ((0.111111112f * fTemp14) + -1.0f)) + 30.0f))))));
			float fTemp16 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow5 + (fSlow12 * fTemp0))));
			float fTemp17 = (fSlow4 * (fTemp16 * (1.0f - (0.333333343f * HipLopFilter_faustpower2_f(fTemp16)))));
			fRec8[0] = (fSlow13 + (fConst2 * fRec8[1]));
			float fTemp18 = std::tan((fConst3 * std::max<float>(20.0f, fRec8[0])));
			float fTemp19 = (1.0f / fTemp18);
			float fTemp20 = (1.0f / fRec6[0]);
			float fTemp21 = (((fTemp19 - fTemp20) / fTemp18) + 1.0f);
			float fTemp22 = (1.0f - (1.0f / HipLopFilter_faustpower2_f(fTemp18)));
			float fTemp23 = (((fTemp20 + fTemp19) / fTemp18) + 1.0f);
			fRec7[0] = (fTemp17 - (((fRec7[2] * fTemp21) + (2.0f * (fRec7[1] * fTemp22))) / fTemp23));
			float fTemp24 = (0.0f - ((0.0333333351f * fTemp14) + -1.0f));
			float fTemp25 = ((fTemp15 * (fTemp17 - ((fRec7[2] + (fRec7[0] + (2.0f * fRec7[1]))) / fTemp23))) * fTemp24);
			float fTemp26 = std::fabs(fTemp25);
			float fTemp27 = ((fRec10[1] > fTemp26) ? fConst7 : fConst6);
			fRec11[0] = ((fRec11[1] * fTemp27) + (fTemp26 * (1.0f - fTemp27)));
			fRec10[0] = fRec11[0];
			fRec9[0] = ((fConst4 * fRec9[1]) + (fConst5 * (0.0f - (0.666666687f * std::max<float>(((20.0f * std::log10(fRec10[0])) + 16.0f), 0.0f)))));
			float fTemp28 = (fTemp2 * fTemp10);
			float fTemp29 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow5 + (fSlow14 * fTemp0))));
			fRec13[0] = ((fSlow4 * (fTemp29 * (1.0f - (0.333333343f * HipLopFilter_faustpower2_f(fTemp29))))) - (((fTemp7 * fRec13[2]) + (2.0f * (fTemp8 * fRec13[1]))) / fTemp9));
			float fTemp30 = ((fTemp28 * (fRec13[2] + (fRec13[0] + (2.0f * fRec13[1])))) / fTemp9);
			fRec12[0] = (fTemp30 - (((fTemp21 * fRec12[2]) + (2.0f * (fTemp22 * fRec12[1]))) / fTemp23));
			float fTemp31 = (fTemp24 * (0.0f - (fTemp15 * (((fRec12[2] + (fRec12[0] + (2.0f * fRec12[1]))) / fTemp23) - fTemp30))));
			float fTemp32 = std::fabs(fTemp31);
			float fTemp33 = ((fRec15[1] > fTemp32) ? fConst7 : fConst6);
			fRec16[0] = ((fRec16[1] * fTemp33) + (fTemp32 * (1.0f - fTemp33)));
			fRec15[0] = fRec16[0];
			fRec14[0] = ((fConst4 * fRec14[1]) + (fConst5 * (0.0f - (0.666666687f * std::max<float>(((20.0f * std::log10(fRec15[0])) + 16.0f), 0.0f)))));
			output0[i0] = FAUSTFLOAT((((fSlow2 * fTemp0) + (17.0f * (((fTemp11 * std::pow(10.0f, (0.0500000007f * fRec3[0]))) / fTemp9) + (fTemp25 * std::pow(10.0f, (0.0500000007f * fRec9[0])))))) + (39.0999985f * (fTemp31 * std::pow(10.0f, (0.0500000007f * fRec14[0]))))));
			float fTemp34 = float(input1[i0]);
			float fTemp35 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow5 + (fSlow9 * fTemp34))));
			fRec17[0] = ((fSlow4 * (fTemp35 * (1.0f - (0.333333343f * HipLopFilter_faustpower2_f(fTemp35))))) - (((fTemp7 * fRec17[2]) + (2.0f * (fTemp8 * fRec17[1]))) / fTemp9));
			float fTemp36 = (fTemp28 * (fRec17[2] + (fRec17[0] + (2.0f * fRec17[1]))));
			float fTemp37 = std::fabs((fTemp36 / fTemp9));
			float fTemp38 = ((fRec19[1] > fTemp37) ? fConst7 : fConst6);
			fRec20[0] = ((fRec20[1] * fTemp38) + (fTemp37 * (1.0f - fTemp38)));
			fRec19[0] = fRec20[0];
			fRec18[0] = ((fConst4 * fRec18[1]) + (fConst5 * (0.0f - (0.666666687f * std::max<float>(((20.0f * std::log10(fRec19[0])) + 16.0f), 0.0f)))));
			float fTemp39 = (fTemp15 * fTemp24);
			float fTemp40 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow5 + (fSlow12 * fTemp34))));
			float fTemp41 = (fSlow4 * (fTemp40 * (1.0f - (0.333333343f * HipLopFilter_faustpower2_f(fTemp40)))));
			fRec21[0] = (fTemp41 - (((fTemp21 * fRec21[2]) + (2.0f * (fTemp22 * fRec21[1]))) / fTemp23));
			float fTemp42 = (fTemp39 * (fTemp41 - ((fRec21[2] + (fRec21[0] + (2.0f * fRec21[1]))) / fTemp23)));
			float fTemp43 = std::fabs(fTemp42);
			float fTemp44 = ((fRec23[1] > fTemp43) ? fConst7 : fConst6);
			fRec24[0] = ((fRec24[1] * fTemp44) + (fTemp43 * (1.0f - fTemp44)));
			fRec23[0] = fRec24[0];
			fRec22[0] = ((fConst4 * fRec22[1]) + (fConst5 * (0.0f - (0.666666687f * std::max<float>(((20.0f * std::log10(fRec23[0])) + 16.0f), 0.0f)))));
			float fTemp45 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow5 + (fSlow14 * fTemp34))));
			fRec25[0] = ((fSlow4 * (fTemp45 * (1.0f - (0.333333343f * HipLopFilter_faustpower2_f(fTemp45))))) - (((fTemp7 * fRec25[2]) + (2.0f * (fTemp8 * fRec25[1]))) / fTemp9));
			float fTemp46 = ((fTemp28 * (fRec25[2] + (fRec25[0] + (2.0f * fRec25[1])))) / fTemp9);
			fRec26[0] = (fTemp46 - (((fTemp21 * fRec26[2]) + (2.0f * (fTemp22 * fRec26[1]))) / fTemp23));
			float fTemp47 = (fTemp39 * (fTemp46 - ((fRec26[2] + (fRec26[0] + (2.0f * fRec26[1]))) / fTemp23)));
			float fTemp48 = std::fabs(fTemp47);
			float fTemp49 = ((fRec28[1] > fTemp48) ? fConst7 : fConst6);
			fRec29[0] = ((fRec29[1] * fTemp49) + (fTemp48 * (1.0f - fTemp49)));
			fRec28[0] = fRec29[0];
			fRec27[0] = ((fConst4 * fRec27[1]) + (fConst5 * (0.0f - (0.666666687f * std::max<float>(((20.0f * std::log10(fRec28[0])) + 16.0f), 0.0f)))));
			output1[i0] = FAUSTFLOAT((((fSlow2 * fTemp34) + (17.0f * (((fTemp36 * std::pow(10.0f, (0.0500000007f * fRec18[0]))) / fTemp9) + (fTemp42 * std::pow(10.0f, (0.0500000007f * fRec22[0])))))) + (39.0999985f * (fTemp47 * std::pow(10.0f, (0.0500000007f * fRec27[0]))))));
			fRec0[1] = fRec0[0];
			fRec2[1] = fRec2[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fRec5[1] = fRec5[0];
			fRec4[1] = fRec4[0];
			fRec3[1] = fRec3[0];
			fRec6[1] = fRec6[0];
			fRec8[1] = fRec8[0];
			fRec7[2] = fRec7[1];
			fRec7[1] = fRec7[0];
			fRec11[1] = fRec11[0];
			fRec10[1] = fRec10[0];
			fRec9[1] = fRec9[0];
			fRec13[2] = fRec13[1];
			fRec13[1] = fRec13[0];
			fRec12[2] = fRec12[1];
			fRec12[1] = fRec12[0];
			fRec16[1] = fRec16[0];
			fRec15[1] = fRec15[0];
			fRec14[1] = fRec14[0];
			fRec17[2] = fRec17[1];
			fRec17[1] = fRec17[0];
			fRec20[1] = fRec20[0];
			fRec19[1] = fRec19[0];
			fRec18[1] = fRec18[0];
			fRec21[2] = fRec21[1];
			fRec21[1] = fRec21[0];
			fRec24[1] = fRec24[0];
			fRec23[1] = fRec23[0];
			fRec22[1] = fRec22[0];
			fRec25[2] = fRec25[1];
			fRec25[1] = fRec25[0];
			fRec26[2] = fRec26[1];
			fRec26[1] = fRec26[0];
			fRec29[1] = fRec29[0];
			fRec28[1] = fRec28[0];
			fRec27[1] = fRec27[0];
		}
	}

};

#endif
