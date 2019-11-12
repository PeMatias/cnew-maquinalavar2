/*
 * ControladorMestreBusca.cpp
 *
 *  Created on: 20/11/2018
 *      Author: pevic
 */

#include "ControladorMestreBusca.h"

ControladorMestreBusca::ControladorMestreBusca()
{

}

void ControladorMestreBusca::enable()
{
	status = true;
}

void ControladorMestreBusca::enableCE()
{
	statusCE = true;
}

void ControladorMestreBusca::disable()
{
	status = false;
}

void ControladorMestreBusca::disableCE()
{
	statusCE = false;
}

void ControladorMestreBusca::writeData(uint16_t dtRAM)
{
	data = dtRAM;
}

uint16_t ControladorMestreBusca::readData()
{
	return data;
}


bool ControladorMestreBusca::isEnable()
{
	return status;
}

bool ControladorMestreBusca::isEnableCE()
{
	return statusCE;
}
void ControladorMestreBusca::setEndCE(bool valor)
{
	endCE = valor;
}

bool ControladorMestreBusca::isEndCE()
{
	return endCE;
}

Estados ControladorMestreBusca::getState()
{
	return stateMachine;
}

