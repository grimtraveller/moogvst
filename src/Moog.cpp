/*
 * Moog.cpp
 *
 *  Created on: 22/08/2010
 *      Author: Bruno Figueira "Jedi" Lourenço
 */

#include "Moog.h"
#include <cmath>

Moog::Moog() :
	oscil1_freq(0), oscil1_amp(1.0), oscil2_freq(0), oscil2_amp(1.0),
			noise_amp(1.0), adder(3), mult_aux(3), master_amp(1.0), input_freq(
					440), oscil1_range(8), oscil1FreqOffset(0),
			oscil2_range(8), oscil2FreqOffset(0) {

	/*
	 * Osciladores e ruído
	 */
	oscil1.setFrequencyInput(&oscil1_freq);
	oscil1.setAmplitudeInput(&oscil1_amp);

	oscil2.setFrequencyInput(&oscil2_freq);
	oscil2.setAmplitudeInput(&oscil2_amp);

	noise.setAmplitudeInput(&noise_amp);

	/*
	 * Somador
	 */
	adder.setInput(0, &oscil1);
	adder.setInput(1, &oscil2);
	adder.setInput(2, &noise);

	filter.setInputSignal(&adder);

	mult_aux.setInput(0, &filter);
	mult_aux.setInput(1, &env);
	mult_aux.setInput(2, &master_amp);

	updateOscil1();
	updateOscil2();
}

void Moog::setInputFreq(float freq) {
	this->input_freq = freq;
	oscil1.resetBlock();
	oscil2.resetBlock();
	updateOscil1();
	updateOscil2();
	env.resetBlock();
	filter_env.resetBlock();
}

void Moog::setMasterAmp(float amp) {
	master_amp.setNumber(amp);
}

float Moog::getMasterAmp() {
	return master_amp.getNumber();
}

float Moog::getNextValue() {
	return mult_aux.getNextValue();
}

/*
 * Oscil1
 */

void Moog::setOscil1Amp(float amp) {
	oscil1_amp.setNumber(amp);
}

float Moog::getOscil1Amp() {
	return oscil1_amp.getNumber();
}

void Moog::setOscil1Waveform(wavetype_t type) {
	oscil1.setWavetable(type);
}

wavetype_t Moog::getOscil1Waveform() {
	return oscil1.getWavetype();
}

void Moog::setOscil1Range(int range) {
	oscil1_range = range;
	updateOscil1();
}

int Moog::getOscil1Range() {
	return oscil1_range;
}

void Moog::setOscil1Frequency(float freq) {
	oscil1FreqOffset = freq;
	updateOscil1();
}

void Moog::setOscil1ON(bool ON) {
	oscil1.setON(ON);
}

bool Moog::getOscil1ON() {
	return oscil1.getON();
}
/*
 * Oscil2
 */

void Moog::setOscil2Amp(float amp) {
	oscil2_amp.setNumber(amp);
}

float Moog::getOscil2Amp() {
	return oscil2_amp.getNumber();
}

void Moog::setOscil2Waveform(wavetype_t type) {
	oscil2.setWavetable(type);
}

wavetype_t Moog::getOscil2Waveform() {
	return oscil2.getWavetype();
}

void Moog::setOscil2Range(int range) {
	oscil2_range = range;
	updateOscil2();
}

int Moog::getOscil2Range() {
	return oscil2_range;
}

void Moog::setOscil2Frequency(float freq) {
	oscil2FreqOffset = freq;
	updateOscil2();
}

void Moog::setOscil2ON(bool ON) {
	oscil2.setON(ON);
}

bool Moog::getOscil2ON() {
	return oscil2.getON();
}

/*
 * Noise
 */

void Moog::setNoiseON(bool ON){
	noise.setON(ON);
}

bool Moog::getNoiseON() {
	return noise.getON();
}

void Moog::setNoiseAmp(float amp){
	noise_amp.setNumber(amp);
}

float Moog::getNoiseAmp() {
	return noise_amp.getNumber();
}

void Moog::setNoiseType(noisetype_t type) {
	noise.setType(type);
}

noisetype_t Moog::getNoiseType() {
	return noise.getType();
}
/*
 * Aux
 */

void Moog::updateOscil1() {
	oscil1_freq.setNumber(input_freq * ((float) oscil1_range / 8.0) * pow(2.0,
			oscil1FreqOffset / 12));
}

void Moog::updateOscil2() {
	oscil2_freq.setNumber(input_freq * ((float) oscil2_range / 8.0) * pow(2.0,
			oscil2FreqOffset / 12));
}
