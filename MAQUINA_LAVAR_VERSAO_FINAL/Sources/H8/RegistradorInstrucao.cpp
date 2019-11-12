/*
 * RegistradorInstrucao.cpp
 *
 *  Created on: 20/11/2018
 *      Author: pevic
 */

#include "RegistradorInstrucao.h"

RegistradorInstrucao::RegistradorInstrucao()
{
	// TODO Auto-generated constructor stub
	data = 0x0;
}
void RegistradorInstrucao::writeData(uint16_t dtRAM)
{
	data = dtRAM;
}

uint16_t RegistradorInstrucao::readData()
{
	return data;
}

