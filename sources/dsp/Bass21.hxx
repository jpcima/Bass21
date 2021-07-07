#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
/* ------------------------------------------------------------
author: "JPC"
license: "AGPL-3.0-or-later"
name: "Bass21"
Code generated with Faust 2.33.0 (https://faust.grame.fr)
Compilation options: -lang cpp -inpl -mapp -es 1 -double -ftz 0
------------------------------------------------------------ */

#ifndef  __Bass21_H__
#define  __Bass21_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

/* link with : "" */
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

class Bass21SIG0 {
	
  private:
	
	int iRec0[2];
	
  public:
	
	int getNumInputsBass21SIG0() {
		return 0;
	}
	int getNumOutputsBass21SIG0() {
		return 1;
	}
	
	void instanceInitBass21SIG0(int sample_rate) {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iRec0[l0] = 0;
		}
	}
	
	void fillBass21SIG0(int count, double* table) {
		for (int i1 = 0; (i1 < count); i1 = (i1 + 1)) {
			iRec0[0] = (iRec0[1] + 1);
			table[i1] = double(tanh(double(((0.062992125984251968 * double((iRec0[0] + -1))) + -4.0))));
			iRec0[1] = iRec0[0];
		}
	}

};

static Bass21SIG0* newBass21SIG0() { return (Bass21SIG0*)new Bass21SIG0(); }
static void deleteBass21SIG0(Bass21SIG0* dsp) { delete dsp; }

static double ftbl0Bass21SIG0[128];
static double Bass21_faustpower2_f(double value) {
	return (value * value);
}
static double Bass21_faustpower3_f(double value) {
	return ((value * value) * value);
}

#ifndef FAUSTCLASS 
#define FAUSTCLASS Bass21
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif


//[Before:class]
class Bass21 {
	//[Begin:class]

	
 private:
	
	int fSampleRate;
	double fConst0;
	double fConst1;
	double fConst3;
	double fConst5;
	double fConst6;
	FAUSTFLOAT fHslider0;
	double fConst7;
	double fRec4[2];
	double fConst9;
	double fConst10;
	double fConst12;
	double fConst13;
	double fConst15;
	double fConst17;
	double fConst19;
	double fConst20;
	FAUSTFLOAT fHslider1;
	double fRec15[2];
	double fConst25;
	double fConst27;
	double fConst30;
	double fRec14[4];
	double fConst32;
	double fConst33;
	double fConst34;
	double fConst35;
	FAUSTFLOAT fHslider2;
	double fRec16[2];
	double fVec0[2];
	double fVec1[2];
	double fConst37;
	double fVec2[2];
	double fRec13[2];
	double fRec12[2];
	FAUSTFLOAT fHslider3;
	double fRec17[2];
	double fConst38;
	double fVec3[2];
	double fVec4[2];
	double fVec5[2];
	double fRec11[2];
	double fRec10[2];
	double fConst39;
	double fConst41;
	double fConst42;
	double fConst43;
	double fRec9[4];
	double fConst44;
	double fConst45;
	double fConst46;
	double fVec6[2];
	double fVec7[2];
	double fConst47;
	double fConst48;
	double fRec8[2];
	double fRec7[2];
	double fVec8[2];
	double fConst49;
	double fRec6[2];
	double fRec5[2];
	FAUSTFLOAT fHslider4;
	double fRec18[2];
	FAUSTFLOAT fHslider5;
	double fRec19[2];
	double fVec9[2];
	double fRec3[2];
	double fRec20[2];
	double fConst50;
	FAUSTFLOAT fHslider6;
	double fRec21[2];
	double fConst51;
	double fRec2[3];
	double fConst52;
	double fConst53;
	double fRec1[3];
	
 public:
	

	static constexpr int getNumInputs() {
		return 1;
	}
	static constexpr int getNumOutputs() {
		return 1;
	}
	
