/*
 * controladorBluetooth.cpp
 *
 *  Created on: 25/11/2018
 *      Author: matheussilva
 */


#include "ControladorBluetooth.h"


ControladorBluetooth::ControladorBluetooth(){};

	void ControladorBluetooth::getDataHC06(uint8_t dado)
	{
		buf = dado;
	}

	uint8_t ControladorBluetooth::writeData()
	{
		return buf;
	}

	bool ControladorBluetooth::getFullBt() // pega da variavel fullBt private
	{
		return fullBt;
	}

	void ControladorBluetooth::writeFullBt(bool boolean) // escreve na variavel fullBt private
	{
		fullBt = boolean;
	}





