#include "basic_blocks.h"

BasicBlock::BasicBlock(int numberOfInputs) :
	inputs(numberOfInputs) {
}

void BasicBlock::setInput(int i, BasicBlock * block) {
	(this->inputs)[i] = block;
}

void BasicBlock::generateSamples(float * output, int sampleNum) {
	for (int i = 0; i < sampleNum; i++) {
		output[i] = getNextValue();
	}
}

void BasicBlock::resetBlock() {

}
