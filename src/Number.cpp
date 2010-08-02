/*
 * Number.cpp
 *
 *  Created on: 23/07/2010
 *      Author: Bruno Figueira "Jedi" Lourenço
 */

#include "basic_blocks.h"

Number::Number(float number) : BasicBlock(0),number(number) {


}

Number::~Number() {
	// TODO Auto-generated destructor stub
}


float Number::getNextValue(){
	return number;
}

void Number::setNumber(float number){
	this->number = number;
}

float Number::getNumber() {
	return number;
}
