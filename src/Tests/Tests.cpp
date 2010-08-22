/*
 * OscilTest.cpp
 *
 *  Created on: 17/08/2010
 *      Author: Bruno Figueira "Jedi" Lourenço
 */
#include "../basic_blocks.h"
#include "wav.h"

#include <stdint.h>
#include <stdio.h>
int main(void) {
	/*
	 *
	 * Importante! É preciso chamar initializeWaves antes de tudo!
	 *
	 */
	Waveforms::initializeWaves(1024, 2);
	Oscil oscil;
	Noise noise;
	Number freq1(220.0f);
	Number freq2(880.0f);
	Number amp(1.0f);
	ADSR adsr;
	Filter filter;
	int16_t samples[44100 * 2];
	Number quality(0.0);
	
	

	oscil.setFrequencyInput(&freq1);
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

	oscil.setWavetable(SQUARE);
	for (int i = 0; i < 44100 * 2; i++) {
		samples[i] = oscil.getNextValue() * 30000;
	}
	write_wave("Saw_test.wav", 44100, samples, 2.0);

	for (int i = 0; i < 44100 * 2; i++) {
		samples[i] = noise.getNextValue() * 30000;
	}
	write_wave("Noise_test.wav", 44100, samples, 2.0);
	

	
	noise.setType(PINK);
	for (int i = 0; i < 44100 * 2; i++) {
	samples[i] = noise.getNextValue() * 30000;
	}
	write_wave("Pink_noise.wav", 44100, samples, 2.0);

	noise.setType(PINK);
	for (int i = 0; i < 44100 * 2; i++) {
			samples[i] = noise.getNextValue() * 30000;
	}
	write_wave("Pink_Noise_test.wav", 44100, samples, 2.0);

	oscil.setAmplitudeInput(&adsr);
	oscil.setWavetable(TRIG);
	adsr.setAttack_sharpness(10000);
	adsr.setAttack(0.2);
	adsr.setDecay(0.1);
	adsr.setSustain(0.2);
	adsr.setRelease(1.0);
	adsr.setReleaseON(true);
	for (int i = 0; i < 44100 * 2; i++) {
		samples[i] = oscil.getNextValue() * 30000;
	}
	write_wave("ADSR_test.wav", 44100, samples, 2.0);
	

	noise.setType(WHITE);

		filter.setFrequencyInput(&freq2);
	filter.setQualityInput(&quality);
	adsr.resetBlock();
	filter.setInputSignal(&oscil);
	
	for (int i = 0; i < 44100 * 2; i++) {
		samples[i] = filter.getNextValue() * 30000;		
		}
	write_wave("filter_test1.wav", 44100, samples, 2.0);
	
	quality.setNumber(3.0);
oscil.setWavetable(SQUARE);
	oscil.setAmplitudeInput(&adsr);
	filter.setInputSignal(&oscil);
	for (int i = 0; i < 44100 * 2; i++) {
		samples[i] = filter.getNextValue() * 30000;
		
	}
	write_wave("filter_test2.wav", 44100, samples, 2.0);
	
	
	return 0;
}
