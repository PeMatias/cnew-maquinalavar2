/*
 * RegistradorInstrucao.h
 *
 *  Created on: 20/11/2018
 *      Author: pevic
 */

#ifndef SOURCES_REGISTRADORINSTRUCAO_H_
#define SOURCES_REGISTRADORINSTRUCAO_H_

#include "cstdint"

class RegistradorInstrucao
{
public:
	RegistradorInstrucao();

	void writeData(uint16_t dtRAM);

	uint16_t readData();

private:
	volatile uint16_t data;
};

#endif /* SOURCES_REGISTRADORINSTRUCAO_H_ */
