/*
 * controladorBluetooth.h
 *
 *  Created on: 25/11/2018
 *      Author: matheussilva
 */

#ifndef SOURCES_CONTROLADORBLUETOOTH_H_
#define SOURCES_CONTROLADORBLUETOOTH_H_


#include "MKL25Z4.h"

class ControladorBluetooth
{
public:
	ControladorBluetooth();

	void getDataHC06(uint8_t dado);

	uint8_t writeData();

	bool getFullBt(); // pega da variavel fullBt private

	void writeFullBt(bool boolean); // escreve na variavel fullBt private

	//bool recebeRdBt(); // recebe o rdBt do contrl de comando



private:

	uint8_t buf; //dado para escrever na memoria
	bool fullBt;
	//bool rdBt;

};




#endif /* SOURCES_CONTROLADORBLUETOOTH_H_ */
