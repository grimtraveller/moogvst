#include "basic_blocks.h"

BasicBlock::BasicBlock(int numberOfInputs) {
	this->inputs = new vector<BasicBlock *>(numberOfInputs);
}

BasicBlock::~BasicBlock() {
	delete this->inputs;
}

BasicBlock::setInput(int i, BasicBlock * block)
