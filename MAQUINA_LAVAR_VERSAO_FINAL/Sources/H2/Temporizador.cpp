/*
 * Temporizador.cpp
 *
 *  Created on: Oct 18, 2018
 *      Author: Guilherme
 */

#include "Temporizador.h"

Temporizador::Temporizador(int modulo) : TEuni(modulo) , TEdez(modulo) {
	// TODO Auto-generated constructor stub
	setEnableTemporizador(false);
	temporizacaoEmProgresso = false;
}

void Temporizador::contar(bool isCarryOutClock1hz){
	//if ( isTemporizacaoEmProgresso() ){
	TEdez.decCounter(TEuni.isCarryOut()	,isCarryOutClock1hz);
	TEuni.decCounter(1					,isCarryOutClock1hz);
	if( isFimTemporizacao() ){
		reset();
	}
}

void Temporizador::setEnableTemporizador(bool enable){
	TEdez.enable = enable;
	TEuni.enable = enable;
}

void Temporizador::writeData(char dezData, char uniData){
	temporizacaoEmProgresso = true;
	TEuni.writeData(true,uniData);
	TEdez.writeData(true,dezData);
}

bool Temporizador::isFimTemporizacao(){
	return TEuni.isCarryOut() && TEdez.isCarryOut() && onTE();
}

bool Temporizador::onTE(){
	return TEdez.enable && TEuni.enable;
}

void Temporizador::reset(){
	TEdez.clearCounter();
	TEuni.clearCounter();
	temporizacaoEmProgresso = false;
}

char Temporizador::getUni(){
	return TEuni.readCounter();
}

char Temporizador::getDez(){
	return TEdez.readCounter();
}
