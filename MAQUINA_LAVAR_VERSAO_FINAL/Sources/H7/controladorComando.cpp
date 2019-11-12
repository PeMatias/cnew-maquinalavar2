/*
 * controladorComando.cpp
 *
 *  Created on: 25/11/2018
 *      Author: matheussilva
 */


#include "ControladorComando.h"


	ControladorComando::ControladorComando(){}


	void ControladorComando::writeRdBt(bool boolean)
	{
		rdBt = boolean;
	}
	bool ControladorComando::getRdBt()
	{
		return rdBt;
	}


	void ControladorComando::writeRdFc(bool boolean)
	{
		rdFc = boolean;
	}
	bool ControladorComando::getRdFc()
	{
		return rdFc;
	}

	void ControladorComando::writeWrFc(bool boolean)
	{
			wrFc = boolean;
	}
	bool ControladorComando::getWrFc()
	{
			return wrFc;
	}

	void ControladorComando::writeBeep(bool boolean)
	{
			beep = boolean;
	}
	bool ControladorComando::getBeep()
	{
			return beep;
	}

	void ControladorComando::writeOnOffCm(bool boolean)
	{
			onOffCm = boolean;
	}
	bool ControladorComando::getOnOffCm()
	{
			return onOffCm;
	}

	void ControladorComando::writeEnCm(bool boolean)
	{
			enCm = boolean;
	}
	bool ControladorComando::getEnCm()
	{
			return enCm;
	}

	void ControladorComando::writeWrPc(bool boolean)
	{
			wrPc = boolean;
	}
	bool ControladorComando::getWrPc()
	{
			return wrPc;
	}

	void ControladorComando::writeRecebeDtFc(uint8_t dtFc)
	{
		recebeDtFc = dtFc;
	}

	uint8_t ControladorComando::getRecebeDtFc()
	{
		return recebeDtFc;
	}

	void ControladorComando::delay(uint16_t n) {
		for (uint16_t i = 0; i < n; i++)
			for (uint16_t j = 0; j < 7000; j++) {}
	}



