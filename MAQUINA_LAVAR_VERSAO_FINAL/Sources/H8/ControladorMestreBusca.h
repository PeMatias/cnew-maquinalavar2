/*
 * ControladorMestreBusca.h
 *
 *  Created on: 20/11/2018
 *      Author: pevic
 */

#ifndef SOURCES_CONTROLADORMESTREBUSCA_H_
#define SOURCES_CONTROLADORMESTREBUSCA_H_

#include "cstdint"

enum Estados {espera,leitura,atualiza,registra,executa,fimCE,fimCM};

class ControladorMestreBusca
{
public:
	ControladorMestreBusca();

	void enable();

	void disable();

	void writeData(uint16_t dtRAM);

	uint16_t readData();

	bool isEnable();

	Estados getState();

	void refreshState();

	void enableCE();

	void disableCE();

	bool isEnableCE();

	void setEndCE(bool valor);

	bool isEndCE();

private:
	volatile uint16_t data;

	Estados stateMachine;

	bool status;

	bool statusCE;

	bool endCE;
};

#endif /* SOURCES_CONTROLADORMESTREBUSCA_H_ */
