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

#ifndef  __Bass21FaustDSP_H__
#define  __Bass21FaustDSP_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

/* link with : "" */
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

class Bass21FaustDSPSIG0 {

  private:

	int iRec0[2];

  public:

	int getNumInputsBass21FaustDSPSIG0() {
		return 0;
	}
	int getNumOutputsBass21FaustDSPSIG0() {
		return 1;
	}

	void instanceInitBass21FaustDSPSIG0(int sample_rate) {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iRec0[l0] = 0;
		}
	}

	void fillBass21FaustDSPSIG0(int count, double* table) {
		for (int i1 = 0; (i1 < count); i1 = (i1 + 1)) {
			iRec0[0] = (iRec0[1] + 1);
			table[i1] = double(tanh(double(((0.062992125984251968 * double((iRec0[0] + -1))) + -4.0))));
			iRec0[1] = iRec0[0];
		}
	}

};

static Bass21FaustDSPSIG0* newBass21FaustDSPSIG0() { return (Bass21FaustDSPSIG0*)new Bass21FaustDSPSIG0(); }
static void deleteBass21FaustDSPSIG0(Bass21FaustDSPSIG0* dsp) { delete dsp; }

static double ftbl0Bass21FaustDSPSIG0[128];
static double Bass21FaustDSP_faustpower3_f(double value) {
	return ((value * value) * value);
}
static double Bass21FaustDSP_faustpower2_f(double value) {
	return (value * value);
}

#ifndef FAUSTCLASS
#define FAUSTCLASS Bass21FaustDSP
#endif

#ifdef __APPLE__
#define exp10f __exp10f
#define exp10 __exp10
#endif


//[Before:class]
class Bass21FaustDSP {
	//[Begin:class]


 private:

	int fSampleRate;
	double fConst0;
	double fConst2;
	double fConst3;
	double fConst5;
	double fConst6;
	double fConst8;
	double fConst10;
	double fConst12;
	double fConst13;
	double fConst14;
	double fConst15;
	FAUSTFLOAT fHslider0;
	double fRec12[2];
	double fConst20;
	double fConst22;
	double fConst25;
	double fRec11[4];
	double fConst27;
	double fConst28;
	double fConst29;
	double fConst30;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fCheckbox0;
	double fRec13[2];
	double fVec0[2];
	double fVec1[2];
	double fConst31;
	double fConst33;
	double fVec2[2];
	double fRec10[2];
	double fRec9[2];
	FAUSTFLOAT fHslider2;
	double fRec14[2];
	double fConst34;
	double fVec3[2];
	double fVec4[2];
	double fVec5[2];
	double fRec8[2];
	double fRec7[2];
	double fConst35;
	double fConst37;
	double fConst38;
	double fConst39;
	double fRec6[4];
	double fConst40;
	double fConst41;
	double fConst42;
	double fVec6[2];
	double fVec7[2];
	double fConst43;
	double fConst44;
	double fRec5[2];
	double fRec4[2];
	double fVec8[2];
	double fConst45;
	double fRec3[2];
	double fRec2[2];
	FAUSTFLOAT fHslider3;
	double fRec15[2];
	FAUSTFLOAT fHslider4;
	double fRec16[2];
	FAUSTFLOAT fHslider5;
	double fRec17[2];
	double fConst46;
	FAUSTFLOAT fHslider6;
	double fRec18[2];
	double fConst47;
	double fConst48;
	double fConst49;
	double fRec1[7];
	double fConst50;
	double fConst51;
	double fConst52;
	double fConst53;

 public:


	static constexpr int getNumInputs() {
		return 1;
	}
	static constexpr int getNumOutputs() {
		return 1;
	}

	static void classInit(int sample_rate) {
		//[Begin:classInit]
		Bass21FaustDSPSIG0* sig0 = newBass21FaustDSPSIG0();
		sig0->instanceInitBass21FaustDSPSIG0(sample_rate);
		sig0->fillBass21FaustDSPSIG0(128, ftbl0Bass21FaustDSPSIG0);
		deleteBass21FaustDSPSIG0(sig0);
		//[End:classInit]
	}

