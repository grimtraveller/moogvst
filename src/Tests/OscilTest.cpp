/*
 * OscilTest.cpp
 *
 *  Created on: 17/08/2010
 *      Author: Bruno Figueira "Jedi" Lourenço
 */

#include "../basic_blocks.h"
#include "wav.h"
#include <stdint.h>

int main(void) {
	/*
	 *
	 * Importante! É preciso chamar initializeWaves antes de tudo!
	 *
	 */
	Waveforms::initializeWaves(1024, 2);
	Oscil oscil;
	Number freq(440.0f);
	Number amp(1.0f);
	int16_t samples[44100 * 2];

	oscil.setFrequencyInput(&freq);
	oscil.setAmplitudeInput(&amp);

	for (int i = 0; i < 44100 * 2; i++) {
		samples[i] = oscil.getNextValue() * 30000;
	}
	write_wave("Trig_test.wav", 44100, samples, 2.0);

	oscil.setWavetable(SQUARE);
	for (int i = 0; i < 44100 * 2; i++) {
		samples[i] = oscil.getNextValue() * 30000;
	}
	write_wave("Square_test.wav", 44100, samples, 2.0);

	oscil.setWavetable(SAW);
	for (int i = 0; i < 44100 * 2; i++) {
		samples[i] = oscil.getNextValue() * 30000;
	}
	write_wave("Saw_test.wav", 44100, samples, 2.0);
	return 0;
}
