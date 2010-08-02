/*
 * Waveform.cpp
 *
 *  Created on: 23/07/2010
 *      Author: Bruno Figueira "Jedi" Lourenço
 */
#include "basic_blocks.h"

vector<float> * Waveforms::getWaveform(wavetype_t wave) {
	switch (wave) {
		case TRIG:
			return trig;
		case SAWTRIG:
			return sawtrig;
		case SAW:
			return saw;
		case SQUARE:
			return square;
		case WIDERECT:
			return widerect;
		case NARROWRECT:
			return narrowrect;
		default:
			return NULL;
	}
}

void Waveforms::initializeWaves(int length, int extraPoints) {
	int i;
	trig = new vector<float> (length);
	sawtrig = new vector<float> (length);
	saw = new vector<float> (length);
	square = new vector<float> (length);
	widerect = new vector<float> (length);
	narrowrect = new vector<float> (length);

	for (i = 0; i < length + extraPoints; i++) {

	}
}

void Waveforms::deleteWaves() {
	delete trig;
	delete sawtrig;
	delete saw;
	delete square;
	delete widerect;
	delete narrowrect;
}
