/*
 * Simulador.cpp
 *
 *  Created on: Oct 26, 2018
 *      Author: Guilherme
 */

#include "Simulador.h"

Simulador::Simulador(int modulo) : NLuni(modulo), NLdez(modulo), logica("07") {

	//Verificar o enable count
	setEnableSimulador(false);
	setUpDown(false);
}

void Simulador::setEnableSimulador(bool enable){

	NLuni.enable = NLdez.enable = enable;

}

void Simulador::setUpDown(bool updown_){

	updown = updown_;
}

void Simulador::setDtRi(char * dtRI_){
	logica.writeMax(dtRI_);
}

char Simulador::getUni(){
	return NLuni.readCounter();
}

char Simulador::getDez(){
	return NLdez.readCounter();
}

bool Simulador::isFull(){
	char nivel[2] =  {NLdez.readCounter(), NLuni.readCounter()};
	return logica.isFull(nivel);
}

void Simulador::reset(){
	NLuni.clearCounter();
	NLdez.clearCounter();

}

bool Simulador::isEmpty(){
	char nivel[2] =  {NLdez.readCounter(), NLuni.readCounter()};
	return logica.isEmpty(nivel);
}

bool Simulador::getEnableSimulador(){
	return NLuni.enable && NLdez.enable;
}

void Simulador::contar(bool carryOut1Hz){

	if(updown && !isFull()) // Contage Crescente
	{
		NLdez.incCounter(NLuni.isCarryOut()	,carryOut1Hz);
		NLuni.incCounter(1					,carryOut1Hz);
	}
	else if(!updown && !isEmpty()) // Contagem Decrescente
	{
		NLuni.decCounter(1					,carryOut1Hz);
		NLdez.decCounter(NLuni.isCarryOut()	,carryOut1Hz);
	}

}

bool Simulador::isFimSimulacao(){
	return  ( ( updown && isFull() ) || ( !updown && isEmpty() ) ) && getEnableSimulador();
}

bool Simulador::getUpDown(){
	return updown;
}
