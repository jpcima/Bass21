#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
/* ------------------------------------------------------------
author: "JPC"
license: "AGPL-3.0-or-later"
name: "Bass21Faust"
Code generated with Faust 2.37.3 (https://faust.grame.fr)
Compilation options: -lang cpp -inpl -mapp -es 1 -double -ftz 0
------------------------------------------------------------ */

#ifndef  __Bass21EQFaustDSP_H__
#define  __Bass21EQFaustDSP_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

static double Bass21EQFaustDSP_faustpower2_f(double value) {
	return (value * value);
}

#ifndef FAUSTCLASS
#define FAUSTCLASS Bass21EQFaustDSP
#endif

#ifdef __APPLE__
#define exp10f __exp10f
#define exp10 __exp10
#endif


//[Before:class]
class Bass21EQFaustDSP {
	//[Begin:class]


 private:

	int fSampleRate;
	double fConst0;
	FAUSTFLOAT fHslider0;
	double fConst1;
	FAUSTFLOAT fCheckbox0;
	double fRec1[2];
	double fConst2;
	double fConst3;
	FAUSTFLOAT fHslider1;
	double fRec2[2];
	double fConst4;
	double fConst5;
	double fConst6;
	double fRec0[7];
	double fConst7;
	double fConst8;
	double fConst9;
	double fConst10;

 public:


	static constexpr int getNumInputs() {
		return 1;
	}
	static constexpr int getNumOutputs() {
		return 1;
	}

	static void classInit(int sample_rate) {
		//[Begin:classInit]
		//[End:classInit]
	}

	void instanceConstants(int sample_rate) {
		//[Begin:instanceConstants]
		fSampleRate = sample_rate;
		fConst0 = double(fSampleRate);
		fConst1 = std::exp((0.0 - (138.19999999999999 / fConst0)));
		fConst2 = Bass21EQFaustDSP_faustpower2_f(fConst0);
		fConst3 = (1.8399743999999998e-15 * fConst0);
		fConst4 = (64.0 * fConst0);
		fConst5 = (6.1332480000000004e-15 * fConst2);
		fConst6 = (3.066624e-16 * fConst0);
		fConst7 = (1.5487999999999999e-10 * fConst0);
		fConst8 = (6.1951999999999995e-10 * fConst0);
		fConst9 = (7.7439999999999993e-10 * fConst0);
		fConst10 = (64.0 * fConst2);
		//[End:instanceConstants]
	}

	void instanceResetUserInterface() {
		//[Begin:instanceResetUserInterface]
		fHslider0 = FAUSTFLOAT(0.5);
		fCheckbox0 = FAUSTFLOAT(0.0);
		fHslider1 = FAUSTFLOAT(0.5);
		//[End:instanceResetUserInterface]
	}

