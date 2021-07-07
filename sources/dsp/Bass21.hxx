#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
/* ------------------------------------------------------------
author: "JPC"
license: "AGPL-3.0-or-later"
name: "Bass21"
Code generated with Faust 2.33.0 (https://faust.grame.fr)
Compilation options: -lang cpp -inpl -mapp -es 1 -single -ftz 0
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


//[Before:class]
class Bass21SIG0 {
	//[Begin:class]

	
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
	
	void fillBass21SIG0(int count, float* table) {
		for (int i1 = 0; (i1 < count); i1 = (i1 + 1)) {
			iRec0[0] = (iRec0[1] + 1);
			table[i1] = float(tanhf(float(((0.0629921257f * float((iRec0[0] + -1))) + -4.0f))));
			iRec0[1] = iRec0[0];
		}
	}

};

static Bass21SIG0* newBass21SIG0() { return (Bass21SIG0*)new Bass21SIG0(); }
static void deleteBass21SIG0(Bass21SIG0* dsp) { delete dsp; }

static float ftbl0Bass21SIG0[128];
static float Bass21_faustpower2_f(float value) {
	return (value * value);
}
static float Bass21_faustpower3_f(float value) {
	return ((value * value) * value);
}

#ifndef FAUSTCLASS 
#define FAUSTCLASS Bass21
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class Bass21 {
	
 private:
	
	int fSampleRate;
	float fConst0;
	float fConst1;
	float fConst3;
	float fConst5;
	float fConst6;
	FAUSTFLOAT fHslider0;
	float fConst7;
	float fRec4[2];
	float fConst9;
	float fConst10;
	float fConst12;
	float fConst13;
	float fConst15;
	float fConst17;
	float fConst19;
	float fConst20;
	float fConst23;
	FAUSTFLOAT fHslider1;
	float fRec17[2];
	float fVec0[2];
	float fConst24;
	float fVec1[2];
	float fConst25;
	float fConst26;
	float fRec16[2];
	float fRec15[2];
	float fConst31;
	float fConst33;
	float fConst36;
	float fRec14[4];
	float fConst38;
	float fConst39;
	float fConst40;
	float fConst41;
	FAUSTFLOAT fHslider2;
	float fRec18[2];
	float fVec2[2];
	float fVec3[2];
	float fConst43;
	float fVec4[2];
	float fRec13[2];
	float fRec12[2];
	FAUSTFLOAT fHslider3;
	float fRec19[2];
	float fConst44;
	float fVec5[2];
	float fVec6[2];
	float fVec7[2];
	float fRec11[2];
	float fRec10[2];
	float fConst45;
	float fConst47;
	float fConst48;
	float fConst49;
	float fRec9[4];
	float fConst50;
	float fConst51;
	float fConst52;
	float fVec8[2];
	float fVec9[2];
	float fConst53;
	float fConst54;
	float fRec8[2];
	float fRec7[2];
	float fVec10[2];
	float fConst55;
	float fRec6[2];
	float fRec5[2];
	FAUSTFLOAT fHslider4;
	float fRec20[2];
	FAUSTFLOAT fHslider5;
	float fRec21[2];
	float fVec11[2];
	float fRec3[2];
	float fRec22[2];
	float fConst56;
	FAUSTFLOAT fHslider6;
	float fRec23[2];
	float fConst57;
	float fRec2[3];
	float fConst58;
	float fConst59;
	float fRec1[3];
	
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
		fConst0 = float(fSampleRate);
		fConst1 = (3.14159274f / fConst0);
		float fConst2 = std::tan(fConst1);
		fConst3 = (2.0f * (1.0f - (1.0f / Bass21_faustpower2_f(fConst2))));
		float fConst4 = std::tan((188.49556f / fConst0));
		fConst5 = (2.0f * (1.0f - (1.0f / Bass21_faustpower2_f(fConst4))));
		fConst6 = (44.0999985f / fConst0);
		fConst7 = (1.0f - fConst6);
		float fConst8 = (1.13256e-08f * fConst0);
		fConst9 = (1.0f / ((fConst0 * (fConst8 + 0.000144000005f)) + 1.0f));
		fConst10 = ((fConst0 * (fConst8 + -0.000144000005f)) + 1.0f);
		float fConst11 = (5.64150412e-07f * fConst0);
		fConst12 = (1.0f / ((fConst0 * (fConst11 + 0.00292359991f)) + 1.0f));
		fConst13 = ((fConst0 * (fConst11 + -0.00292359991f)) + 1.0f);
		float fConst14 = ((fConst0 * ((fConst0 * ((3.59236424e-07f * fConst0) + 0.00361684919f)) + 118.466316f)) + 32000.0f);
		fConst15 = (((fConst0 * (fConst11 + -0.000855599996f)) + 1.0f) / fConst14);
		float fConst16 = (20.6800003f * fConst0);
		fConst17 = (fConst16 + 22000.0f);
		float fConst18 = (4.12290563e-10f * fConst0);
		fConst19 = (1.0f / ((fConst0 * ((fConst0 * (fConst18 + 5.39214716e-06f)) + 0.00652959989f)) + 1.0f));
		fConst20 = ((fConst0 * ((fConst0 * (fConst18 + 2.81107191e-07f)) + 0.00212959992f)) + 1.0f);
		float fConst21 = (0.0444400012f * fConst0);
		float fConst22 = (fConst21 + 1.0f);
		fConst23 = (0.0f - (0.0439999998f * (fConst0 / fConst22)));
		fConst24 = ((1.0f - fConst21) / fConst22);
		fConst25 = (1.0f / fConst22);
		fConst26 = (0.0439999998f * fConst0);
		float fConst27 = Bass21_faustpower3_f(fConst0);
		float fConst28 = (0.0f - (24.0f * fConst27));
		float fConst29 = (5.15363204e-11f * fConst28);
		float fConst30 = (5.39214716e-06f * fConst0);
		fConst31 = ((fConst29 + (fConst0 * (0.00652959989f - fConst30))) + 3.0f);
		float fConst32 = (1.23687172e-09f * fConst0);
		fConst33 = ((fConst0 * ((fConst0 * (fConst32 + -5.39214716e-06f)) + -0.00652959989f)) + 3.0f);
		float fConst34 = (0.0f - (8.0f * fConst27));
		float fConst35 = (5.15363204e-11f * fConst34);
		fConst36 = ((fConst35 + (fConst0 * (fConst30 + -0.00652959989f))) + 1.0f);
		float fConst37 = (2.81107191e-07f * fConst0);
		fConst38 = ((fConst29 + (fConst0 * (0.00212959992f - fConst37))) + 3.0f);
		fConst39 = ((fConst0 * ((fConst0 * (fConst32 + -2.81107191e-07f)) + -0.00212959992f)) + 3.0f);
		fConst40 = ((fConst35 + (fConst0 * (fConst37 + -0.00212959992f))) + 1.0f);
		fConst41 = (2.90399996e-12f * fConst0);
		float fConst42 = (0.0f - (8.0f * Bass21_faustpower2_f(fConst0)));
		fConst43 = (7.25999989e-13f * fConst42);
		fConst44 = (0.0001452f * fConst0);
		fConst45 = (1.0f / fConst14);
		float fConst46 = (0.00361684919f * fConst0);
		fConst47 = (((4.4904553e-08f * fConst28) + (fConst0 * (118.466316f - fConst46))) + 96000.0f);
		fConst48 = ((fConst0 * ((fConst0 * ((1.07770927e-06f * fConst0) + -0.00361684919f)) + -118.466316f)) + 96000.0f);
		fConst49 = (((4.4904553e-08f * fConst34) + (fConst0 * (fConst46 + -118.466316f))) + 32000.0f);
		fConst50 = (fConst16 + 66000.0f);
		fConst51 = (66000.0f - fConst16);
		fConst52 = (22000.0f - fConst16);
		fConst53 = ((1.41037603e-07f * fConst42) + 2.0f);
		fConst54 = (((fConst0 * (fConst11 + 0.000855599996f)) + 1.0f) / fConst14);
		fConst55 = ((2.8314e-09f * fConst42) + 2.0f);
		fConst56 = (1.0f / fConst4);
		fConst57 = (942.477783f / (fConst0 * std::sin((376.991119f / fConst0))));
		fConst58 = (1.0f / fConst2);
		fConst59 = (31.415926f / (fConst0 * std::sin((6.28318548f / fConst0))));
		//[End:instanceConstants]
	}
	
	void instanceResetUserInterface() {
		//[Begin:instanceResetUserInterface]
		fHslider0 = FAUSTFLOAT(0.5f);
		fHslider1 = FAUSTFLOAT(0.5f);
		fHslider2 = FAUSTFLOAT(0.5f);
		fHslider3 = FAUSTFLOAT(0.5f);
		fHslider4 = FAUSTFLOAT(0.5f);
		fHslider5 = FAUSTFLOAT(0.5f);
		fHslider6 = FAUSTFLOAT(0.5f);
		//[End:instanceResetUserInterface]
	}
	
	void instanceClear() {
		//[Begin:instanceClear]
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec4[l1] = 0.0f;
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec17[l2] = 0.0f;
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fVec0[l3] = 0.0f;
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fVec1[l4] = 0.0f;
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec16[l5] = 0.0f;
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec15[l6] = 0.0f;
		}
		for (int l7 = 0; (l7 < 4); l7 = (l7 + 1)) {
			fRec14[l7] = 0.0f;
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec18[l8] = 0.0f;
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fVec2[l9] = 0.0f;
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fVec3[l10] = 0.0f;
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fVec4[l11] = 0.0f;
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec13[l12] = 0.0f;
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec12[l13] = 0.0f;
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec19[l14] = 0.0f;
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fVec5[l15] = 0.0f;
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fVec6[l16] = 0.0f;
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fVec7[l17] = 0.0f;
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fRec11[l18] = 0.0f;
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec10[l19] = 0.0f;
		}
		for (int l20 = 0; (l20 < 4); l20 = (l20 + 1)) {
			fRec9[l20] = 0.0f;
		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fVec8[l21] = 0.0f;
		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fVec9[l22] = 0.0f;
		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fRec8[l23] = 0.0f;
		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fRec7[l24] = 0.0f;
		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fVec10[l25] = 0.0f;
		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fRec6[l26] = 0.0f;
		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			fRec5[l27] = 0.0f;
		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			fRec20[l28] = 0.0f;
		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fRec21[l29] = 0.0f;
		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fVec11[l30] = 0.0f;
		}
		for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			fRec3[l31] = 0.0f;
		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			fRec22[l32] = 0.0f;
		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fRec23[l33] = 0.0f;
		}
		for (int l34 = 0; (l34 < 3); l34 = (l34 + 1)) {
			fRec2[l34] = 0.0f;
		}
		for (int l35 = 0; (l35 < 3); l35 = (l35 + 1)) {
			fRec1[l35] = 0.0f;
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
		float fSlow0 = (fConst6 * float(fHslider0));
		float fSlow1 = (fConst6 * float(fHslider1));
		float fSlow2 = (fConst6 * float(fHslider2));
		float fSlow3 = (fConst6 * float(fHslider3));
		float fSlow4 = (fConst6 * float(fHslider4));
		float fSlow5 = (fConst6 * float(fHslider5));
		float fSlow6 = (fConst6 * float(fHslider6));
		for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
			float fTemp0 = float(input0[i0]);
			fRec4[0] = (fSlow0 + (fConst7 * fRec4[1]));
			float fTemp1 = ((40.0f * fRec4[0]) + -20.0f);
			float fTemp2 = std::tan((fConst1 * ((fTemp1 > 0.0f) ? 7500.0f : std::pow(10.0f, (0.0500000007f * (fTemp1 + 77.5012283f))))));
			float fTemp3 = (1.0f / fTemp2);
			float fTemp4 = (1.0f - fTemp3);
			fRec17[0] = (fSlow1 + (fConst7 * fRec17[1]));
			float fTemp5 = (fTemp0 * fRec17[0]);
			fVec0[0] = fTemp5;
			fVec1[0] = ((fConst23 * fVec0[1]) - (fConst24 * fRec15[1]));
			fRec16[0] = (fVec1[1] + (fConst25 * ((fConst26 * fTemp5) - (2.0f * fRec16[1]))));
			fRec15[0] = fRec16[0];
			fRec14[0] = (fRec15[0] - (fConst19 * (((fConst31 * fRec14[1]) + (fConst33 * fRec14[2])) + (fConst36 * fRec14[3]))));
			float fTemp6 = ((((fConst20 * fRec14[0]) + (fConst38 * fRec14[1])) + (fConst39 * fRec14[2])) + (fConst40 * fRec14[3]));
			fRec18[0] = (fSlow2 + (fConst7 * fRec18[1]));
			float fTemp7 = ((100000.0f * (1.0f - fRec18[0])) + 3300.0f);
			float fTemp8 = (fConst41 * fTemp7);
			float fTemp9 = (9.99999994e-09f * fTemp7);
			float fTemp10 = (2.0f * (fTemp9 + 0.00337260007f));
			float fTemp11 = (2.0f * (fTemp9 + 7.25999998e-05f));
			float fTemp12 = ((fConst0 * (fTemp11 + fTemp8)) + 1.0f);
			fVec2[0] = ((fTemp6 * ((fConst0 * (fTemp8 - fTemp10)) + 1.0f)) / fTemp12);
			fVec3[0] = ((fConst19 * fVec2[1]) - ((fRec12[1] * ((fConst0 * (fTemp8 - fTemp11)) + 1.0f)) / fTemp12));
			float fTemp13 = ((fConst43 * fTemp7) + 2.0f);
			fVec4[0] = ((fTemp13 * fTemp6) / fTemp12);
			fRec13[0] = ((fVec3[1] + (fConst19 * fVec4[1])) - (((fRec13[1] * fTemp13) - (fConst19 * (fTemp6 * ((fConst0 * (fTemp8 + fTemp10)) + 1.0f)))) / fTemp12));
			fRec12[0] = fRec13[0];
			float fTemp14 = std::min<float>(127.0f, std::max<float>(0.0f, (15.875f * (fRec12[0] + 4.0f))));
			int iTemp15 = int(fTemp14);
			float fTemp16 = ftbl0Bass21SIG0[iTemp15];
			float fTemp17 = (fTemp16 + ((fTemp14 - float(iTemp15)) * (ftbl0Bass21SIG0[std::min<int>(127, (iTemp15 + 1))] - fTemp16)));
			fRec19[0] = (fSlow3 + (fConst7 * fRec19[1]));
			float fTemp18 = (100000.0f * (1.0f - fRec19[0]));
			float fTemp19 = (fTemp18 + 3300.0f);
			float fTemp20 = (fConst44 * fTemp19);
			float fTemp21 = (fTemp18 + fTemp20);
			float fTemp22 = (fTemp21 + 3300.0f);
			fVec5[0] = ((fTemp17 * (fTemp18 + (333300.0f - fTemp20))) / fTemp22);
			fVec6[0] = (fVec5[1] - ((fRec10[1] * (fTemp18 + (3300.0f - fTemp20))) / fTemp22));
			fVec7[0] = ((fTemp17 * (fTemp18 + 333300.0f)) / fTemp22);
			fRec11[0] = ((fVec6[1] + ((fTemp17 * (fTemp21 + 333300.0f)) / fTemp22)) - (2.0f * (((fRec11[1] * fTemp19) / fTemp22) - fVec7[1])));
			fRec10[0] = fRec11[0];
			float fTemp23 = std::min<float>(127.0f, std::max<float>(0.0f, (15.875f * (fRec10[0] + 4.0f))));
			int iTemp24 = int(fTemp23);
			float fTemp25 = ftbl0Bass21SIG0[iTemp24];
			fRec9[0] = ((fTemp25 + ((fTemp23 - float(iTemp24)) * (ftbl0Bass21SIG0[std::min<int>(127, (iTemp24 + 1))] - fTemp25))) - (fConst45 * (((fConst47 * fRec9[1]) + (fConst48 * fRec9[2])) + (fConst49 * fRec9[3]))));
			float fTemp26 = ((((fConst17 * fRec9[0]) + (fConst50 * fRec9[1])) + (fConst51 * fRec9[2])) + (fConst52 * fRec9[3]));
			fVec8[0] = fTemp26;
			fVec9[0] = (0.0f - (fConst12 * ((fConst13 * fRec7[1]) - (fConst15 * fVec8[1]))));
			fRec8[0] = (fVec9[1] - (fConst12 * ((fConst53 * (fRec8[1] - (fConst45 * fVec8[1]))) - (fConst54 * fTemp26))));
			fRec7[0] = fRec8[0];
			fVec10[0] = (0.0f - (fConst9 * ((fConst10 * fRec5[1]) - fRec7[1])));
			fRec6[0] = (fVec10[1] + (fConst9 * (fRec7[0] + ((2.0f * fRec7[1]) - (fConst55 * fRec6[1])))));
			fRec5[0] = fRec6[0];
			fRec20[0] = (fSlow4 + (fConst7 * fRec20[1]));
			fRec21[0] = (fSlow5 + (fConst7 * fRec21[1]));
			float fTemp27 = std::min<float>(127.0f, std::max<float>(0.0f, (15.875f * (4.0f - (2.20000005f * (((fRec5[0] * fRec20[0]) + (fRec15[0] * (1.0f - fRec20[0]))) * fRec21[0]))))));
			int iTemp28 = int(fTemp27);
			float fTemp29 = ftbl0Bass21SIG0[iTemp28];
			float fTemp30 = (fTemp29 + ((fTemp27 - float(iTemp28)) * (ftbl0Bass21SIG0[std::min<int>(127, (iTemp28 + 1))] - fTemp29)));
			fVec11[0] = fTemp30;
			float fTemp31 = (fTemp3 + 1.0f);
			fRec3[0] = (0.0f - (((fTemp4 * fRec3[1]) - (fTemp30 + fVec11[1])) / fTemp31));
			fRec22[0] = ((fVec11[1] * (0.0f - (1.0f / (fTemp2 * fTemp31)))) - (((fRec22[1] * fTemp4) - (fTemp30 / fTemp2)) / fTemp31));
			fRec23[0] = (fSlow6 + (fConst7 * fRec23[1]));
			float fTemp32 = ((24.0f * fRec23[0]) + -18.0f);
			int iTemp33 = (fTemp32 > 0.0f);
			float fTemp34 = (fConst57 * std::pow(10.0f, (0.0500000007f * std::fabs(fTemp32))));
			float fTemp35 = (iTemp33 ? fConst57 : fTemp34);
			float fTemp36 = (fConst5 * fRec2[1]);
			float fTemp37 = ((fConst56 * (fConst56 + fTemp35)) + 1.0f);
			fRec2[0] = ((fRec3[0] + (fRec22[0] * std::pow(10.0f, (0.0500000007f * fTemp1)))) - (((fRec2[2] * ((fConst56 * (fConst56 - fTemp35)) + 1.0f)) + fTemp36) / fTemp37));
			float fTemp38 = (iTemp33 ? fTemp34 : fConst57);
			float fTemp39 = ((6.0f * fRec23[0]) + -18.0f);
			int iTemp40 = (fTemp39 > 0.0f);
			float fTemp41 = (fConst59 * std::pow(10.0f, (0.0500000007f * std::fabs(fTemp39))));
			float fTemp42 = (iTemp40 ? fConst59 : fTemp41);
			float fTemp43 = (fConst3 * fRec1[1]);
			float fTemp44 = ((fConst58 * (fConst58 + fTemp42)) + 1.0f);
			fRec1[0] = ((((fTemp36 + (fRec2[0] * ((fConst56 * (fConst56 + fTemp38)) + 1.0f))) + (fRec2[2] * ((fConst56 * (fConst56 - fTemp38)) + 1.0f))) / fTemp37) - (((fRec1[2] * ((fConst58 * (fConst58 - fTemp42)) + 1.0f)) + fTemp43) / fTemp44));
			float fTemp45 = (iTemp40 ? fTemp41 : fConst59);
			float fTemp46 = std::min<float>(127.0f, std::max<float>(0.0f, (15.875f * ((((fTemp43 + (fRec1[0] * ((fConst58 * (fConst58 + fTemp45)) + 1.0f))) + (fRec1[2] * ((fConst58 * (fConst58 - fTemp45)) + 1.0f))) / fTemp44) + 4.0f))));
			int iTemp47 = int(fTemp46);
			float fTemp48 = ftbl0Bass21SIG0[iTemp47];
			output0[i0] = FAUSTFLOAT((fTemp48 + ((fTemp46 - float(iTemp47)) * (ftbl0Bass21SIG0[std::min<int>(127, (iTemp47 + 1))] - fTemp48))));
			fRec4[1] = fRec4[0];
			fRec17[1] = fRec17[0];
			fVec0[1] = fVec0[0];
			fVec1[1] = fVec1[0];
			fRec16[1] = fRec16[0];
			fRec15[1] = fRec15[0];
			for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				fRec14[j0] = fRec14[(j0 - 1)];
			}
			fRec18[1] = fRec18[0];
			fVec2[1] = fVec2[0];
			fVec3[1] = fVec3[0];
			fVec4[1] = fVec4[0];
			fRec13[1] = fRec13[0];
			fRec12[1] = fRec12[0];
			fRec19[1] = fRec19[0];
			fVec5[1] = fVec5[0];
			fVec6[1] = fVec6[0];
			fVec7[1] = fVec7[0];
			fRec11[1] = fRec11[0];
			fRec10[1] = fRec10[0];
			for (int j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
				fRec9[j1] = fRec9[(j1 - 1)];
			}
			fVec8[1] = fVec8[0];
			fVec9[1] = fVec9[0];
			fRec8[1] = fRec8[0];
			fRec7[1] = fRec7[0];
			fVec10[1] = fVec10[0];
			fRec6[1] = fRec6[0];
			fRec5[1] = fRec5[0];
			fRec20[1] = fRec20[0];
			fRec21[1] = fRec21[0];
			fVec11[1] = fVec11[0];
			fRec3[1] = fRec3[0];
			fRec22[1] = fRec22[0];
			fRec23[1] = fRec23[0];
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
