/*
 * botao.cpp
 *
 *  Created on: Aug 27, 2018
 *      Author: Guilherme
 */

#include "botao.h"

Botao::Botao(gpio_Pin pin) : port(pin){
	port.setPortMode(gpio_input);
}


bool Botao::read(){
	return port.readBit();
}




