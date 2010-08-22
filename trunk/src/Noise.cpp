/*
 * Noise.cpp
 *
 *  Created on: 24/07/2010
 *      Author: Bruno Figueira "Jedi" Lourenço
 */

#include "basic_blocks.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

Noise::Noise() : BasicBlock(0) {
	setType(WHITE);
}

float generateWhiteNoise(){
	return (2.0f*rand()/RAND_MAX) - 1.0f;
}
float generatePinkNoise(){
	float alpha=1.0;
	int poles=5;
	float a;
	float multipliers[5];
	(2.0f*rand()/RAND_MAX) - 1.0f;
	for (int i=0;i<poles;i++){
	    a = (i - alpha/2) * a / (i+1);
            multipliers[i] = a;
       }
	return 0.0;
}

void Noise::setType(noisetype_t type){
	this->noise_type = type;

	if (type == WHITE){
		this->noiseGenerator = generateWhiteNoise;
		srand(time(NULL));
	}
	else {
		this->noiseGenerator = generatePinkNoise;
	}
}

noisetype_t Noise::getType() {
	return this->noise_type;
}

float Noise::getNextValue(){
	return this->noiseGenerator();
}
