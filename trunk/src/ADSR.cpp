/*
 * ADSR.cpp
 *
 *  Created on: 18/08/2010
 *      Author: Bruno Figueira "Jedi" Lourenço
 */

#include "basic_blocks.h"
#include "globals.h"
#include <cmath>


ADSR::ADSR() :
	BasicBlock(0), current_phase(ATTACK), current_phase_samples(0),
			attack(0.8), decay(0.2), sustain(0.8), release(0.2),
			attack_sharpness(0.5), decay_sharpness(0.5), sustain_amp(0.9),
			release_sharpness(0.5), releaseON(false) {

}

ADSR::ADSR(float attack, float decay, float sustain, float release) :
	BasicBlock(0), current_phase(ATTACK), current_phase_samples(0), attack(
			attack), decay(decay), sustain(sustain), release(release),
			attack_sharpness(0.5), decay_sharpness(0.5), sustain_amp(0.9),
			release_sharpness(0.5), releaseON(false) {

}

void ADSR::resetBlock() {
	current_phase = ATTACK;
}

float ADSR::attack_function() {
	return exp(-attack_sharpness/current_phase_samples + (attack_sharpness/(attack*sample_rate)));
}

float ADSR::decay_function() {
	return exp(log(sustain_amp)*current_phase_samples/(decay*sample_rate));
}

float ADSR::release_function() {
	return sustain_amp*exp(current_phase_samples*(log(0.01) - log(sustain_amp))/(release*sample_rate));
}
float ADSR::getNextValue() {
	float out;
	current_phase_samples++;
	switch (current_phase) {
	case ATTACK:
		out = attack_function();
		if (current_phase_samples > sample_rate * attack) {
			current_phase = DECAY;
			current_phase_samples = 0;
		}
		break;
	case DECAY:
		out = decay_function();
		if (current_phase_samples > sample_rate * decay) {
			current_phase = SUSTAIN;
			current_phase_samples = 0;
		}
		break;
	case SUSTAIN:
		out = sustain_amp;
		if (releaseON && (current_phase_samples > sample_rate * sustain)){
			current_phase = RELEASE;
			current_phase_samples = 0;
		}
		break;
	case RELEASE:
		out = decay_function();
		break;
	}

	return out;
}

float ADSR::getAttack_sharpness() const {
	return attack_sharpness;
}

float ADSR::getDecay_sharpness() const {
	return decay_sharpness;
}

float ADSR::getRelease_sharpness() const {
	return release_sharpness;
}

float ADSR::getSustain_amp() const {
	return sustain_amp;
}

bool ADSR::getReleaseON() const {
	return releaseON;
}

void ADSR::setAttack_sharpness(float attack_sharpness) {
	this->attack_sharpness = attack_sharpness;
}

void ADSR::setDecay_sharpness(float decay_sharpness) {
	this->decay_sharpness = decay_sharpness;
}

void ADSR::setRelease_sharpness(float release_sharpness) {
	this->release_sharpness = release_sharpness;
}

void ADSR::setSustain_amp(float sustain_amp) {
	this->sustain_amp = sustain_amp;
}

void ADSR::setReleaseON(bool on) {
	releaseON = on;
}
