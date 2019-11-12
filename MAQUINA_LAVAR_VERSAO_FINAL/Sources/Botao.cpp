/*
 * botao.cpp
 *
 *  Created on: Aug 27, 2018
 *      Author: Guilherme
 */

#include "Botao.h"

Botao::Botao(gpio_Pin pin) : port(pin){
	port.setPortMode(gpio_input);
	port.setPullResistor(gpio_pullUpResistor);
}


bool Botao::read(){
	return !port.readBit();
}

bool Botao::isOn(){
	return !port.readBit();
}

bool Botao::isOff(){
	return port.readBit();
}


