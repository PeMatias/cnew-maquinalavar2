/*
 * DecoderCmdAddr.h
 *
 *  Created on: 20/11/2018
 *      Author: pevic
 */

#ifndef DECODERCMDADDR_H_
#define DECODERCMDADDR_H_

#include "cstdint"

class DecoderCmdAddr
{
public:
	DecoderCmdAddr();

	void writeData(uint8_t cmd);

	uint8_t readData();

protected:

	volatile uint8_t data;

};

#endif /* DECODERCMDADDR_H_ */
