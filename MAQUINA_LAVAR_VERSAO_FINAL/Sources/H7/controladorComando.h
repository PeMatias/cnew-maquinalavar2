/*
 * controladorComando.h
 *
 *  Created on: 25/11/2018
 *      Author: matheussilva
 */

#ifndef SOURCES_CONTROLADORCOMANDO_H_
#define SOURCES_CONTROLADORCOMANDO_H_




#include "MKL25Z4.h"



class ControladorComando
{
public:

	ControladorComando();

	void writeRdBt(bool boolean);
	bool getRdBt();


	void writeRdFc(bool boolean);
	bool getRdFc();

	void writeWrFc(bool boolean);
	bool getWrFc();

	void writeBeep(bool boolean);
	bool getBeep();

	void writeOnOffCm(bool boolean);
	bool getOnOffCm();

	void writeEnCm(bool boolean);
	bool getEnCm();

	void writeWrPc(bool boolean);
	bool getWrPc();

	void writeRecebeDtFc(uint8_t dtFc);
	uint8_t getRecebeDtFc();

	void delay(uint16_t n);


private:

uint8_t recebeDtFc;

bool rdBt;

bool rdFc;
bool wrFc;

bool beep;

bool onOffCm;

bool enCm;

bool wrPc;

};


#endif /* SOURCES_CONTROLADORCOMANDO_H_ */