	void instanceConstants(int sample_rate) {
		//[Begin:instanceConstants]
		fSampleRate = sample_rate;
		fConst0 = double(fSampleRate);
		double fConst1 = (1.13256e-08 * fConst0);
		fConst2 = (1.0 / ((fConst0 * (fConst1 + 0.000144)) + 1.0));
		fConst3 = ((fConst0 * (fConst1 + -0.000144)) + 1.0);
		double fConst4 = (5.641504e-07 * fConst0);
		fConst5 = (1.0 / ((fConst0 * (fConst4 + 0.0029236000000000002)) + 1.0));
		fConst6 = ((fConst0 * (fConst4 + -0.0029236000000000002)) + 1.0);
		double fConst7 = ((fConst0 * ((fConst0 * ((3.5923641600000005e-07 * fConst0) + 0.0036168492799999994)) + 118.46632000000001)) + 32000.0);
		fConst8 = (((fConst0 * (fConst4 + -0.00085559999999999998)) + 1.0) / fConst7);
		double fConst9 = (20.68 * fConst0);
		fConst10 = (fConst9 + 22000.0);
		double fConst11 = (4.1229055999999999e-10 * fConst0);
		fConst12 = (1.0 / ((fConst0 * ((fConst0 * (fConst11 + 5.3921471999999997e-06)) + 0.0065295999999999991)) + 1.0));
		fConst13 = ((fConst0 * ((fConst0 * (fConst11 + 2.8110719999999996e-07)) + 0.0021295999999999997)) + 1.0);
		fConst14 = std::exp((0.0 - (138.19999999999999 / fConst0)));
		fConst15 = (1.0 - fConst14);
		double fConst16 = Bass21FaustDSP_faustpower3_f(fConst0);
		double fConst17 = (0.0 - (24.0 * fConst16));
		double fConst18 = (5.1536319999999999e-11 * fConst17);
		double fConst19 = (5.3921471999999997e-06 * fConst0);
		fConst20 = ((fConst18 + (fConst0 * (0.0065295999999999991 - fConst19))) + 3.0);
		double fConst21 = (1.2368716799999999e-09 * fConst0);
		fConst22 = ((fConst0 * ((fConst0 * (fConst21 + -5.3921471999999997e-06)) + -0.0065295999999999991)) + 3.0);
		double fConst23 = (0.0 - (8.0 * fConst16));
		double fConst24 = (5.1536319999999999e-11 * fConst23);
		fConst25 = ((fConst24 + (fConst0 * (fConst19 + -0.0065295999999999991))) + 1.0);
		double fConst26 = (2.8110719999999996e-07 * fConst0);
		fConst27 = ((fConst18 + (fConst0 * (0.0021295999999999997 - fConst26))) + 3.0);
		fConst28 = ((fConst0 * ((fConst0 * (fConst21 + -2.8110719999999996e-07)) + -0.0021295999999999997)) + 3.0);
		fConst29 = ((fConst24 + (fConst0 * (fConst26 + -0.0021295999999999997))) + 1.0);
		fConst30 = (2.9040000000000001e-12 * fConst0);
		fConst31 = Bass21FaustDSP_faustpower2_f(fConst0);
		double fConst32 = (0.0 - (8.0 * fConst31));
		fConst33 = (7.2600000000000004e-13 * fConst32);
		fConst34 = (0.00014520000000000001 * fConst0);
		fConst35 = (1.0 / fConst7);
		double fConst36 = (0.0036168492799999994 * fConst0);
		fConst37 = (((4.4904552000000007e-08 * fConst17) + (fConst0 * (118.46632000000001 - fConst36))) + 96000.0);
		fConst38 = ((fConst0 * ((fConst0 * ((1.0777092480000002e-06 * fConst0) + -0.0036168492799999994)) + -118.46632000000001)) + 96000.0);
		fConst39 = (((4.4904552000000007e-08 * fConst23) + (fConst0 * (fConst36 + -118.46632000000001))) + 32000.0);
		fConst40 = (fConst9 + 66000.0);
		fConst41 = (66000.0 - fConst9);
		fConst42 = (22000.0 - fConst9);
		fConst43 = ((1.410376e-07 * fConst32) + 2.0);
		fConst44 = (((fConst0 * (fConst4 + 0.00085559999999999998)) + 1.0) / fConst7);
		fConst45 = ((2.8314e-09 * fConst32) + 2.0);
		fConst46 = (1.8399743999999998e-15 * fConst0);
		fConst47 = (64.0 * fConst0);
		fConst48 = (6.1332480000000004e-15 * fConst31);
		fConst49 = (3.066624e-16 * fConst0);
		fConst50 = (1.5487999999999999e-10 * fConst0);
		fConst51 = (6.1951999999999995e-10 * fConst0);
		fConst52 = (7.7439999999999993e-10 * fConst0);
		fConst53 = (64.0 * fConst31);
		//[End:instanceConstants]
	}

