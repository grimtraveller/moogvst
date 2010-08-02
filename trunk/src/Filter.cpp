#include "basic_blocks.h"
#include "globals.h"
#include "math.h"

Filter::Filter(float quality) : 
	BasicBlock(2), previousOutput(0.0), Quality(quality) {

}

void Filter::setInputSignal(BasicBlock * block) {
	(this->inputs)[0] = block;
}

void Filter::setFrequencyInput(BasicBlock * block) {
	(this->inputs)[1] = block;
}

void Filter::setQuality(float quality){
	this->Quality=quality;
	};
	
float Filter::getNextValue(){
	float input;
	float freq;
	float output;
	
	input=inputs[0]->getNextValue();
	freq=inputs[1]->getNextValue();
	
	output=previousOutput+2*Quality*(1-exp(-6.2632*freq/sample_rate))*(tanh(input/Quality)-tanh(previousOutput/Quality));
	return previousOutput=output;
	};
