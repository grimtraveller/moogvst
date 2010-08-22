/*
 * Moog.h
 *
 *  Created on: 22/08/2010
 *      Author: Bruno Figueira "Jedi" Lourenço
 */

#ifndef MOOG_H_
#define MOOG_H_

#include "basic_blocks.h"

class Moog {
public:
	Moog();

	void setInputFreq(float freq);
	float getInputFreq();
	void setMasterAmp(float amp);
	float getMasterAmp();

	void setOscil1Amp(float amp);
	float getOscil1Amp();
	void setOscil1Waveform(wavetype_t type);
	wavetype_t getOscil1Waveform();
	void setOscil1Range(int range);
	int getOscil1Range();
	void setOscil1Frequency(float freq);
	float getOscil1Frequency();

	void setOscil2Amp(float amp);
	float getOscil2Amp();
	void setOscil2Waveform(wavetype_t type);
	wavetype_t getOscil2Waveform();
	void setOscil2Range(int range);
	int getOscil2Range();
	void setOscil2Frequency(float freq);
	float getOscil2Frequency();
private:
	/*
	 * Os blocos que compõem o sintetizador
	 */
	Oscil oscil1;
	Number oscil1_freq;
	Number oscil1_amp;
	Oscil oscil2;
	Number oscil2_freq;
	Number oscil2_amp;

	Noise noise;
	Number noise_amp;

	Adder adder;

	Filter filter;

	ADSR filter_env;
	ADSR env;

	Multiplier mult_aux;
	Number master_amp;

	/*
	 * Knobs
	 *
	 */
	float input_freq;
	int oscil1_range;
	float oscil1FreqOffset;
	int oscil2_range;
	float oscil2FreqOffset;

	/*
	 * Aux
	 */
	void updateOscil1();
	void updateOscil2();
};

#endif /* MOOG_H_ */
