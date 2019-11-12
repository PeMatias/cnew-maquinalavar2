/*
 * Temporizador.h
 *
 *  Created on: Oct 18, 2018
 *      Author: Guilherme
 */

#ifndef SOURCES_TEMPORIZADOR_H_
#define SOURCES_TEMPORIZADOR_H_

#include "DownCounterProgramable.h"
#include "DivFreq.h"

class Temporizador {

private:

	DownCounterProgramable TEuni;
	DownCounterProgramable TEdez;
	bool temporizacaoEmProgresso;

public:
	Temporizador(int);
	void setEnableTemporizador(bool enable);
	void contar(bool isCarryOutClock1hz);
	void writeData(char uniData, char dezData);
	bool isFimTemporizacao();
	bool onTE();
	void reset();
	char getUni();
	char getDez();

};

#endif /* SOURCES_TEMPORIZADOR_H_ */
