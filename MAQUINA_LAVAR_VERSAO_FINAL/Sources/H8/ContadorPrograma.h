/*
 * ContadorPrograma.h
 *
 *  Created on: 20/11/2018
 *      Author: pevic
 */

#ifndef SOURCES_CONTADORPROGRAMA_H_
#define SOURCES_CONTADORPROGRAMA_H_

#include "cstdint"

class ContadorPrograma
{
public:
	ContadorPrograma();

	void writeData(uint8_t addr);

	uint8_t readData();

	void incCounter(bool cin);

	void reset();

private:

	volatile uint8_t data;
};

#endif /* SOURCES_CONTADORPROGRAMA_H_ */
