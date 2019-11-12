/*
 * RAM32x16.cpp
 *
 *  Created on: 20/11/2018
 *      Author: pevic
 */

#include "RAM32x16.h"

RAM32x16::RAM32x16()
{
	addr = 0x00;

}


uint16_t RAM32x16::readData()
{
	return data[addr];
}

void RAM32x16::writeAddr(uint8_t addr)
{
    this->addr = addr;
}

