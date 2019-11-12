/*
 * ContadorPrograma.cpp
 *
 *  Created on: 20/11/2018
 *      Author: pevic
 */

#include "ContadorPrograma.h"

ContadorPrograma::ContadorPrograma()
{
    data = 0x00;
}

void ContadorPrograma::writeData(uint8_t addr)
{
    data = addr;
}

uint8_t ContadorPrograma::readData()
{
	return data;
}

void ContadorPrograma::incCounter(bool cin)
{
    if(cin == 1) data++;
}

void ContadorPrograma::reset()
{
	data = 0x0;
}
