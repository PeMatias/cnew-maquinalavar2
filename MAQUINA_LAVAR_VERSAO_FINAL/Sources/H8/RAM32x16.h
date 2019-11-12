/*
 * RAM32x16.h
 *
 *  Created on: 20/11/2018
 *      Author: pevic
 */

#ifndef SOURCES_RAM32X16_H_
#define SOURCES_RAM32X16_H_

#include "cstdint"

class RAM32x16
{
public:
	RAM32x16();

	void writeAddr(uint8_t addr);

	uint16_t readData();

protected:
	volatile uint16_t data[32];

	volatile uint8_t addr;
};

#endif /* SOURCES_RAM32X16_H_ */