	void instanceClear() {
		//[Begin:instanceClear]
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec1[l0] = 0.0;
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec2[l1] = 0.0;
		}
		for (int l2 = 0; (l2 < 7); l2 = (l2 + 1)) {
			fRec0[l2] = 0.0;
		}
		//[End:instanceClear]
	}

	void init(int sample_rate) {
		//[Begin:init]
		classInit(sample_rate);
		instanceInit(sample_rate);
		//[End:init]
	}
	void instanceInit(int sample_rate) {
		//[Begin:instanceInit]
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
		//[End:instanceInit]
	}


	int getSampleRate() {
		return fSampleRate;
	}


	void compute(int count, FAUSTFLOAT const* const* inputs, FAUSTFLOAT* const* outputs) {
		//[Begin:compute]
		FAUSTFLOAT const* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		double fSlow0 = double(fCheckbox0);
		double fSlow1 = (fConst1 * double(((fSlow0 == fSlow0) | (fSlow0 == 0.0))));
		double fSlow2 = (1.0 - fSlow1);
		double fSlow3 = (double(fHslider0) * fSlow2);
		double fSlow4 = (double(fHslider1) * fSlow2);
		for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
			double fTemp0 = double(input0[i0]);
			fRec1[0] = (fSlow3 + (fSlow1 * fRec1[1]));
			double fTemp1 = (1.0 - fRec1[0]);
			double fTemp2 = (1120000.0 - (100000.0 * fTemp1));
			double fTemp3 = (6.0 * fTemp2);
			double fTemp4 = (fTemp1 * (0.0 - fRec1[0]));
			fRec2[0] = (fSlow4 + (fSlow1 * fRec2[1]));
			double fTemp5 = (1.0 - fRec2[0]);
			double fTemp6 = (fTemp5 * (1.0 - fTemp5));
			double fTemp7 = (fTemp4 * ((1000.0 * fTemp6) + 33.0));
			double fTemp8 = (fConst3 * fTemp7);
			double fTemp9 = Bass21EQFaustDSP_faustpower2_f(fTemp5);
			double fTemp10 = (((fTemp1 * ((((fTemp1 * ((fTemp5 * ((5.017434399999999e-09 * fTemp5) + -6.468955239999999e-09)) + -1.7117815307999998e-10)) - (5.017434399999999e-09 * fTemp9)) + (6.468955239999999e-09 * fTemp5)) + 1.7117815307999998e-10)) + (2.1780000000000002e-12 * fTemp6)) + 7.1874e-14);
			double fTemp11 = (128.0 * fTemp10);
			double fTemp12 = (((fTemp1 * ((((fTemp1 * ((fTemp5 * ((2.7857060000000002e-05 * fTemp5) + -3.6639635999999999e-05)) + -8.8882818023999985e-06)) - (2.7857060000000002e-05 * fTemp9)) + (3.6639635999999999e-05 * fTemp5)) + 8.8882818023999985e-06)) + (fTemp5 * (2.9348242e-06 - (2.2750420000000001e-06 * fTemp5)))) + 7.7623121400000002e-08);
			double fTemp13 = (32.0 * fTemp12);
			double fTemp14 = (((fTemp1 * ((((fTemp1 * ((0.10000000000000001 * fTemp5) + -44.752179999999996)) + (0.10000000000000001 * fTemp9)) - (2.2000000000000002 * fTemp5)) + 56.405362199999999)) + (fTemp5 * (2.097 - (1.1200000000000001 * fTemp5)))) + 9.7002253599999992);
			double fTemp15 = (8.0 * fTemp14);
			double fTemp16 = ((fTemp1 * (11210.1 - (1320.0 * fTemp1))) + 6094.8800000000001);
			double fTemp17 = (8.0 * fTemp16);
			double fTemp18 = (15.0 * fTemp2);
			double fTemp19 = (160.0 * fTemp10);
			double fTemp20 = (fConst4 * (0.0 - (7.1874000000000004e-17 * fTemp7)));
			double fTemp21 = (16.0 * fTemp12);
			double fTemp22 = (((fTemp1 * ((((fTemp1 * ((fTemp5 * ((0.0012199999999999999 * fTemp5) + -0.0111287)) + -0.048826257259999999)) - (0.0112167 * fTemp9)) + (0.021125399999999999 * fTemp5)) + 0.049156148359999999)) + (fTemp5 * (0.0057706010000000002 - (0.00347796 * fTemp5)))) + 0.003730485099);
			double fTemp23 = (24.0 * fTemp22);
			double fTemp24 = (4.0 * fTemp14);
			double fTemp25 = (10.0 * fTemp16);
			double fTemp26 = (32.0 * fTemp10);
			double fTemp27 = (fConst6 * fTemp7);
			double fTemp28 = (8.0 * fTemp22);
			double fTemp29 = (2.0 * fTemp16);
			double fTemp30 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fTemp26 - fTemp27)) + fTemp21)) + fTemp28)) + fTemp24)) + fTemp29)) + fTemp2);
			fRec0[0] = (fTemp0 - (((((((fRec0[1] * (fTemp3 + (fConst0 * ((fConst0 * ((fConst2 * ((fConst0 * (fTemp8 - fTemp11)) - fTemp13)) + fTemp15)) + fTemp17)))) + (fRec0[2] * (fTemp18 + (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fTemp19 + fTemp20)) - fTemp21)) - fTemp23)) - fTemp24)) + fTemp25))))) + (fRec0[3] * ((20.0 * fTemp2) + (fConst2 * ((fConst2 * ((64.0 * fTemp12) + (fConst5 * fTemp7))) - (16.0 * fTemp14)))))) + (fRec0[4] * (fTemp18 + (fConst0 * ((fConst0 * ((fConst0 * (fTemp23 + (fConst0 * ((fConst0 * (fTemp20 - fTemp19)) - fTemp21)))) - fTemp24)) - fTemp25))))) + (fRec0[5] * (fTemp3 + (fConst0 * ((fConst0 * (fTemp15 + (fConst2 * ((fConst0 * (fTemp11 + fTemp8)) - fTemp13)))) - fTemp17))))) + (fRec0[6] * ((fConst0 * ((fConst0 * (fTemp24 + (fConst0 * ((fConst0 * (fTemp21 + (fConst0 * (0.0 - (fTemp26 + fTemp27))))) - fTemp28)))) - fTemp29)) + fTemp2))) / fTemp30));
			double fTemp31 = (((fTemp1 * ((((fTemp1 * ((fTemp5 * (1.3200000000000001e-05 - (2.1999999999999999e-05 * fTemp5))) + 1.6137439999999998e-05)) + (2.1999999999999999e-05 * fTemp9)) - (1.3200000000000001e-05 * fTemp5)) + -1.6137439999999998e-05)) + (fTemp5 * ((2.2000000000000001e-06 * fTemp5) + -1.5400000000000001e-06))) + -7.3259999999999998e-07);
			double fTemp32 = (16.0 * fTemp31);
			double fTemp33 = (fTemp4 * ((fTemp5 * (700.0 - (1000.0 * fTemp5))) + 333.0));
			double fTemp34 = (fConst7 * fTemp33);
			double fTemp35 = (((fTemp1 * ((((fTemp1 * (0.047092000000000002 - (0.01 * fTemp5))) - (0.01 * fTemp9)) + (0.02 * fTemp5)) + -0.046761999999999998)) + (fTemp5 * ((0.010999999999999999 * fTemp5) + -0.0086999999999999994))) + -0.0056682);
			double fTemp36 = (8.0 * fTemp35);
			double fTemp37 = ((fTemp1 * ((32.0 * fTemp1) + -21.34)) + -16.225999999999999);
			double fTemp38 = (4.0 * fTemp37);
			double fTemp39 = ((10000.0 * fTemp1) + -11000.0);
			double fTemp40 = (2.0 * fTemp39);
			double fTemp41 = (32.0 * fTemp31);
			double fTemp42 = (fConst8 * fTemp33);
			double fTemp43 = (8.0 * fTemp37);
			double fTemp44 = (8.0 * fTemp39);
			double fTemp45 = (fConst9 * fTemp33);
			double fTemp46 = (24.0 * fTemp35);
			double fTemp47 = (10.0 * fTemp39);
			output0[i0] = FAUSTFLOAT((fConst0 * ((((((((fRec0[0] * ((fConst0 * ((fConst0 * ((fConst0 * (fTemp32 + fTemp34)) + fTemp36)) + fTemp38)) + fTemp40)) + (fRec0[1] * ((fConst0 * ((fConst2 * (0.0 - (fTemp41 + fTemp42))) + fTemp43)) + fTemp44))) + (fRec0[2] * ((fConst0 * ((fConst0 * ((fConst0 * (fTemp45 - fTemp32)) - fTemp46)) - fTemp38)) + fTemp47))) + (fConst0 * (fRec0[3] * ((fConst10 * fTemp31) - (16.0 * fTemp37))))) + (fRec0[4] * ((fConst0 * ((fConst0 * (fTemp46 + (fConst0 * (0.0 - (fTemp32 + fTemp45))))) - fTemp38)) - fTemp47))) + (fRec0[5] * ((fConst0 * (fTemp43 + (fConst2 * (fTemp42 - fTemp41)))) - fTemp44))) + (fRec0[6] * ((fConst0 * (fTemp38 + (fConst0 * ((fConst0 * (fTemp32 - fTemp34)) - fTemp36)))) - fTemp40))) / fTemp30)));
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			for (int j0 = 6; (j0 > 0); j0 = (j0 - 1)) {
				fRec0[j0] = fRec0[(j0 - 1)];
			}
		}
		//[End:compute]
	}


	FAUSTFLOAT getBegin() const { return fCheckbox0; }
	void setBegin(FAUSTFLOAT value) { fCheckbox0 = value; }

	FAUSTFLOAT getBass() const { return fHslider0; }
	void setBass(FAUSTFLOAT value) { fHslider0 = value; }

	FAUSTFLOAT getTreble() const { return fHslider1; }
	void setTreble(FAUSTFLOAT value) { fHslider1 = value; }

	//[End:class]
};
//[After:class]


#endif
#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif
#undef FAUSTFLOAT
#undef FAUSTCLASS
