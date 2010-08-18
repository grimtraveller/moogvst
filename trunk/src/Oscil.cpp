/*
 * Oscil.cpp
 *
 *  Created on: 23/07/2010
 *      Author: Bruno Figueira "Jedi" Lourenço
 */

#include "basic_blocks.h"
#include "globals.h"

Oscil::Oscil() :
	BasicBlock(2), table(*(Waveforms::getWaveform(TRIG))), increment(0.0),
			previous_phase(0.0) {

}

Oscil::Oscil(wavetype_t wave) :
	BasicBlock(2), table(*(Waveforms::getWaveform(wave))), increment(0.0),
			previous_phase(0.0) {

}

void Oscil::setWavetable(wavetype_t wave) {
	table = *(Waveforms::getWaveform(wave));
}

void Oscil::setWavetable(vector<float> & table) {
	this->table = table;
}

void Oscil::setFrequencyInput(BasicBlock * block) {
	(this->inputs)[0] = block;
}

void Oscil::setAmplitudeInput(BasicBlock * block) {
	(this->inputs)[1] = block;
}

float Oscil::getNextValue() {
	float phase;
	float aux;
	float freq;
	float amp;
	int table_length;

	freq = inputs[0]->getNextValue();
	amp = inputs[1]->getNextValue();
	/*Assume que a tabela tem dois pontos extras no final*/
	table_length = table.size() - 2;
	increment = (float) table_length * freq / sample_rate;
	phase = previous_phase + increment;
	/*Pega a parte fracionária da fase*/
	aux = phase - (int) phase;

	phase = (int) phase % table_length;
	/*
	 * Soma a parte fracionária à fase. Isso só é útil no
	 * caso de utilizar interpolação
	 */
	phase += aux;
	previous_phase = phase;

	return linear_interpolation(phase)*amp;
}

float Oscil::cubic_interpolation(float phase)const{
	float x0,x1,x2,x3;
	float y,y0,y1,y2,y3;
	float frac;

	x1 = (int) phase;
	x0 = x1 - 1;
	x2 = x1 + 1;
	x3 = x1 + 2;
	frac = phase - x1;

	y1 = table[x1];
	y2 = table[x2];
	y3 = table[x3];

	if (x1 <= 0 ){
		int table_length = table.size() - 2;
		y0 = table[table_length - 1];
	}
	else{
		y0 = table[x1 - 1];
	}

	/*Apenas divide a fórmula em duas partes para facilitar a leitura*/
	y = -frac*(frac-1)*(frac-2)*y0/6.0 + (frac+1)*(frac-1)*(frac-2)*y1/2.0;
	y += -(frac+1)*(frac)*(frac-2)*y2/2.0 + (frac+1)*(frac)*(frac-1)*y3/6.0;


	return y;
}

float Oscil::linear_interpolation(float phase)const{
	int x1,x2;
	float y1,y2,y;

	x1 = (int) phase;
	x2 = (int) phase + 1;

	y1 = table[x1];
	y2 = table[x2];

	y = y1 + (phase - x1)*(y2-y1);

	return y;
}

void Oscil::reset_block(void){
	increment = 0.0;
	previous_phase = 0.0;
}
