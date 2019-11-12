/*
 * ControladorH7.h
 *
 *  Created on: Dec 13, 2018
 *      Author: Guilherme
 */

#ifndef SOURCES_H7_CONTROLADORH7_H_
#define SOURCES_H7_CONTROLADORH7_H_
#include "cstdint"
#include "../H1/mkl_LCD.h"
#include "Led.h"

typedef struct {
	volatile bool enCM;
	volatile bool wrPC;
	volatile bool lcd;
	volatile bool buzzer;
	volatile bool perdaBT;
	volatile bool standbye;
} SaidasH7;

typedef enum {
	DESLIGADA,
	ESPERA_LAVAGEM,
	ESCREVE_PC,
	LAVAGEM_AUTOMATICA,
	FIM_LAVAGEM
} EstadosH7;

namespace std {

class ControladorH7 {
public:

	ControladorH7();
	uint16_t getDtFc();
	void setDtFc(uint16_t dtFc);
	bool isEndCm();
	void setEndCm(bool endCm);
	EstadosH7 getEstadoH7();
	bool isH8inicioLavagem();
	void setH8inicioLavagem(bool h7inicioLavagem);
	SaidasH7 getSaidaH7();


protected:

	EstadosH7 estadoH7;
	SaidasH7 saidaH7;

	// Entradas
	uint16_t dtFC;
	bool endCM;
	bool H8inicioLavagem;
	void delayMs(uint16_t);

public:

	void refreshEstado();
	void writeOutputs();

};

} /* namespace std */

#endif /* SOURCES_H7_CONTROLADORH7_H_ */
