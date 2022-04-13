/* ------------------------------------------------------------
name: "test"
Code generated with Faust 2.37.3 (https://faust.grame.fr)
Compilation options: -lang cpp -es 1 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __Test_H__
#define  __Test_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>


#ifndef FAUSTCLASS 
#define FAUSTCLASS Test
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class Test : public dsp {
	
 private:
	
	int fSampleRate;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fVslider0;
	float fRec0[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-lang cpp -es 1 -single -ftz 0");
		m->declare("filename", "test.dsp");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.3");
		m->declare("name", "test");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.1");
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
		fConst1 = (1.0f / fConst0);
	}
	
	virtual void instanceResetUserInterface() {
		fVslider0 = FAUSTFLOAT(220.0f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec0[l0] = 0.0f;
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
	
	virtual Test* clone() {
		return new Test();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("test");
		ui_interface->addVerticalSlider("freq", &fVslider0, FAUSTFLOAT(220.0f), FAUSTFLOAT(40.0f), FAUSTFLOAT(1000.0f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = std::max<float>(1.1920929e-07f, std::fabs(float(fVslider0)));
		float fSlow1 = (fConst1 * fSlow0);
		float fSlow2 = (1.0f - (fConst0 / fSlow0));
		for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
			float fTemp0 = (fSlow1 + (fRec0[1] + -1.0f));
			int iTemp1 = (fTemp0 < 0.0f);
			float fTemp2 = (fSlow1 + fRec0[1]);
			fRec0[0] = (iTemp1 ? fTemp2 : fTemp0);
			float fThen1 = (fSlow1 + (fRec0[1] + (fSlow2 * fTemp0)));
			float fRec1 = (iTemp1 ? fTemp2 : fThen1);
			float fTemp3 = ((2.0f * fRec1) + -1.0f);
			output0[i0] = FAUSTFLOAT(fTemp3);
			output1[i0] = FAUSTFLOAT(fTemp3);
			fRec0[1] = fRec0[0];
		}
	}

};

#endif
