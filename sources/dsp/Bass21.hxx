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

#ifndef  __Bass21DSP_H__
#define  __Bass21DSP_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

/* link with : "" */
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

class Bass21DSPSIG0 {
	
  private:
	
	int iRec0[2];
	
  public:
	
	int getNumInputsBass21DSPSIG0() {
		return 0;
	}
	int getNumOutputsBass21DSPSIG0() {
		return 1;
	}
	
	void instanceInitBass21DSPSIG0(int sample_rate) {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iRec0[l0] = 0;
		}
	}
	
	void fillBass21DSPSIG0(int count, double* table) {
		for (int i1 = 0; (i1 < count); i1 = (i1 + 1)) {
			iRec0[0] = (iRec0[1] + 1);
			table[i1] = double(tanh(double(((0.062992125984251968 * double((iRec0[0] + -1))) + -4.0))));
			iRec0[1] = iRec0[0];
		}
	}

};

static Bass21DSPSIG0* newBass21DSPSIG0() { return (Bass21DSPSIG0*)new Bass21DSPSIG0(); }
static void deleteBass21DSPSIG0(Bass21DSPSIG0* dsp) { delete dsp; }

static double ftbl0Bass21DSPSIG0[128];
static double Bass21DSP_faustpower2_f(double value) {
	return (value * value);
}
static double Bass21DSP_faustpower3_f(double value) {
	return ((value * value) * value);
}

#ifndef FAUSTCLASS 
#define FAUSTCLASS Bass21DSP
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif


//[Before:class]
class Bass21DSP {
	//[Begin:class]

	
 private:
	
	FAUSTFLOAT fCheckbox0;
	int fSampleRate;
	double fConst0;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	double fConst1;
	double fConst2;
	double fVec0[2];
	double fConst3;
	double fRec3[2];
	double fRec2[2];
	double fRec1[2];
	double fConst5;
	double fConst6;
	double fConst8;
	double fConst9;
	double fConst10;
	double fConst13;
	double fConst16;
	double fConst17;
	double fConst18;
	FAUSTFLOAT fHslider2;
	double fRec12[2];
	double fConst19;
	double fConst24;
	double fConst26;
	double fRec13[2];
	double fConst28;
	double fConst29;
	double fRec14[2];
	double fConst32;
	double fConst33;
	double fRec15[2];
	double fConst34;
	FAUSTFLOAT fHslider3;
	double fRec16[2];
	double fVec1[2];
	double fVec2[2];
	double fConst35;
	double fConst37;
	double fVec3[2];
	double fRec11[2];
	double fRec10[2];
	FAUSTFLOAT fHslider4;
	double fRec17[2];
	double fConst38;
	double fVec4[2];
	double fVec5[2];
	double fVec6[2];
	double fRec9[2];
	double fRec8[2];
	double fConst39;
	double fConst40;
	double fConst42;
	double fVec7[2];
	double fRec18[2];
	double fConst43;
	double fConst44;
	double fRec19[2];
	double fConst45;
	double fConst46;
	double fRec20[2];
	double fVec8[2];
	double fConst47;
	double fConst48;
	double fRec7[2];
	double fRec6[2];
	double fVec9[2];
	double fConst49;
	double fRec5[2];
	double fRec4[2];
	FAUSTFLOAT fHslider5;
	double fRec21[2];
	FAUSTFLOAT fHslider6;
	double fRec22[2];
	double fVec10[2];
	double fRec31[2];
	double fRec30[2];
	double fRec29[2];
	double fVec11[2];
	double fRec34[2];
	double fRec33[2];
	double fRec32[2];
	double fRec23[2];
	double fConst50;
	double fVec12[2];
	double fRec37[2];
	double fRec36[2];
	double fRec35[2];
	double fConst51;
	double fVec13[2];
	double fRec40[2];
	double fRec39[2];
	double fRec38[2];
	double fRec24[2];
	double fConst52;
	double fVec14[2];
	double fRec43[2];
	double fRec42[2];
	double fRec41[2];
	double fConst53;
	double fVec15[2];
	double fRec46[2];
	double fRec45[2];
	double fRec44[2];
	double fRec25[2];
	double fConst54;
	double fVec16[2];
	double fRec49[2];
	double fRec48[2];
	double fRec47[2];
	double fConst55;
	double fVec17[2];
	double fRec52[2];
	double fRec51[2];
	double fRec50[2];
	double fRec26[2];
	double fVec18[2];
	double fRec55[2];
	double fRec54[2];
	double fRec53[2];
	double fVec19[2];
	double fRec58[2];
	double fRec57[2];
	double fRec56[2];
	double fRec27[2];
	double fVec20[2];
	double fRec61[2];
	double fRec60[2];
	double fRec59[2];
	double fVec21[2];
	double fRec64[2];
	double fRec63[2];
	double fRec62[2];
	double fRec28[2];
	
 public:
	

	static constexpr int getNumInputs() {
		return 1;
	}
	static constexpr int getNumOutputs() {
		return 1;
	}
	
	static void classInit(int sample_rate) {
		//[Begin:classInit]
		Bass21DSPSIG0* sig0 = newBass21DSPSIG0();
		sig0->instanceInitBass21DSPSIG0(sample_rate);
		sig0->fillBass21DSPSIG0(128, ftbl0Bass21DSPSIG0);
		deleteBass21DSPSIG0(sig0);
		//[End:classInit]
	}
	
