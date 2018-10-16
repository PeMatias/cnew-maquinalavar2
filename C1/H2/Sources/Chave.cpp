/**
 * Project Untitled
 */


#include "Chave.h"

/**
 * Chave implementation
 */


/**
 * @param pin
 */
Chave::Chave(gpio_Pin pin): port(pin)
{
	  this->port.setPortMode(gpio_input);
	  //this->port.setPullResistor(gpio_pullUpResistor);
}

/**
 * @return bool
 */
bool Chave::isOn() {
	if(	this->port.readBit()  == 1) return true;
	return false;
}

/**
 * @return bool
 */
bool Chave::isOff() {
	if(	this->port.readBit() == 0) return true;
	return false;
}



