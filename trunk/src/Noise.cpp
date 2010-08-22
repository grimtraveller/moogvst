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

/*
 * Okay, here is the algorithm that includes a coefficient set to cover
 *  approximately 9 octaves conforming to the "pink" 1/f power distribution.
 *  First, we need to define the parameters. The pP and the pA parameters are
 *  the amplitude scaling and probability of update parameters described 
 * in http://home.earthlink.net/~ltrammell/tech/pinkalg.htm.
 * 
 * referencia:  http://home.earthlink.net/~ltrammell/tech/newpink.htm
 * 
 * */
float generatePinkNoise(){
	
		float pA[] =   {  3.8024,    2.9694,    2.5970,    3.0870,    3.4006};
		float pP[] =   {  0.00198,   0.01280,   0.04900,   0.17000,   0.68200 };
		float pSUM[] = {  0.00198,   0.01478,   0.06378,   0.23378,   0.91578};
		float acc=0;
		float ur2;
   float ur1 = rand()/RAND_MAX;
   for (int i;i<5 && ur1<=pSUM[i];i++){
         ur2 = rand()/RAND_MAX;
         acc+=2*(ur2-0.5)*pA[i];
	}
	return acc;
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