	void instanceConstants(int sample_rate) {
		//[Begin:instanceConstants]
		fSampleRate = sample_rate;
		fConst0 = double(fSampleRate);
		fConst1 = (1.5487999999999999e-10 * fConst0);
		fConst2 = (3.066624e-16 * fConst0);
		fConst3 = (20.0 / fConst0);
		double fConst4 = (1.13256e-08 * fConst0);
		fConst5 = (1.0 / ((fConst0 * (fConst4 + 0.000144)) + 1.0));
		fConst6 = ((fConst0 * (fConst4 + -0.000144)) + 1.0);
		double fConst7 = (5.641504e-07 * fConst0);
		fConst8 = (1.0 / ((fConst0 * (fConst7 + 0.0029236000000000002)) + 1.0));
		fConst9 = ((fConst0 * (fConst7 + -0.0029236000000000002)) + 1.0);
		fConst10 = ((fConst0 * (fConst7 + -0.00085559999999999998)) + 1.0);
		double fConst11 = (20.68 * fConst0);
		double fConst12 = ((fConst0 * ((fConst0 * ((3.5923641600000005e-07 * fConst0) + 0.0036168492799999994)) + 118.46632000000001)) + 32000.0);
		fConst13 = ((fConst11 + 22000.0) / fConst12);
		double fConst14 = (4.1229055999999999e-10 * fConst0);
		double fConst15 = ((fConst0 * ((fConst0 * (fConst14 + 5.3921471999999997e-06)) + 0.0065295999999999991)) + 1.0);
		fConst16 = (((fConst0 * ((fConst0 * (fConst14 + 2.8110719999999996e-07)) + 0.0021295999999999997)) + 1.0) / fConst15);
		fConst17 = std::exp((0.0 - (138.19999999999999 / fConst0)));
		fConst18 = (1.0 - fConst17);
		fConst19 = (1.0 / fConst15);
		double fConst20 = Bass21DSP_faustpower3_f(fConst0);
		double fConst21 = (0.0 - (8.0 * fConst20));
		double fConst22 = (5.1536319999999999e-11 * fConst21);
		double fConst23 = (2.8110719999999996e-07 * fConst0);
		fConst24 = ((fConst22 + (fConst0 * (fConst23 + -0.0021295999999999997))) + 1.0);
		double fConst25 = (5.3921471999999997e-06 * fConst0);
		fConst26 = ((fConst22 + (fConst0 * (fConst25 + -0.0065295999999999991))) + 1.0);
		double fConst27 = (1.2368716799999999e-09 * fConst0);
		fConst28 = ((fConst0 * ((fConst0 * (fConst27 + -2.8110719999999996e-07)) + -0.0021295999999999997)) + 3.0);
		fConst29 = ((fConst0 * ((fConst0 * (fConst27 + -5.3921471999999997e-06)) + -0.0065295999999999991)) + 3.0);
		double fConst30 = (0.0 - (24.0 * fConst20));
		double fConst31 = (5.1536319999999999e-11 * fConst30);
		fConst32 = ((fConst31 + (fConst0 * (0.0021295999999999997 - fConst23))) + 3.0);
		fConst33 = ((fConst31 + (fConst0 * (0.0065295999999999991 - fConst25))) + 3.0);
		fConst34 = (2.9040000000000001e-12 * fConst0);
		fConst35 = Bass21DSP_faustpower2_f(fConst0);
		double fConst36 = (0.0 - (8.0 * fConst35));
		fConst37 = (7.2600000000000004e-13 * fConst36);
		fConst38 = (0.00014520000000000001 * fConst0);
		fConst39 = (1.0 / fConst12);
		fConst40 = (22000.0 - fConst11);
		double fConst41 = (0.0036168492799999994 * fConst0);
		fConst42 = (((4.4904552000000007e-08 * fConst21) + (fConst0 * (fConst41 + -118.46632000000001))) + 32000.0);
		fConst43 = (66000.0 - fConst11);
		fConst44 = ((fConst0 * ((fConst0 * ((1.0777092480000002e-06 * fConst0) + -0.0036168492799999994)) + -118.46632000000001)) + 96000.0);
		fConst45 = (fConst11 + 66000.0);
		fConst46 = (((4.4904552000000007e-08 * fConst30) + (fConst0 * (118.46632000000001 - fConst41))) + 96000.0);
		fConst47 = ((1.410376e-07 * fConst36) + 2.0);
		fConst48 = ((fConst0 * (fConst7 + 0.00085559999999999998)) + 1.0);
		fConst49 = ((2.8314e-09 * fConst36) + 2.0);
		fConst50 = (6.1951999999999995e-10 * fConst0);
		fConst51 = (1.8399743999999998e-15 * fConst0);
		fConst52 = (7.7439999999999993e-10 * fConst0);
		fConst53 = (64.0 * fConst0);
		fConst54 = (64.0 * fConst35);
		fConst55 = (6.1332480000000004e-15 * fConst35);
		//[End:instanceConstants]
	}
	
