/*
 * ControladorMestreBusca2.h
 *
 *  Created on: 27/11/2018
 *      Author: pevic
 */

#ifndef SOURCES_CONTROLADORMESTREBUSCA2_H_
#define SOURCES_CONTROLADORMESTREBUSCA2_H_

#include "ControladorMestreBusca.h"

class ControladorMestreBusca2: public ControladorMestreBusca {
public:
	ControladorMestreBusca2();

private:
	volatile uint16_t data;

	Estados stateMachine;

	volatile bool status;

	volatile bool statusCE;

	volatile bool endCE;
};

#endif /* SOURCES_CONTROLADORMESTREBUSCA2_H_ */
