/*
 * ControladorH6.h
 *
 *  Created on: Dec 9, 2018
 *      Author: Guilherme
 */

#ifndef SOURCES_H6_CONTROLADORH6_H_
#define SOURCES_H6_CONTROLADORH6_H_

#include "Led.h"
#include "cstdint"
#include "H5/mkl_TPMPulseWidthModulation.h"

typedef struct {
	volatile bool enTE;
	volatile bool enNL;
	bool UpDown;
	volatile bool endCE;
} SaidasH6;

typedef enum {
	ESPERA,
	SETUP,
	EXECUTA,
	FIM
} EstadosCtr;

class ControladorH6 {

public:
	Led onAgua;
	Led onSabao;
	Led onDreno;
	//Led onGiraMotor;  //TEMPORÁRI
	SaidasH6 saida;
	mkl_TPMPulseWidthModulation pwm_direito;
	mkl_TPMPulseWidthModulation pwm_esquerdo;
	EstadosCtr estados;
	//int status;

	// Entradas
	bool enCE, endTE, endNL;
	uint8_t dtRi;




	ControladorH6(tpm_Pin,tpm_Pin);
	void setup(uint8_t dtRi);
	void espera();
	void T_Agua();
	void T_Sabao();
	void Dreno();
	void AgitacaoEnxague();
	void Molho();
	void setGiroRapido();
	void setGiroLento();
	void setGiroZero();
	void fim();
	void enCEAction(uint8_t dtRi);
	bool endNLAction();
	bool endTEAction();
	void executeService();
	void setDirecaoMotor(bool);
	EstadosCtr getEstado();
	SaidasH6 getSaidasH6();
	void refreshEstado();

	bool eoc();
	bool isEnable();
	void writeOutputs();

	//virtual ~Controlador();
};

#endif /* SOURCES_H6_CONTROLADORH6_H_ */