	static void classInit(int sample_rate) {
		//[Begin:classInit]
		Bass21SIG0* sig0 = newBass21SIG0();
		sig0->instanceInitBass21SIG0(sample_rate);
		sig0->fillBass21SIG0(128, ftbl0Bass21SIG0);
		deleteBass21SIG0(sig0);
		//[End:classInit]
	}
	
	void instanceConstants(int sample_rate) {
		//[Begin:instanceConstants]
		fSampleRate = sample_rate;
		fConst0 = double(fSampleRate);
		fConst1 = (3.1415926535897931 / fConst0);
		double fConst2 = std::tan(fConst1);
		fConst3 = (2.0 * (1.0 - (1.0 / Bass21_faustpower2_f(fConst2))));
		double fConst4 = std::tan((188.49555921538757 / fConst0));
		fConst5 = (2.0 * (1.0 - (1.0 / Bass21_faustpower2_f(fConst4))));
		fConst6 = (44.100000000000001 / fConst0);
		fConst7 = (1.0 - fConst6);
		double fConst8 = (1.13256e-08 * fConst0);
		fConst9 = (1.0 / ((fConst0 * (fConst8 + 0.000144)) + 1.0));
		fConst10 = ((fConst0 * (fConst8 + -0.000144)) + 1.0);
		double fConst11 = (5.641504e-07 * fConst0);
		fConst12 = (1.0 / ((fConst0 * (fConst11 + 0.0029236000000000002)) + 1.0));
		fConst13 = ((fConst0 * (fConst11 + -0.0029236000000000002)) + 1.0);
		double fConst14 = ((fConst0 * ((fConst0 * ((3.5923641600000005e-07 * fConst0) + 0.0036168492799999994)) + 118.46632000000001)) + 32000.0);
		fConst15 = (((fConst0 * (fConst11 + -0.00085559999999999998)) + 1.0) / fConst14);
		double fConst16 = (20.68 * fConst0);
		fConst17 = (fConst16 + 22000.0);
		double fConst18 = (4.1229055999999999e-10 * fConst0);
		fConst19 = (1.0 / ((fConst0 * ((fConst0 * (fConst18 + 5.3921471999999997e-06)) + 0.0065295999999999991)) + 1.0));
		fConst20 = ((fConst0 * ((fConst0 * (fConst18 + 2.8110719999999996e-07)) + 0.0021295999999999997)) + 1.0);
		double fConst21 = Bass21_faustpower3_f(fConst0);
		double fConst22 = (0.0 - (24.0 * fConst21));
		double fConst23 = (5.1536319999999999e-11 * fConst22);
		double fConst24 = (5.3921471999999997e-06 * fConst0);
		fConst25 = ((fConst23 + (fConst0 * (0.0065295999999999991 - fConst24))) + 3.0);
		double fConst26 = (1.2368716799999999e-09 * fConst0);
		fConst27 = ((fConst0 * ((fConst0 * (fConst26 + -5.3921471999999997e-06)) + -0.0065295999999999991)) + 3.0);
		double fConst28 = (0.0 - (8.0 * fConst21));
		double fConst29 = (5.1536319999999999e-11 * fConst28);
		fConst30 = ((fConst29 + (fConst0 * (fConst24 + -0.0065295999999999991))) + 1.0);
		double fConst31 = (2.8110719999999996e-07 * fConst0);
		fConst32 = ((fConst23 + (fConst0 * (0.0021295999999999997 - fConst31))) + 3.0);
		fConst33 = ((fConst0 * ((fConst0 * (fConst26 + -2.8110719999999996e-07)) + -0.0021295999999999997)) + 3.0);
		fConst34 = ((fConst29 + (fConst0 * (fConst31 + -0.0021295999999999997))) + 1.0);
		fConst35 = (2.9040000000000001e-12 * fConst0);
		double fConst36 = (0.0 - (8.0 * Bass21_faustpower2_f(fConst0)));
		fConst37 = (7.2600000000000004e-13 * fConst36);
		fConst38 = (0.00014520000000000001 * fConst0);
		fConst39 = (1.0 / fConst14);
		double fConst40 = (0.0036168492799999994 * fConst0);
		fConst41 = (((4.4904552000000007e-08 * fConst22) + (fConst0 * (118.46632000000001 - fConst40))) + 96000.0);
		fConst42 = ((fConst0 * ((fConst0 * ((1.0777092480000002e-06 * fConst0) + -0.0036168492799999994)) + -118.46632000000001)) + 96000.0);
		fConst43 = (((4.4904552000000007e-08 * fConst28) + (fConst0 * (fConst40 + -118.46632000000001))) + 32000.0);
		fConst44 = (fConst16 + 66000.0);
		fConst45 = (66000.0 - fConst16);
		fConst46 = (22000.0 - fConst16);
		fConst47 = ((1.410376e-07 * fConst36) + 2.0);
		fConst48 = (((fConst0 * (fConst11 + 0.00085559999999999998)) + 1.0) / fConst14);
		fConst49 = ((2.8314e-09 * fConst36) + 2.0);
		fConst50 = (1.0 / fConst4);
		fConst51 = (942.47779607693792 / (fConst0 * std::sin((376.99111843077515 / fConst0))));
		fConst52 = (1.0 / fConst2);
		fConst53 = (31.415926535897931 / (fConst0 * std::sin((6.2831853071795862 / fConst0))));
		//[End:instanceConstants]
	}
	
