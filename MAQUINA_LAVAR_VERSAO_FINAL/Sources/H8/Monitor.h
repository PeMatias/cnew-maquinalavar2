/*
 * Monitor.h
 *
 *  Created on: 27/11/2018
 *      Author: pevic
 */

#ifndef SOURCES_MONITOR_H_
#define SOURCES_MONITOR_H_
#include "cstdint"
// View

//Comunicação
#include "ControladorMestreBusca2.h"
#include "ContadorPrograma2.h"
#include "Memoria2.h"

//Saida
#include "Led.h"
#include "Botao.h"
#include "DecoderCmdAddr.h"
#include "RegistradorInstrucao.h"

enum ServiceH8{inicioLavagem,executaLavagem,fimLavagem, reset};

typedef struct {
	volatile bool enCE;
	volatile bool endCM;
	volatile bool buzzer;
} SaidasH8;


class Monitor {
public:

	Monitor();
	//Botao wrPC = Botao(gpio_PTC0);
	//Botao endCE = Botao(gpio_PTC11);
	//Botao enCM = Botao(gpio_PTD4);
	//Botao tipoLavagem = Botao(gpio_PTC0);

	DecoderCmdAddr decoder;
	ContadorPrograma2 pc;
	ControladorMestreBusca2 cm;
	Memoria2 mem;
	RegistradorInstrucao ri;

	//Led enCE = Led(gpio_PTB19); // Led Verde
	//Led endCM = Led(gpio_PTB18);//Led Vermelho
	//Led buzzer = Led(gpio_PTA12);

	//ViewBotao wrPC();
	void setup();

	void readInputs(bool,bool,bool,uint8_t);

	void executeService();

	void writeOutputs();

	SaidasH8 getSaidas();

	ServiceH8 atual = reset;
	uint8_t dtFC; // Comando do H7
	uint8_t dtPC; // Programa decodificado
	uint8_t dtAddr;
	uint16_t dtRAM;

protected:

	SaidasH8 saidas;


};

#endif /* SOURCES_MONITOR_H_ */
