/*
 * monitor.h
 *
 *  Created on: 22/11/2018
 *      Author: matheussilva
 */

#ifndef SOURCES_MONITORH7_H_
#define SOURCES_MONITORH7_H_

#include "MKL25Z4.h"
#include "controladorBluetooth.h"
#include "controladorComando.h"
#include "fc.h"
#include "mkl_HC06BluetoothSlave.h"
#include "mkl_GPIOPort.h"

enum Service {esperaa,liga,leituraBT,leituraFC,escreveMemoria,lavagem,desliga};


class MonitorH7
{
public:
	MonitorH7();

	ControladorBluetooth cb;
	ControladorComando cc;
	fc fila;

	void setup();
	void readInputs();
	void executeServices(int botao,bool &ledVerde,bool &ledVermelho, bool &ledAzul,bool &buzzer);
	void delay(uint32_t milliSeconds);
	void reset();
	void writeEndCm();

private:
Service controleMaquinaEstado;

uint8_t dtFc;
bool fullBt;
bool isDataFc;
bool endCm;



};



#endif /* SOURCES_MONITOR_H_ */
