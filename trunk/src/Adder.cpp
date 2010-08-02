/*
 * Adder.cpp
 *
 *  Created on: 22/07/2010
 *      Author: Bruno Figueira "Jedi" Lourenço
 */

#include "basic_blocks.h"

Adder::Adder(int numberOfInputs) : BasicBlock(numberOfInputs) {

}

Adder::~Adder() {

}

float Adder::getNextValue() {
	float acc = 0;
	for ( vector<BasicBlock *>::iterator it = inputs.begin(); it < inputs.end(); it++ ){
		acc += (*it)->getNextValue();
	}
	return acc;
}