	void instanceResetUserInterface() {
		//[Begin:instanceResetUserInterface]
		fHslider0 = FAUSTFLOAT(0.5);
		fHslider1 = FAUSTFLOAT(0.5);
		fCheckbox0 = FAUSTFLOAT(0.0);
		fHslider2 = FAUSTFLOAT(0.5);
		fHslider3 = FAUSTFLOAT(0.5);
		fHslider4 = FAUSTFLOAT(0.5);
		fHslider5 = FAUSTFLOAT(0.5);
		fHslider6 = FAUSTFLOAT(0.5);
		//[End:instanceResetUserInterface]
	}

	void instanceClear() {
		//[Begin:instanceClear]
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec12[l1] = 0.0;
		}
		for (int l2 = 0; (l2 < 4); l2 = (l2 + 1)) {
			fRec11[l2] = 0.0;
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec13[l3] = 0.0;
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fVec0[l4] = 0.0;
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fVec1[l5] = 0.0;
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fVec2[l6] = 0.0;
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec10[l7] = 0.0;
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec9[l8] = 0.0;
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec14[l9] = 0.0;
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fVec3[l10] = 0.0;
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fVec4[l11] = 0.0;
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fVec5[l12] = 0.0;
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec8[l13] = 0.0;
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec7[l14] = 0.0;
		}
		for (int l15 = 0; (l15 < 4); l15 = (l15 + 1)) {
			fRec6[l15] = 0.0;
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fVec6[l16] = 0.0;
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fVec7[l17] = 0.0;
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fRec5[l18] = 0.0;
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec4[l19] = 0.0;
		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fVec8[l20] = 0.0;
		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fRec3[l21] = 0.0;
		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fRec2[l22] = 0.0;
		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fRec15[l23] = 0.0;
		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fRec16[l24] = 0.0;
		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fRec17[l25] = 0.0;
		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fRec18[l26] = 0.0;
		}
		for (int l27 = 0; (l27 < 7); l27 = (l27 + 1)) {
			fRec1[l27] = 0.0;
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
		double fSlow0 = (fConst15 * double(fHslider0));
		double fSlow1 = double(fCheckbox0);
		double fSlow2 = (fConst14 * double(((fSlow1 == fSlow1) | (fSlow1 == 0.0))));
		double fSlow3 = (1.0 - fSlow2);
		double fSlow4 = (double(fHslider1) * fSlow3);
		double fSlow5 = (double(fHslider2) * fSlow3);
		double fSlow6 = (fConst15 * double(fHslider3));
		double fSlow7 = (fConst15 * double(fHslider4));
		double fSlow8 = (double(fHslider5) * fSlow3);
		double fSlow9 = (double(fHslider6) * fSlow3);
		for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
			double fTemp0 = double(input0[i0]);
			fRec12[0] = (fSlow0 + (fConst14 * fRec12[1]));
			double fTemp1 = (fTemp0 * fRec12[0]);
			fRec11[0] = (fTemp1 - (fConst12 * (((fConst20 * fRec11[1]) + (fConst22 * fRec11[2])) + (fConst25 * fRec11[3]))));
			double fTemp2 = ((((fConst13 * fRec11[0]) + (fConst27 * fRec11[1])) + (fConst28 * fRec11[2])) + (fConst29 * fRec11[3]));
			fRec13[0] = (fSlow4 + (fSlow2 * fRec13[1]));
			double fTemp3 = ((100000.0 * (1.0 - fRec13[0])) + 3300.0);
			double fTemp4 = (fConst30 * fTemp3);
			double fTemp5 = (1e-08 * fTemp3);
			double fTemp6 = (2.0 * (fTemp5 + 0.0033725999999999999));
			double fTemp7 = (2.0 * (fTemp5 + 7.2600000000000003e-05));
			double fTemp8 = ((fConst0 * (fTemp7 + fTemp4)) + 1.0);
			fVec0[0] = ((fTemp2 * ((fConst0 * (fTemp4 - fTemp6)) + 1.0)) / fTemp8);
			fVec1[0] = ((fConst12 * fVec0[1]) - ((fRec9[1] * ((fConst0 * (fTemp4 - fTemp7)) + 1.0)) / fTemp8));
			double fTemp9 = ((fConst33 * fTemp3) + 2.0);
			fVec2[0] = ((fTemp9 * fTemp2) / fTemp8);
			fRec10[0] = ((fVec1[1] + (fConst12 * fVec2[1])) - (((fRec10[1] * fTemp9) - (fConst12 * (fTemp2 * ((fConst0 * (fTemp4 + fTemp6)) + 1.0)))) / fTemp8));
			fRec9[0] = fRec10[0];
			double fTemp10 = std::min<double>(127.0, std::max<double>(0.0, (15.875 * (fRec9[0] + 4.0))));
			int iTemp11 = int(fTemp10);
			double fTemp12 = ftbl0Bass21FaustDSPSIG0[iTemp11];
			double fTemp13 = (fTemp12 + ((fTemp10 - double(iTemp11)) * (ftbl0Bass21FaustDSPSIG0[std::min<int>(127, int((iTemp11 + 1)))] - fTemp12)));
			fRec14[0] = (fSlow5 + (fSlow2 * fRec14[1]));
			double fTemp14 = (100000.0 * (1.0 - fRec14[0]));
			double fTemp15 = (fTemp14 + 3300.0);
			double fTemp16 = (fConst34 * fTemp15);
			double fTemp17 = (fTemp14 + fTemp16);
			double fTemp18 = (fTemp17 + 3300.0);
			fVec3[0] = ((fTemp13 * (fTemp14 + (333300.0 - fTemp16))) / fTemp18);
			fVec4[0] = (fVec3[1] - ((fRec7[1] * (fTemp14 + (3300.0 - fTemp16))) / fTemp18));
			fVec5[0] = ((fTemp13 * (fTemp14 + 333300.0)) / fTemp18);
			fRec8[0] = ((fVec4[1] + ((fTemp13 * (fTemp17 + 333300.0)) / fTemp18)) - (2.0 * (((fRec8[1] * fTemp15) / fTemp18) - fVec5[1])));
			fRec7[0] = fRec8[0];
			double fTemp19 = std::min<double>(127.0, std::max<double>(0.0, (15.875 * (fRec7[0] + 4.0))));
			int iTemp20 = int(fTemp19);
			double fTemp21 = ftbl0Bass21FaustDSPSIG0[iTemp20];
			fRec6[0] = ((fTemp21 + ((fTemp19 - double(iTemp20)) * (ftbl0Bass21FaustDSPSIG0[std::min<int>(127, int((iTemp20 + 1)))] - fTemp21))) - (fConst35 * (((fConst37 * fRec6[1]) + (fConst38 * fRec6[2])) + (fConst39 * fRec6[3]))));
			double fTemp22 = ((((fConst10 * fRec6[0]) + (fConst40 * fRec6[1])) + (fConst41 * fRec6[2])) + (fConst42 * fRec6[3]));
			fVec6[0] = fTemp22;
			fVec7[0] = (0.0 - (fConst5 * ((fConst6 * fRec4[1]) - (fConst8 * fVec6[1]))));
			fRec5[0] = (fVec7[1] - (fConst5 * ((fConst43 * (fRec5[1] - (fConst35 * fVec6[1]))) - (fConst44 * fTemp22))));
			fRec4[0] = fRec5[0];
			fVec8[0] = (0.0 - (fConst2 * ((fConst3 * fRec2[1]) - fRec4[1])));
			fRec3[0] = (fVec8[1] + (fConst2 * (fRec4[0] + ((2.0 * fRec4[1]) - (fConst45 * fRec3[1])))));
			fRec2[0] = fRec3[0];
			fRec15[0] = (fSlow6 + (fConst14 * fRec15[1]));
			fRec16[0] = (fSlow7 + (fConst14 * fRec16[1]));
			double fTemp23 = std::min<double>(127.0, std::max<double>(0.0, (15.875 * (4.0 - (2.2000000000000002 * (((fRec2[0] * fRec15[0]) + (fTemp1 * (1.0 - fRec15[0]))) * fRec16[0]))))));
			int iTemp24 = int(fTemp23);
			double fTemp25 = ftbl0Bass21FaustDSPSIG0[iTemp24];
			fRec17[0] = (fSlow8 + (fSlow2 * fRec17[1]));
			double fTemp26 = (1.0 - fRec17[0]);
			double fTemp27 = (1120000.0 - (100000.0 * fTemp26));
			double fTemp28 = (6.0 * fTemp27);
			double fTemp29 = (fTemp26 * (0.0 - fRec17[0]));
			fRec18[0] = (fSlow9 + (fSlow2 * fRec18[1]));
			double fTemp30 = (1.0 - fRec18[0]);
			double fTemp31 = (fTemp30 * (1.0 - fTemp30));
			double fTemp32 = (fTemp29 * ((1000.0 * fTemp31) + 33.0));
			double fTemp33 = (fConst46 * fTemp32);
			double fTemp34 = Bass21FaustDSP_faustpower2_f(fTemp30);
			double fTemp35 = (((fTemp26 * ((((fTemp26 * ((fTemp30 * ((5.017434399999999e-09 * fTemp30) + -6.468955239999999e-09)) + -1.7117815307999998e-10)) - (5.017434399999999e-09 * fTemp34)) + (6.468955239999999e-09 * fTemp30)) + 1.7117815307999998e-10)) + (2.1780000000000002e-12 * fTemp31)) + 7.1874e-14);
			double fTemp36 = (128.0 * fTemp35);
			double fTemp37 = (((fTemp26 * ((((fTemp26 * ((fTemp30 * ((2.7857060000000002e-05 * fTemp30) + -3.6639635999999999e-05)) + -8.8882818023999985e-06)) - (2.7857060000000002e-05 * fTemp34)) + (3.6639635999999999e-05 * fTemp30)) + 8.8882818023999985e-06)) + (fTemp30 * (2.9348242e-06 - (2.2750420000000001e-06 * fTemp30)))) + 7.7623121400000002e-08);
			double fTemp38 = (32.0 * fTemp37);
			double fTemp39 = (((fTemp26 * ((((fTemp26 * ((0.10000000000000001 * fTemp30) + -44.752179999999996)) + (0.10000000000000001 * fTemp34)) - (2.2000000000000002 * fTemp30)) + 56.405362199999999)) + (fTemp30 * (2.097 - (1.1200000000000001 * fTemp30)))) + 9.7002253599999992);
			double fTemp40 = (8.0 * fTemp39);
			double fTemp41 = ((fTemp26 * (11210.1 - (1320.0 * fTemp26))) + 6094.8800000000001);
			double fTemp42 = (8.0 * fTemp41);
			double fTemp43 = (15.0 * fTemp27);
			double fTemp44 = (160.0 * fTemp35);
			double fTemp45 = (fConst47 * (0.0 - (7.1874000000000004e-17 * fTemp32)));
			double fTemp46 = (16.0 * fTemp37);
			double fTemp47 = (((fTemp26 * ((((fTemp26 * ((fTemp30 * ((0.0012199999999999999 * fTemp30) + -0.0111287)) + -0.048826257259999999)) - (0.0112167 * fTemp34)) + (0.021125399999999999 * fTemp30)) + 0.049156148359999999)) + (fTemp30 * (0.0057706010000000002 - (0.00347796 * fTemp30)))) + 0.003730485099);
			double fTemp48 = (24.0 * fTemp47);
			double fTemp49 = (4.0 * fTemp39);
			double fTemp50 = (10.0 * fTemp41);
			double fTemp51 = (32.0 * fTemp35);
			double fTemp52 = (fConst49 * fTemp32);
			double fTemp53 = (8.0 * fTemp47);
			double fTemp54 = (2.0 * fTemp41);
			double fTemp55 = ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fTemp51 - fTemp52)) + fTemp46)) + fTemp53)) + fTemp49)) + fTemp54)) + fTemp27);
			fRec1[0] = ((fTemp25 + ((fTemp23 - double(iTemp24)) * (ftbl0Bass21FaustDSPSIG0[std::min<int>(127, int((iTemp24 + 1)))] - fTemp25))) - (((((((fRec1[1] * (fTemp28 + (fConst0 * ((fConst0 * ((fConst31 * ((fConst0 * (fTemp33 - fTemp36)) - fTemp38)) + fTemp40)) + fTemp42)))) + (fRec1[2] * (fTemp43 + (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fTemp44 + fTemp45)) - fTemp46)) - fTemp48)) - fTemp49)) + fTemp50))))) + (fRec1[3] * ((20.0 * fTemp27) + (fConst31 * ((fConst31 * ((64.0 * fTemp37) + (fConst48 * fTemp32))) - (16.0 * fTemp39)))))) + (fRec1[4] * (fTemp43 + (fConst0 * ((fConst0 * ((fConst0 * (fTemp48 + (fConst0 * ((fConst0 * (fTemp45 - fTemp44)) - fTemp46)))) - fTemp49)) - fTemp50))))) + (fRec1[5] * (fTemp28 + (fConst0 * ((fConst0 * (fTemp40 + (fConst31 * ((fConst0 * (fTemp36 + fTemp33)) - fTemp38)))) - fTemp42))))) + (fRec1[6] * ((fConst0 * ((fConst0 * (fTemp49 + (fConst0 * ((fConst0 * (fTemp46 + (fConst0 * (0.0 - (fTemp51 + fTemp52))))) - fTemp53)))) - fTemp54)) + fTemp27))) / fTemp55));
			double fTemp56 = (((fTemp26 * ((((fTemp26 * ((fTemp30 * (1.3200000000000001e-05 - (2.1999999999999999e-05 * fTemp30))) + 1.6137439999999998e-05)) + (2.1999999999999999e-05 * fTemp34)) - (1.3200000000000001e-05 * fTemp30)) + -1.6137439999999998e-05)) + (fTemp30 * ((2.2000000000000001e-06 * fTemp30) + -1.5400000000000001e-06))) + -7.3259999999999998e-07);
			double fTemp57 = (16.0 * fTemp56);
			double fTemp58 = (fTemp29 * ((fTemp30 * (700.0 - (1000.0 * fTemp30))) + 333.0));
			double fTemp59 = (fConst50 * fTemp58);
			double fTemp60 = (((fTemp26 * ((((fTemp26 * (0.047092000000000002 - (0.01 * fTemp30))) - (0.01 * fTemp34)) + (0.02 * fTemp30)) + -0.046761999999999998)) + (fTemp30 * ((0.010999999999999999 * fTemp30) + -0.0086999999999999994))) + -0.0056682);
			double fTemp61 = (8.0 * fTemp60);
			double fTemp62 = ((fTemp26 * ((32.0 * fTemp26) + -21.34)) + -16.225999999999999);
			double fTemp63 = (4.0 * fTemp62);
			double fTemp64 = ((10000.0 * fTemp26) + -11000.0);
			double fTemp65 = (2.0 * fTemp64);
			double fTemp66 = (32.0 * fTemp56);
			double fTemp67 = (fConst51 * fTemp58);
			double fTemp68 = (8.0 * fTemp62);
			double fTemp69 = (8.0 * fTemp64);
			double fTemp70 = (fConst52 * fTemp58);
			double fTemp71 = (24.0 * fTemp60);
			double fTemp72 = (10.0 * fTemp64);
			double fTemp73 = std::min<double>(127.0, std::max<double>(0.0, (15.875 * ((fConst0 * ((((((((fRec1[0] * ((fConst0 * ((fConst0 * ((fConst0 * (fTemp57 + fTemp59)) + fTemp61)) + fTemp63)) + fTemp65)) + (fRec1[1] * ((fConst0 * ((fConst31 * (0.0 - (fTemp66 + fTemp67))) + fTemp68)) + fTemp69))) + (fRec1[2] * ((fConst0 * ((fConst0 * ((fConst0 * (fTemp70 - fTemp57)) - fTemp71)) - fTemp63)) + fTemp72))) + (fConst0 * (fRec1[3] * ((fConst53 * fTemp56) - (16.0 * fTemp62))))) + (fRec1[4] * ((fConst0 * ((fConst0 * (fTemp71 + (fConst0 * (0.0 - (fTemp57 + fTemp70))))) - fTemp63)) - fTemp72))) + (fRec1[5] * ((fConst0 * (fTemp68 + (fConst31 * (fTemp67 - fTemp66)))) - fTemp69))) + (fRec1[6] * ((fConst0 * (fTemp63 + (fConst0 * ((fConst0 * (fTemp57 - fTemp59)) - fTemp61)))) - fTemp65))) / fTemp55)) + 4.0))));
			int iTemp74 = int(fTemp73);
			double fTemp75 = ftbl0Bass21FaustDSPSIG0[iTemp74];
			output0[i0] = FAUSTFLOAT((fTemp75 + ((fTemp73 - double(iTemp74)) * (ftbl0Bass21FaustDSPSIG0[std::min<int>(127, int((iTemp74 + 1)))] - fTemp75))));
			fRec12[1] = fRec12[0];
			for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				fRec11[j0] = fRec11[(j0 - 1)];
			}
			fRec13[1] = fRec13[0];
			fVec0[1] = fVec0[0];
			fVec1[1] = fVec1[0];
			fVec2[1] = fVec2[0];
			fRec10[1] = fRec10[0];
			fRec9[1] = fRec9[0];
			fRec14[1] = fRec14[0];
			fVec3[1] = fVec3[0];
			fVec4[1] = fVec4[0];
			fVec5[1] = fVec5[0];
			fRec8[1] = fRec8[0];
			fRec7[1] = fRec7[0];
			for (int j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
				fRec6[j1] = fRec6[(j1 - 1)];
			}
			fVec6[1] = fVec6[0];
			fVec7[1] = fVec7[0];
			fRec5[1] = fRec5[0];
			fRec4[1] = fRec4[0];
			fVec8[1] = fVec8[0];
			fRec3[1] = fRec3[0];
			fRec2[1] = fRec2[0];
			fRec15[1] = fRec15[0];
			fRec16[1] = fRec16[0];
			fRec17[1] = fRec17[0];
			fRec18[1] = fRec18[0];
			for (int j2 = 6; (j2 > 0); j2 = (j2 - 1)) {
				fRec1[j2] = fRec1[(j2 - 1)];
			}
		}
		//[End:compute]
	}


	FAUSTFLOAT getBegin() const { return fCheckbox0; }
	void setBegin(FAUSTFLOAT value) { fCheckbox0 = value; }

	FAUSTFLOAT getPregain() const { return fHslider0; }
	void setPregain(FAUSTFLOAT value) { fHslider0 = value; }

	FAUSTFLOAT getLevel() const { return fHslider4; }
	void setLevel(FAUSTFLOAT value) { fHslider4 = value; }

	FAUSTFLOAT getBlend() const { return fHslider3; }
	void setBlend(FAUSTFLOAT value) { fHslider3 = value; }

	FAUSTFLOAT getPresence() const { return fHslider1; }
	void setPresence(FAUSTFLOAT value) { fHslider1 = value; }

	FAUSTFLOAT getDrive() const { return fHslider2; }
	void setDrive(FAUSTFLOAT value) { fHslider2 = value; }

	FAUSTFLOAT getBass() const { return fHslider5; }
	void setBass(FAUSTFLOAT value) { fHslider5 = value; }

	FAUSTFLOAT getTreble() const { return fHslider6; }
	void setTreble(FAUSTFLOAT value) { fHslider6 = value; }

	//[End:class]
};
//[After:class]


#endif
#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif
#undef FAUSTFLOAT
#undef FAUSTCLASS
