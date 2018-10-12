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
Chave::Chave(gpio_Pin pin)
{
	  this->port.setPortMode(gpio_input);
	  this->port.setPullResistor(gpio_pullUpResistor);
}

/**
 * @return bool
 */
bool Chave::isOn() {
    return false;
}

/**
 * @return bool
 */
bool Chave::isOff() {
    return false;
}
