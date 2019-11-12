/*
 * Simulador.h
 *
 *  Created on: Oct 26, 2018
 *      Author: Guilherme
 */

#ifndef SOURCES_H3_SIMULADOR_H_
#define SOURCES_H3_SIMULADOR_H_

#include "UpDownCounter.h"
#include "Logica.h"

class Simulador {

protected:

	UpDownCounter NLuni;
	UpDownCounter NLdez;
	Logica logica;
	bool updown;

public:

	Simulador(int);
	void setEnableSimulador(bool);
	bool getEnableSimulador();
	void setUpDown(bool);
	char getUni();
	char getDez();
	//char * getNivel();
	void setDtRi(char * dtRI_);
	bool isEmpty();
	bool isFull();
	void reset();
	void contar(bool);
	bool isFimSimulacao();
	bool getUpDown();

};

#endif /* SOURCES_H3_SIMULADOR_H_ */