	void instanceResetUserInterface() {
		//[Begin:instanceResetUserInterface]
		fCheckbox0 = FAUSTFLOAT(0.0);
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
			fVec0[l1] = 0.0;
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec3[l2] = 0.0;
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec2[l3] = 0.0;
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec1[l4] = 0.0;
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec12[l5] = 0.0;
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec13[l6] = 0.0;
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec14[l7] = 0.0;
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec15[l8] = 0.0;
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec16[l9] = 0.0;
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fVec1[l10] = 0.0;
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fVec2[l11] = 0.0;
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fVec3[l12] = 0.0;
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec11[l13] = 0.0;
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec10[l14] = 0.0;
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec17[l15] = 0.0;
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fVec4[l16] = 0.0;
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fVec5[l17] = 0.0;
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fVec6[l18] = 0.0;
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec9[l19] = 0.0;
		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fRec8[l20] = 0.0;
		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fVec7[l21] = 0.0;
		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fRec18[l22] = 0.0;
		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fRec19[l23] = 0.0;
		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fRec20[l24] = 0.0;
		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fVec8[l25] = 0.0;
		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fRec7[l26] = 0.0;
		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			fRec6[l27] = 0.0;
		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			fVec9[l28] = 0.0;
		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fRec5[l29] = 0.0;
		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fRec4[l30] = 0.0;
		}
		for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			fRec21[l31] = 0.0;
		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			fRec22[l32] = 0.0;
		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fVec10[l33] = 0.0;
		}
		for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			fRec31[l34] = 0.0;
		}
		for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			fRec30[l35] = 0.0;
		}
		for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			fRec29[l36] = 0.0;
		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			fVec11[l37] = 0.0;
		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fRec34[l38] = 0.0;
		}
		for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			fRec33[l39] = 0.0;
		}
		for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			fRec32[l40] = 0.0;
		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			fRec23[l41] = 0.0;
		}
		for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			fVec12[l42] = 0.0;
		}
		for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			fRec37[l43] = 0.0;
		}
		for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			fRec36[l44] = 0.0;
		}
		for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			fRec35[l45] = 0.0;
		}
		for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			fVec13[l46] = 0.0;
		}
		for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			fRec40[l47] = 0.0;
		}
		for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) {
			fRec39[l48] = 0.0;
		}
		for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			fRec38[l49] = 0.0;
		}
		for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			fRec24[l50] = 0.0;
		}
		for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) {
			fVec14[l51] = 0.0;
		}
		for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			fRec43[l52] = 0.0;
		}
		for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			fRec42[l53] = 0.0;
		}
		for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) {
			fRec41[l54] = 0.0;
		}
		for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			fVec15[l55] = 0.0;
		}
		for (int l56 = 0; (l56 < 2); l56 = (l56 + 1)) {
			fRec46[l56] = 0.0;
		}
		for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			fRec45[l57] = 0.0;
		}
		for (int l58 = 0; (l58 < 2); l58 = (l58 + 1)) {
			fRec44[l58] = 0.0;
		}
		for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			fRec25[l59] = 0.0;
		}
		for (int l60 = 0; (l60 < 2); l60 = (l60 + 1)) {
			fVec16[l60] = 0.0;
		}
		for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			fRec49[l61] = 0.0;
		}
		for (int l62 = 0; (l62 < 2); l62 = (l62 + 1)) {
			fRec48[l62] = 0.0;
		}
		for (int l63 = 0; (l63 < 2); l63 = (l63 + 1)) {
			fRec47[l63] = 0.0;
		}
		for (int l64 = 0; (l64 < 2); l64 = (l64 + 1)) {
			fVec17[l64] = 0.0;
		}
		for (int l65 = 0; (l65 < 2); l65 = (l65 + 1)) {
			fRec52[l65] = 0.0;
		}
		for (int l66 = 0; (l66 < 2); l66 = (l66 + 1)) {
			fRec51[l66] = 0.0;
		}
		for (int l67 = 0; (l67 < 2); l67 = (l67 + 1)) {
			fRec50[l67] = 0.0;
		}
		for (int l68 = 0; (l68 < 2); l68 = (l68 + 1)) {
			fRec26[l68] = 0.0;
		}
		for (int l69 = 0; (l69 < 2); l69 = (l69 + 1)) {
			fVec18[l69] = 0.0;
		}
		for (int l70 = 0; (l70 < 2); l70 = (l70 + 1)) {
			fRec55[l70] = 0.0;
		}
		for (int l71 = 0; (l71 < 2); l71 = (l71 + 1)) {
			fRec54[l71] = 0.0;
		}
		for (int l72 = 0; (l72 < 2); l72 = (l72 + 1)) {
			fRec53[l72] = 0.0;
		}
		for (int l73 = 0; (l73 < 2); l73 = (l73 + 1)) {
			fVec19[l73] = 0.0;
		}
		for (int l74 = 0; (l74 < 2); l74 = (l74 + 1)) {
			fRec58[l74] = 0.0;
		}
		for (int l75 = 0; (l75 < 2); l75 = (l75 + 1)) {
			fRec57[l75] = 0.0;
		}
		for (int l76 = 0; (l76 < 2); l76 = (l76 + 1)) {
			fRec56[l76] = 0.0;
		}
		for (int l77 = 0; (l77 < 2); l77 = (l77 + 1)) {
			fRec27[l77] = 0.0;
		}
		for (int l78 = 0; (l78 < 2); l78 = (l78 + 1)) {
			fVec20[l78] = 0.0;
		}
		for (int l79 = 0; (l79 < 2); l79 = (l79 + 1)) {
			fRec61[l79] = 0.0;
		}
		for (int l80 = 0; (l80 < 2); l80 = (l80 + 1)) {
			fRec60[l80] = 0.0;
		}
		for (int l81 = 0; (l81 < 2); l81 = (l81 + 1)) {
			fRec59[l81] = 0.0;
		}
		for (int l82 = 0; (l82 < 2); l82 = (l82 + 1)) {
			fVec21[l82] = 0.0;
		}
		for (int l83 = 0; (l83 < 2); l83 = (l83 + 1)) {
			fRec64[l83] = 0.0;
		}
		for (int l84 = 0; (l84 < 2); l84 = (l84 + 1)) {
			fRec63[l84] = 0.0;
		}
		for (int l85 = 0; (l85 < 2); l85 = (l85 + 1)) {
			fRec62[l85] = 0.0;
		}
		for (int l86 = 0; (l86 < 2); l86 = (l86 + 1)) {
			fRec28[l86] = 0.0;
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
		int iSlow1 = int(fSlow0);
		double fSlow2 = double(fHslider0);
		double fSlow3 = (1.0 - fSlow2);
		double fSlow4 = ((10000.0 * fSlow3) + -11000.0);
		double fSlow5 = (2.0 * fSlow4);
		double fSlow6 = ((fSlow3 * ((32.0 * fSlow3) + -21.34)) + -16.225999999999999);
		double fSlow7 = (4.0 * fSlow6);
		double fSlow8 = (1.0 - double(fHslider1));
		double fSlow9 = Bass21DSP_faustpower2_f(fSlow8);
		double fSlow10 = (((fSlow3 * ((((fSlow3 * (0.047092000000000002 - (0.01 * fSlow8))) - (0.01 * fSlow9)) + (0.02 * fSlow8)) + -0.046761999999999998)) + (fSlow8 * ((0.010999999999999999 * fSlow8) + -0.0086999999999999994))) + -0.0056682);
		double fSlow11 = (8.0 * fSlow10);
		double fSlow12 = (((fSlow3 * ((((fSlow3 * ((fSlow8 * (1.3200000000000001e-05 - (2.1999999999999999e-05 * fSlow8))) + 1.6137439999999998e-05)) + (2.1999999999999999e-05 * fSlow9)) - (1.3200000000000001e-05 * fSlow8)) + -1.6137439999999998e-05)) + (fSlow8 * ((2.2000000000000001e-06 * fSlow8) + -1.5400000000000001e-06))) + -7.3259999999999998e-07);
		double fSlow13 = (16.0 * fSlow12);
		double fSlow14 = (fSlow3 * (0.0 - fSlow2));
		double fSlow15 = (fSlow14 * ((fSlow8 * (700.0 - (1000.0 * fSlow8))) + 333.0));
		double fSlow16 = (fConst1 * fSlow15);
		double fSlow17 = ((fSlow3 * (11210.1 - (1320.0 * fSlow3))) + 6094.8800000000001);
		double fSlow18 = (2.0 * fSlow17);
		double fSlow19 = (((fSlow3 * ((((fSlow3 * ((0.10000000000000001 * fSlow8) + -44.752179999999996)) + (0.10000000000000001 * fSlow9)) - (2.2000000000000002 * fSlow8)) + 56.405362199999999)) + (fSlow8 * (2.097 - (1.1200000000000001 * fSlow8)))) + 9.7002253599999992);
		double fSlow20 = (4.0 * fSlow19);
		double fSlow21 = (((fSlow3 * ((((fSlow3 * ((fSlow8 * ((0.0012199999999999999 * fSlow8) + -0.0111287)) + -0.048826257259999999)) - (0.0112167 * fSlow9)) + (0.021125399999999999 * fSlow8)) + 0.049156148359999999)) + (fSlow8 * (0.0057706010000000002 - (0.00347796 * fSlow8)))) + 0.003730485099);
		double fSlow22 = (8.0 * fSlow21);
		double fSlow23 = (((fSlow3 * ((((fSlow3 * ((fSlow8 * ((2.7857060000000002e-05 * fSlow8) + -3.6639635999999999e-05)) + -8.8882818023999985e-06)) - (2.7857060000000002e-05 * fSlow9)) + (3.6639635999999999e-05 * fSlow8)) + 8.8882818023999985e-06)) + (fSlow8 * (2.9348242e-06 - (2.2750420000000001e-06 * fSlow8)))) + 7.7623121400000002e-08);
		double fSlow24 = (16.0 * fSlow23);
		double fSlow25 = (fSlow8 * (1.0 - fSlow8));
		double fSlow26 = (((fSlow3 * ((((fSlow3 * ((fSlow8 * ((5.017434399999999e-09 * fSlow8) + -6.468955239999999e-09)) + -1.7117815307999998e-10)) - (5.017434399999999e-09 * fSlow9)) + (6.468955239999999e-09 * fSlow8)) + 1.7117815307999998e-10)) + (2.1780000000000002e-12 * fSlow25)) + 7.1874e-14);
		double fSlow27 = (32.0 * fSlow26);
		double fSlow28 = (fSlow14 * ((1000.0 * fSlow25) + 33.0));
		double fSlow29 = (fConst2 * fSlow28);
		double fSlow30 = (1120000.0 - (100000.0 * fSlow3));
		double fSlow31 = ((fConst0 * (fSlow18 + (fConst0 * (fSlow20 + (fConst0 * (fSlow22 + (fConst0 * (fSlow24 + (fConst0 * (fSlow27 - fSlow29)))))))))) + fSlow30);
		double fSlow32 = ((fSlow5 + (fConst0 * (fSlow7 + (fConst0 * (fSlow11 + (fConst0 * (fSlow13 + fSlow16))))))) / fSlow31);
		double fSlow33 = (fConst0 * fSlow32);
		double fSlow34 = (fConst18 * double(fHslider2));
		double fSlow35 = (fConst17 * double(((fSlow0 == fSlow0) | (fSlow0 == 0.0))));
		double fSlow36 = (1.0 - fSlow35);
		double fSlow37 = (double(fHslider3) * fSlow36);
		double fSlow38 = (double(fHslider4) * fSlow36);
		double fSlow39 = (fConst18 * double(fHslider5));
		double fSlow40 = (fConst18 * double(fHslider6));
		double fSlow41 = (((fConst0 * (fSlow7 + (fConst0 * ((fConst0 * (fSlow13 - fSlow16)) - fSlow11)))) - fSlow5) / fSlow31);
		double fSlow42 = (fConst0 * fSlow41);
		double fSlow43 = (((fConst0 * ((fConst0 * (fSlow20 + (fConst0 * ((fConst0 * (fSlow24 + (fConst0 * (0.0 - (fSlow27 + fSlow29))))) - fSlow22)))) - fSlow18)) + fSlow30) / fSlow31);
		double fSlow44 = (8.0 * fSlow6);
		double fSlow45 = (fConst50 * fSlow15);
		double fSlow46 = (32.0 * fSlow12);
		double fSlow47 = (8.0 * fSlow4);
		double fSlow48 = (((fConst0 * (fSlow44 + (fConst35 * (fSlow45 - fSlow46)))) - fSlow47) / fSlow31);
		double fSlow49 = (fConst0 * fSlow48);
		double fSlow50 = (6.0 * fSlow30);
		double fSlow51 = (8.0 * fSlow19);
		double fSlow52 = (128.0 * fSlow26);
		double fSlow53 = (fConst51 * fSlow28);
		double fSlow54 = (32.0 * fSlow23);
		double fSlow55 = (8.0 * fSlow17);
		double fSlow56 = ((fSlow50 + (fConst0 * ((fConst0 * (fSlow51 + (fConst35 * ((fConst0 * (fSlow52 + fSlow53)) - fSlow54)))) - fSlow55))) / fSlow31);
		double fSlow57 = (24.0 * fSlow10);
		double fSlow58 = (fConst52 * fSlow15);
		double fSlow59 = (10.0 * fSlow4);
		double fSlow60 = (((fConst0 * ((fConst0 * (fSlow57 + (fConst0 * (0.0 - (fSlow13 + fSlow58))))) - fSlow7)) - fSlow59) / fSlow31);
		double fSlow61 = (fConst0 * fSlow60);
		double fSlow62 = (15.0 * fSlow30);
		double fSlow63 = (24.0 * fSlow21);
		double fSlow64 = (fConst53 * (0.0 - (7.1874000000000004e-17 * fSlow28)));
		double fSlow65 = (160.0 * fSlow26);
		double fSlow66 = (10.0 * fSlow17);
		double fSlow67 = ((fSlow62 + (fConst0 * ((fConst0 * ((fConst0 * (fSlow63 + (fConst0 * ((fConst0 * (fSlow64 - fSlow65)) - fSlow24)))) - fSlow20)) - fSlow66))) / fSlow31);
		double fSlow68 = (((fConst54 * fSlow12) - (16.0 * fSlow6)) / fSlow31);
		double fSlow69 = (fConst35 * fSlow68);
		double fSlow70 = (((20.0 * fSlow30) + (fConst35 * ((fConst35 * ((64.0 * fSlow23) + (fConst55 * fSlow28))) - (16.0 * fSlow19)))) / fSlow31);
		double fSlow71 = ((fSlow59 + (fConst0 * ((fConst0 * ((fConst0 * (fSlow58 - fSlow13)) - fSlow57)) - fSlow7))) / fSlow31);
		double fSlow72 = (fConst0 * fSlow71);
		double fSlow73 = ((fSlow62 + (fConst0 * (fSlow66 + (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (fSlow65 + fSlow64)) - fSlow24)) - fSlow63)) - fSlow20))))) / fSlow31);
		double fSlow74 = ((fSlow47 + (fConst0 * (fSlow44 + (fConst35 * (0.0 - (fSlow46 + fSlow45)))))) / fSlow31);
		double fSlow75 = (fConst0 * fSlow74);
		double fSlow76 = ((fSlow50 + (fConst0 * (fSlow55 + (fConst0 * (fSlow51 + (fConst35 * ((fConst0 * (fSlow53 - fSlow52)) - fSlow54))))))) / fSlow31);
		for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
			double fTemp0 = double(input0[i0]);
			fVec0[0] = fSlow32;
			double fTemp1 = (fSlow33 - fRec1[1]);
			fRec3[0] = ((fSlow33 != (fConst0 * fVec0[1])) ? (fConst3 * fTemp1) : fRec3[1]);
			fRec2[0] = (iSlow1 ? fSlow33 : (fRec2[1] + double(copysign(double(std::min<double>(std::fabs(fTemp1), std::fabs(fRec3[0]))), double(fTemp1)))));
			fRec1[0] = fRec2[0];
			fRec12[0] = (fSlow34 + (fConst17 * fRec12[1]));
			double fTemp2 = (fTemp0 * fRec12[0]);
			double fTemp3 = ((fConst16 * fTemp2) + fRec15[1]);
			fRec13[0] = (fConst19 * ((fConst24 * fTemp2) - (fConst26 * fTemp3)));
			fRec14[0] = ((fConst19 * ((fConst28 * fTemp2) - (fConst29 * fTemp3))) + fRec13[1]);
			fRec15[0] = ((fConst19 * ((fConst32 * fTemp2) - (fConst33 * fTemp3))) + fRec14[1]);
			fRec16[0] = (fSlow37 + (fSlow35 * fRec16[1]));
			double fTemp4 = ((100000.0 * (1.0 - fRec16[0])) + 3300.0);
			double fTemp5 = (fConst34 * fTemp4);
			double fTemp6 = (1e-08 * fTemp4);
			double fTemp7 = (2.0 * (fTemp6 + 0.0033725999999999999));
			double fTemp8 = (2.0 * (fTemp6 + 7.2600000000000003e-05));
			double fTemp9 = ((fConst0 * (fTemp8 + fTemp5)) + 1.0);
			fVec1[0] = ((fTemp3 * ((fConst0 * (fTemp5 - fTemp7)) + 1.0)) / fTemp9);
			fVec2[0] = (fVec1[1] - ((fRec10[1] * ((fConst0 * (fTemp5 - fTemp8)) + 1.0)) / fTemp9));
			double fTemp10 = ((fConst37 * fTemp4) + 2.0);
			fVec3[0] = ((fTemp10 * fTemp3) / fTemp9);
			fRec11[0] = ((fVec2[1] + fVec3[1]) - (((fRec11[1] * fTemp10) - (fTemp3 * ((fConst0 * (fTemp5 + fTemp7)) + 1.0))) / fTemp9));
			fRec10[0] = fRec11[0];
			double fTemp11 = std::min<double>(127.0, std::max<double>(0.0, (15.875 * (fRec10[0] + 4.0))));
			int iTemp12 = int(fTemp11);
			double fTemp13 = ftbl0Bass21DSPSIG0[iTemp12];
			double fTemp14 = (fTemp13 + ((fTemp11 - double(iTemp12)) * (ftbl0Bass21DSPSIG0[std::min<int>(127, int((iTemp12 + 1)))] - fTemp13)));
			fRec17[0] = (fSlow38 + (fSlow35 * fRec17[1]));
			double fTemp15 = (100000.0 * (1.0 - fRec17[0]));
			double fTemp16 = (fTemp15 + 3300.0);
			double fTemp17 = (fConst38 * fTemp16);
			double fTemp18 = (fTemp15 + fTemp17);
			double fTemp19 = (fTemp18 + 3300.0);
			fVec4[0] = ((fTemp14 * (fTemp15 + (333300.0 - fTemp17))) / fTemp19);
			fVec5[0] = (fVec4[1] - ((fRec8[1] * (fTemp15 + (3300.0 - fTemp17))) / fTemp19));
			fVec6[0] = ((fTemp14 * (fTemp15 + 333300.0)) / fTemp19);
			fRec9[0] = ((fVec5[1] + ((fTemp14 * (fTemp18 + 333300.0)) / fTemp19)) - (2.0 * (((fRec9[1] * fTemp16) / fTemp19) - fVec6[1])));
			fRec8[0] = fRec9[0];
			double fTemp20 = std::min<double>(127.0, std::max<double>(0.0, (15.875 * (fRec8[0] + 4.0))));
			int iTemp21 = int(fTemp20);
			double fTemp22 = ftbl0Bass21DSPSIG0[iTemp21];
			double fTemp23 = (fTemp22 + ((fTemp20 - double(iTemp21)) * (ftbl0Bass21DSPSIG0[std::min<int>(127, int((iTemp21 + 1)))] - fTemp22)));
			double fTemp24 = ((fConst13 * fTemp23) + fRec20[1]);
			fVec7[0] = fTemp24;
			fRec18[0] = (fConst39 * ((fConst40 * fTemp23) - (fConst42 * fTemp24)));
			fRec19[0] = ((fConst39 * ((fConst43 * fTemp23) - (fConst44 * fTemp24))) + fRec18[1]);
			fRec20[0] = ((fConst39 * ((fConst45 * fTemp23) - (fConst46 * fTemp24))) + fRec19[1]);
			fVec8[0] = (0.0 - (fConst8 * ((fConst9 * fRec6[1]) - (fConst10 * fVec7[1]))));
			fRec7[0] = (fVec8[1] - (fConst8 * ((fConst47 * (fRec7[1] - fVec7[1])) - (fConst48 * fTemp24))));
			fRec6[0] = fRec7[0];
			fVec9[0] = (0.0 - (fConst5 * ((fConst6 * fRec4[1]) - fRec6[1])));
			fRec5[0] = (fVec9[1] + (fConst5 * (fRec6[0] + ((2.0 * fRec6[1]) - (fConst49 * fRec5[1])))));
			fRec4[0] = fRec5[0];
			fRec21[0] = (fSlow39 + (fConst17 * fRec21[1]));
			fRec22[0] = (fSlow40 + (fConst17 * fRec22[1]));
			double fTemp25 = std::min<double>(127.0, std::max<double>(0.0, (15.875 * (4.0 - (2.2000000000000002 * (((fRec4[0] * fRec21[0]) + (fTemp2 * (1.0 - fRec21[0]))) * fRec22[0]))))));
			int iTemp26 = int(fTemp25);
			double fTemp27 = ftbl0Bass21DSPSIG0[iTemp26];
			double fTemp28 = (fTemp27 + ((fTemp25 - double(iTemp26)) * (ftbl0Bass21DSPSIG0[std::min<int>(127, int((iTemp26 + 1)))] - fTemp27)));
			fVec10[0] = fSlow41;
			double fTemp29 = (fSlow42 - fRec29[1]);
			fRec31[0] = ((fSlow42 != (fConst0 * fVec10[1])) ? (fConst3 * fTemp29) : fRec31[1]);
			fRec30[0] = (iSlow1 ? fSlow42 : (fRec30[1] + double(copysign(double(std::min<double>(std::fabs(fTemp29), std::fabs(fRec31[0]))), double(fTemp29)))));
			fRec29[0] = fRec30[0];
			fVec11[0] = fSlow43;
			double fTemp30 = (fSlow43 - fRec32[1]);
			fRec34[0] = ((fSlow43 != fVec11[1]) ? (fConst3 * fTemp30) : fRec34[1]);
			fRec33[0] = (iSlow1 ? fSlow43 : (fRec33[1] + double(copysign(double(std::min<double>(std::fabs(fTemp30), std::fabs(fRec34[0]))), double(fTemp30)))));
			fRec32[0] = fRec33[0];
			double fTemp31 = ((fRec1[0] * fTemp28) + fRec28[1]);
			fRec23[0] = ((fRec29[0] * fTemp28) - (fRec32[0] * fTemp31));
			fVec12[0] = fSlow48;
			double fTemp32 = (fSlow49 - fRec35[1]);
			fRec37[0] = ((fSlow49 != (fConst0 * fVec12[1])) ? (fConst3 * fTemp32) : fRec37[1]);
			fRec36[0] = (iSlow1 ? fSlow49 : (fRec36[1] + double(copysign(double(std::min<double>(std::fabs(fTemp32), std::fabs(fRec37[0]))), double(fTemp32)))));
			fRec35[0] = fRec36[0];
			fVec13[0] = fSlow56;
			double fTemp33 = (fSlow56 - fRec38[1]);
			fRec40[0] = ((fSlow56 != fVec13[1]) ? (fConst3 * fTemp33) : fRec40[1]);
			fRec39[0] = (iSlow1 ? fSlow56 : (fRec39[1] + double(copysign(double(std::min<double>(std::fabs(fTemp33), std::fabs(fRec40[0]))), double(fTemp33)))));
			fRec38[0] = fRec39[0];
			fRec24[0] = (((fRec35[0] * fTemp28) + fRec23[1]) - (fRec38[0] * fTemp31));
			fVec14[0] = fSlow60;
			double fTemp34 = (fSlow61 - fRec41[1]);
			fRec43[0] = ((fSlow61 != (fConst0 * fVec14[1])) ? (fConst3 * fTemp34) : fRec43[1]);
			fRec42[0] = (iSlow1 ? fSlow61 : (fRec42[1] + double(copysign(double(std::min<double>(std::fabs(fTemp34), std::fabs(fRec43[0]))), double(fTemp34)))));
			fRec41[0] = fRec42[0];
			fVec15[0] = fSlow67;
			double fTemp35 = (fSlow67 - fRec44[1]);
			fRec46[0] = ((fSlow67 != fVec15[1]) ? (fConst3 * fTemp35) : fRec46[1]);
			fRec45[0] = (iSlow1 ? fSlow67 : (fRec45[1] + double(copysign(double(std::min<double>(std::fabs(fTemp35), std::fabs(fRec46[0]))), double(fTemp35)))));
			fRec44[0] = fRec45[0];
			fRec25[0] = (((fRec41[0] * fTemp28) + fRec24[1]) - (fRec44[0] * fTemp31));
			fVec16[0] = fSlow68;
			double fTemp36 = (fSlow69 - fRec47[1]);
			fRec49[0] = ((fSlow69 != (fConst35 * fVec16[1])) ? (fConst3 * fTemp36) : fRec49[1]);
			fRec48[0] = (iSlow1 ? fSlow69 : (fRec48[1] + double(copysign(double(std::min<double>(std::fabs(fTemp36), std::fabs(fRec49[0]))), double(fTemp36)))));
			fRec47[0] = fRec48[0];
			fVec17[0] = fSlow70;
			double fTemp37 = (fSlow70 - fRec50[1]);
			fRec52[0] = ((fSlow70 != fVec17[1]) ? (fConst3 * fTemp37) : fRec52[1]);
			fRec51[0] = (iSlow1 ? fSlow70 : (fRec51[1] + double(copysign(double(std::min<double>(std::fabs(fTemp37), std::fabs(fRec52[0]))), double(fTemp37)))));
			fRec50[0] = fRec51[0];
			fRec26[0] = (((fRec47[0] * fTemp28) + fRec25[1]) - (fRec50[0] * fTemp31));
			fVec18[0] = fSlow71;
			double fTemp38 = (fSlow72 - fRec53[1]);
			fRec55[0] = ((fSlow72 != (fConst0 * fVec18[1])) ? (fConst3 * fTemp38) : fRec55[1]);
			fRec54[0] = (iSlow1 ? fSlow72 : (fRec54[1] + double(copysign(double(std::min<double>(std::fabs(fTemp38), std::fabs(fRec55[0]))), double(fTemp38)))));
			fRec53[0] = fRec54[0];
			fVec19[0] = fSlow73;
			double fTemp39 = (fSlow73 - fRec56[1]);
			fRec58[0] = ((fSlow73 != fVec19[1]) ? (fConst3 * fTemp39) : fRec58[1]);
			fRec57[0] = (iSlow1 ? fSlow73 : (fRec57[1] + double(copysign(double(std::min<double>(std::fabs(fTemp39), std::fabs(fRec58[0]))), double(fTemp39)))));
			fRec56[0] = fRec57[0];
			fRec27[0] = (((fRec53[0] * fTemp28) + fRec26[1]) - (fRec56[0] * fTemp31));
			fVec20[0] = fSlow74;
			double fTemp40 = (fSlow75 - fRec59[1]);
			fRec61[0] = ((fSlow75 != (fConst0 * fVec20[1])) ? (fConst3 * fTemp40) : fRec61[1]);
			fRec60[0] = (iSlow1 ? fSlow75 : (fRec60[1] + double(copysign(double(std::min<double>(std::fabs(fTemp40), std::fabs(fRec61[0]))), double(fTemp40)))));
			fRec59[0] = fRec60[0];
			fVec21[0] = fSlow76;
			double fTemp41 = (fSlow76 - fRec62[1]);
			fRec64[0] = ((fSlow76 != fVec21[1]) ? (fConst3 * fTemp41) : fRec64[1]);
			fRec63[0] = (iSlow1 ? fSlow76 : (fRec63[1] + double(copysign(double(std::min<double>(std::fabs(fTemp41), std::fabs(fRec64[0]))), double(fTemp41)))));
			fRec62[0] = fRec63[0];
			fRec28[0] = (((fRec59[0] * fTemp28) + fRec27[1]) - (fRec62[0] * fTemp31));
			double fTemp42 = std::min<double>(127.0, std::max<double>(0.0, (15.875 * (fTemp31 + 4.0))));
			int iTemp43 = int(fTemp42);
			double fTemp44 = ftbl0Bass21DSPSIG0[iTemp43];
			output0[i0] = FAUSTFLOAT((fTemp44 + ((fTemp42 - double(iTemp43)) * (ftbl0Bass21DSPSIG0[std::min<int>(127, int((iTemp43 + 1)))] - fTemp44))));
			fVec0[1] = fVec0[0];
			fRec3[1] = fRec3[0];
			fRec2[1] = fRec2[0];
			fRec1[1] = fRec1[0];
			fRec12[1] = fRec12[0];
			fRec13[1] = fRec13[0];
			fRec14[1] = fRec14[0];
			fRec15[1] = fRec15[0];
			fRec16[1] = fRec16[0];
			fVec1[1] = fVec1[0];
			fVec2[1] = fVec2[0];
			fVec3[1] = fVec3[0];
			fRec11[1] = fRec11[0];
			fRec10[1] = fRec10[0];
			fRec17[1] = fRec17[0];
			fVec4[1] = fVec4[0];
			fVec5[1] = fVec5[0];
			fVec6[1] = fVec6[0];
			fRec9[1] = fRec9[0];
			fRec8[1] = fRec8[0];
			fVec7[1] = fVec7[0];
			fRec18[1] = fRec18[0];
			fRec19[1] = fRec19[0];
			fRec20[1] = fRec20[0];
			fVec8[1] = fVec8[0];
			fRec7[1] = fRec7[0];
			fRec6[1] = fRec6[0];
			fVec9[1] = fVec9[0];
			fRec5[1] = fRec5[0];
			fRec4[1] = fRec4[0];
			fRec21[1] = fRec21[0];
			fRec22[1] = fRec22[0];
			fVec10[1] = fVec10[0];
			fRec31[1] = fRec31[0];
			fRec30[1] = fRec30[0];
			fRec29[1] = fRec29[0];
			fVec11[1] = fVec11[0];
			fRec34[1] = fRec34[0];
			fRec33[1] = fRec33[0];
			fRec32[1] = fRec32[0];
			fRec23[1] = fRec23[0];
			fVec12[1] = fVec12[0];
			fRec37[1] = fRec37[0];
			fRec36[1] = fRec36[0];
			fRec35[1] = fRec35[0];
			fVec13[1] = fVec13[0];
			fRec40[1] = fRec40[0];
			fRec39[1] = fRec39[0];
			fRec38[1] = fRec38[0];
			fRec24[1] = fRec24[0];
			fVec14[1] = fVec14[0];
			fRec43[1] = fRec43[0];
			fRec42[1] = fRec42[0];
			fRec41[1] = fRec41[0];
			fVec15[1] = fVec15[0];
			fRec46[1] = fRec46[0];
			fRec45[1] = fRec45[0];
			fRec44[1] = fRec44[0];
			fRec25[1] = fRec25[0];
			fVec16[1] = fVec16[0];
			fRec49[1] = fRec49[0];
			fRec48[1] = fRec48[0];
			fRec47[1] = fRec47[0];
			fVec17[1] = fVec17[0];
			fRec52[1] = fRec52[0];
			fRec51[1] = fRec51[0];
			fRec50[1] = fRec50[0];
			fRec26[1] = fRec26[0];
			fVec18[1] = fVec18[0];
			fRec55[1] = fRec55[0];
			fRec54[1] = fRec54[0];
			fRec53[1] = fRec53[0];
			fVec19[1] = fVec19[0];
			fRec58[1] = fRec58[0];
			fRec57[1] = fRec57[0];
			fRec56[1] = fRec56[0];
			fRec27[1] = fRec27[0];
			fVec20[1] = fVec20[0];
			fRec61[1] = fRec61[0];
			fRec60[1] = fRec60[0];
			fRec59[1] = fRec59[0];
			fVec21[1] = fVec21[0];
			fRec64[1] = fRec64[0];
			fRec63[1] = fRec63[0];
			fRec62[1] = fRec62[0];
			fRec28[1] = fRec28[0];
		}
		//[End:compute]
	}


    FAUSTFLOAT getBegin() const { return fCheckbox0; }
    void setBegin(FAUSTFLOAT value) { fCheckbox0 = value; }

    FAUSTFLOAT getPregain() const { return fHslider2; }
    void setPregain(FAUSTFLOAT value) { fHslider2 = value; }

    FAUSTFLOAT getLevel() const { return fHslider6; }
    void setLevel(FAUSTFLOAT value) { fHslider6 = value; }

    FAUSTFLOAT getBlend() const { return fHslider5; }
    void setBlend(FAUSTFLOAT value) { fHslider5 = value; }

    FAUSTFLOAT getPresence() const { return fHslider3; }
    void setPresence(FAUSTFLOAT value) { fHslider3 = value; }

    FAUSTFLOAT getDrive() const { return fHslider4; }
    void setDrive(FAUSTFLOAT value) { fHslider4 = value; }

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
