/*
 * GiroControle.h
 *
 *  Created on: 04/12/2018
 *      Author: adrie
 */

#ifndef SOURCES_GIROCONTROLE_H_
#define SOURCES_GIROCONTROLE_H_

#include "mkl_TPMPulseWidthModulation.h"

class GiroControle
{
public:

	GiroControle(tpm_Pin,tpm_Pin);

	void delayMs(int time);

	void setGiroRapido();

	void setGiroLento();

	void setGiroAlternado();

	void setGiroZero();

	void enCEAction(uint8_t dtRi);

	void endTEAction();


protected:
	bool condicao;
	mkl_TPMPulseWidthModulation pwm_direito;
	mkl_TPMPulseWidthModulation pwm_esquerdo;

	// Definition of the onoff logic state machine
	typedef enum {
		ST_OFF,
		ST_GIRO,
		ST_ON,
		ST_WAIT
	} States;

	typedef struct {
		bool enTE;
		bool enNL;
		bool UpDown;
		bool modoGiro;
	} Saidas;

};

#endif /* SOURCES_GIROCONTROLE_H_ */
