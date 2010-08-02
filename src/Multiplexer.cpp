/*
 * Multiplexer.cpp
 *
 *  Created on: 22/07/2010
 *      Author: Bruno Figueira "Jedi" Lourenço
 */

#include "basic_blocks.h"

Multiplexer::Multiplexer(int numberOfInputs, int selectedInput):
	BasicBlock(numberOfInputs),
	selectedInput(selectedInput){

}

Multiplexer::~Multiplexer() {

}

void Multiplexer::setSelectedInput(int i) {
	selectedInput = i;
}

int Multiplexer::getSelectedInput(){
	return selectedInput;
}

float Multiplexer::getNextValue() {
	return inputs[selectedInput]->getNextValue();
}