	void instanceResetUserInterface() {
		//[Begin:instanceResetUserInterface]
		fHslider0 = FAUSTFLOAT(0.5);
		fHslider1 = FAUSTFLOAT(0.5);
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
			fRec4[l1] = 0.0;
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec15[l2] = 0.0;
		}
		for (int l3 = 0; (l3 < 4); l3 = (l3 + 1)) {
			fRec14[l3] = 0.0;
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec16[l4] = 0.0;
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fVec0[l5] = 0.0;
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fVec1[l6] = 0.0;
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fVec2[l7] = 0.0;
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec13[l8] = 0.0;
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec12[l9] = 0.0;
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec17[l10] = 0.0;
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fVec3[l11] = 0.0;
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fVec4[l12] = 0.0;
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fVec5[l13] = 0.0;
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec11[l14] = 0.0;
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec10[l15] = 0.0;
		}
		for (int l16 = 0; (l16 < 4); l16 = (l16 + 1)) {
			fRec9[l16] = 0.0;
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fVec6[l17] = 0.0;
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fVec7[l18] = 0.0;
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec8[l19] = 0.0;
		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fRec7[l20] = 0.0;
		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fVec8[l21] = 0.0;
		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fRec6[l22] = 0.0;
		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fRec5[l23] = 0.0;
		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fRec18[l24] = 0.0;
		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fRec19[l25] = 0.0;
		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fVec9[l26] = 0.0;
		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			fRec3[l27] = 0.0;
		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			fRec20[l28] = 0.0;
		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fRec21[l29] = 0.0;
		}
		for (int l30 = 0; (l30 < 3); l30 = (l30 + 1)) {
			fRec2[l30] = 0.0;
		}
		for (int l31 = 0; (l31 < 3); l31 = (l31 + 1)) {
			fRec1[l31] = 0.0;
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
		double fSlow0 = (fConst6 * double(fHslider0));
		double fSlow1 = (fConst6 * double(fHslider1));
		double fSlow2 = (fConst6 * double(fHslider2));
		double fSlow3 = (fConst6 * double(fHslider3));
		double fSlow4 = (fConst6 * double(fHslider4));
		double fSlow5 = (fConst6 * double(fHslider5));
		double fSlow6 = (fConst6 * double(fHslider6));
		for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
			double fTemp0 = double(input0[i0]);
			fRec4[0] = (fSlow0 + (fConst7 * fRec4[1]));
			double fTemp1 = ((40.0 * fRec4[0]) + -20.0);
			double fTemp2 = std::tan((fConst1 * ((fTemp1 > 0.0) ? 7500.0 : std::pow(10.0, (0.050000000000000003 * (fTemp1 + 77.501225267834002))))));
			double fTemp3 = (1.0 / fTemp2);
			double fTemp4 = (1.0 - fTemp3);
			fRec15[0] = (fSlow1 + (fConst7 * fRec15[1]));
			double fTemp5 = (fTemp0 * fRec15[0]);
			fRec14[0] = (fTemp5 - (fConst19 * (((fConst25 * fRec14[1]) + (fConst27 * fRec14[2])) + (fConst30 * fRec14[3]))));
			double fTemp6 = ((((fConst20 * fRec14[0]) + (fConst32 * fRec14[1])) + (fConst33 * fRec14[2])) + (fConst34 * fRec14[3]));
			fRec16[0] = (fSlow2 + (fConst7 * fRec16[1]));
			double fTemp7 = ((100000.0 * (1.0 - fRec16[0])) + 3300.0);
			double fTemp8 = (fConst35 * fTemp7);
			double fTemp9 = (1e-08 * fTemp7);
			double fTemp10 = (2.0 * (fTemp9 + 0.0033725999999999999));
			double fTemp11 = (2.0 * (fTemp9 + 7.2600000000000003e-05));
			double fTemp12 = ((fConst0 * (fTemp11 + fTemp8)) + 1.0);
			fVec0[0] = ((fTemp6 * ((fConst0 * (fTemp8 - fTemp10)) + 1.0)) / fTemp12);
			fVec1[0] = ((fConst19 * fVec0[1]) - ((fRec12[1] * ((fConst0 * (fTemp8 - fTemp11)) + 1.0)) / fTemp12));
			double fTemp13 = ((fConst37 * fTemp7) + 2.0);
			fVec2[0] = ((fTemp13 * fTemp6) / fTemp12);
			fRec13[0] = ((fVec1[1] + (fConst19 * fVec2[1])) - (((fRec13[1] * fTemp13) - (fConst19 * (fTemp6 * ((fConst0 * (fTemp8 + fTemp10)) + 1.0)))) / fTemp12));
			fRec12[0] = fRec13[0];
			double fTemp14 = std::min<double>(127.0, std::max<double>(0.0, (15.875 * (fRec12[0] + 4.0))));
			int iTemp15 = int(fTemp14);
			double fTemp16 = ftbl0Bass21SIG0[iTemp15];
			double fTemp17 = (fTemp16 + ((fTemp14 - double(iTemp15)) * (ftbl0Bass21SIG0[std::min<int>(127, (iTemp15 + 1))] - fTemp16)));
			fRec17[0] = (fSlow3 + (fConst7 * fRec17[1]));
			double fTemp18 = (100000.0 * (1.0 - fRec17[0]));
			double fTemp19 = (fTemp18 + 3300.0);
			double fTemp20 = (fConst38 * fTemp19);
			double fTemp21 = (fTemp18 + fTemp20);
			double fTemp22 = (fTemp21 + 3300.0);
			fVec3[0] = ((fTemp17 * (fTemp18 + (333300.0 - fTemp20))) / fTemp22);
			fVec4[0] = (fVec3[1] - ((fRec10[1] * (fTemp18 + (3300.0 - fTemp20))) / fTemp22));
			fVec5[0] = ((fTemp17 * (fTemp18 + 333300.0)) / fTemp22);
			fRec11[0] = ((fVec4[1] + ((fTemp17 * (fTemp21 + 333300.0)) / fTemp22)) - (2.0 * (((fRec11[1] * fTemp19) / fTemp22) - fVec5[1])));
			fRec10[0] = fRec11[0];
			double fTemp23 = std::min<double>(127.0, std::max<double>(0.0, (15.875 * (fRec10[0] + 4.0))));
			int iTemp24 = int(fTemp23);
			double fTemp25 = ftbl0Bass21SIG0[iTemp24];
			fRec9[0] = ((fTemp25 + ((fTemp23 - double(iTemp24)) * (ftbl0Bass21SIG0[std::min<int>(127, (iTemp24 + 1))] - fTemp25))) - (fConst39 * (((fConst41 * fRec9[1]) + (fConst42 * fRec9[2])) + (fConst43 * fRec9[3]))));
			double fTemp26 = ((((fConst17 * fRec9[0]) + (fConst44 * fRec9[1])) + (fConst45 * fRec9[2])) + (fConst46 * fRec9[3]));
			fVec6[0] = fTemp26;
			fVec7[0] = (0.0 - (fConst12 * ((fConst13 * fRec7[1]) - (fConst15 * fVec6[1]))));
			fRec8[0] = (fVec7[1] - (fConst12 * ((fConst47 * (fRec8[1] - (fConst39 * fVec6[1]))) - (fConst48 * fTemp26))));
			fRec7[0] = fRec8[0];
			fVec8[0] = (0.0 - (fConst9 * ((fConst10 * fRec5[1]) - fRec7[1])));
			fRec6[0] = (fVec8[1] + (fConst9 * (fRec7[0] + ((2.0 * fRec7[1]) - (fConst49 * fRec6[1])))));
			fRec5[0] = fRec6[0];
			fRec18[0] = (fSlow4 + (fConst7 * fRec18[1]));
			fRec19[0] = (fSlow5 + (fConst7 * fRec19[1]));
			double fTemp27 = std::min<double>(127.0, std::max<double>(0.0, (15.875 * (4.0 - (2.2000000000000002 * (((fRec5[0] * fRec18[0]) + (fTemp5 * (1.0 - fRec18[0]))) * fRec19[0]))))));
			int iTemp28 = int(fTemp27);
			double fTemp29 = ftbl0Bass21SIG0[iTemp28];
			double fTemp30 = (fTemp29 + ((fTemp27 - double(iTemp28)) * (ftbl0Bass21SIG0[std::min<int>(127, (iTemp28 + 1))] - fTemp29)));
			fVec9[0] = fTemp30;
			double fTemp31 = (fTemp3 + 1.0);
			fRec3[0] = (0.0 - (((fTemp4 * fRec3[1]) - (fTemp30 + fVec9[1])) / fTemp31));
			fRec20[0] = ((fVec9[1] * (0.0 - (1.0 / (fTemp2 * fTemp31)))) - (((fRec20[1] * fTemp4) - (fTemp30 / fTemp2)) / fTemp31));
			fRec21[0] = (fSlow6 + (fConst7 * fRec21[1]));
			double fTemp32 = ((24.0 * fRec21[0]) + -18.0);
			int iTemp33 = (fTemp32 > 0.0);
			double fTemp34 = (fConst51 * std::pow(10.0, (0.050000000000000003 * std::fabs(fTemp32))));
			double fTemp35 = (iTemp33 ? fConst51 : fTemp34);
			double fTemp36 = (fConst5 * fRec2[1]);
			double fTemp37 = ((fConst50 * (fConst50 + fTemp35)) + 1.0);
			fRec2[0] = ((fRec3[0] + (fRec20[0] * std::pow(10.0, (0.050000000000000003 * fTemp1)))) - (((fRec2[2] * ((fConst50 * (fConst50 - fTemp35)) + 1.0)) + fTemp36) / fTemp37));
			double fTemp38 = (iTemp33 ? fTemp34 : fConst51);
			double fTemp39 = ((6.0 * fRec21[0]) + -18.0);
			int iTemp40 = (fTemp39 > 0.0);
			double fTemp41 = (fConst53 * std::pow(10.0, (0.050000000000000003 * std::fabs(fTemp39))));
			double fTemp42 = (iTemp40 ? fConst53 : fTemp41);
			double fTemp43 = (fConst3 * fRec1[1]);
			double fTemp44 = ((fConst52 * (fConst52 + fTemp42)) + 1.0);
			fRec1[0] = ((((fTemp36 + (fRec2[0] * ((fConst50 * (fConst50 + fTemp38)) + 1.0))) + (fRec2[2] * ((fConst50 * (fConst50 - fTemp38)) + 1.0))) / fTemp37) - (((fRec1[2] * ((fConst52 * (fConst52 - fTemp42)) + 1.0)) + fTemp43) / fTemp44));
			double fTemp45 = (iTemp40 ? fTemp41 : fConst53);
			double fTemp46 = std::min<double>(127.0, std::max<double>(0.0, (15.875 * ((((fTemp43 + (fRec1[0] * ((fConst52 * (fConst52 + fTemp45)) + 1.0))) + (fRec1[2] * ((fConst52 * (fConst52 - fTemp45)) + 1.0))) / fTemp44) + 4.0))));
			int iTemp47 = int(fTemp46);
			double fTemp48 = ftbl0Bass21SIG0[iTemp47];
			output0[i0] = FAUSTFLOAT((fTemp48 + ((fTemp46 - double(iTemp47)) * (ftbl0Bass21SIG0[std::min<int>(127, (iTemp47 + 1))] - fTemp48))));
			fRec4[1] = fRec4[0];
			fRec15[1] = fRec15[0];
			for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				fRec14[j0] = fRec14[(j0 - 1)];
			}
			fRec16[1] = fRec16[0];
			fVec0[1] = fVec0[0];
			fVec1[1] = fVec1[0];
			fVec2[1] = fVec2[0];
			fRec13[1] = fRec13[0];
			fRec12[1] = fRec12[0];
			fRec17[1] = fRec17[0];
			fVec3[1] = fVec3[0];
			fVec4[1] = fVec4[0];
			fVec5[1] = fVec5[0];
			fRec11[1] = fRec11[0];
			fRec10[1] = fRec10[0];
			for (int j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
				fRec9[j1] = fRec9[(j1 - 1)];
			}
			fVec6[1] = fVec6[0];
			fVec7[1] = fVec7[0];
			fRec8[1] = fRec8[0];
			fRec7[1] = fRec7[0];
			fVec8[1] = fVec8[0];
			fRec6[1] = fRec6[0];
			fRec5[1] = fRec5[0];
			fRec18[1] = fRec18[0];
			fRec19[1] = fRec19[0];
			fVec9[1] = fVec9[0];
			fRec3[1] = fRec3[0];
			fRec20[1] = fRec20[0];
			fRec21[1] = fRec21[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
		}
		//[End:compute]
	}


    FAUSTFLOAT getPregain() const { return fHslider1; }
    void setPregain(FAUSTFLOAT value) { fHslider1 = value; }

    FAUSTFLOAT getLevel() const { return fHslider5; }
    void setLevel(FAUSTFLOAT value) { fHslider5 = value; }

    FAUSTFLOAT getBlend() const { return fHslider4; }
    void setBlend(FAUSTFLOAT value) { fHslider4 = value; }

    FAUSTFLOAT getPresence() const { return fHslider2; }
    void setPresence(FAUSTFLOAT value) { fHslider2 = value; }

    FAUSTFLOAT getDrive() const { return fHslider3; }
    void setDrive(FAUSTFLOAT value) { fHslider3 = value; }

    FAUSTFLOAT getBass() const { return fHslider6; }
    void setBass(FAUSTFLOAT value) { fHslider6 = value; }

    FAUSTFLOAT getTreble() const { return fHslider0; }
    void setTreble(FAUSTFLOAT value) { fHslider0 = value; }

	//[End:class]
};
//[After:class]


#endif
#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif
#undef FAUSTFLOAT
#undef FAUSTCLASS
