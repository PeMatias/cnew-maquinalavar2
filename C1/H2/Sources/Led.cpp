/**
 * Project Untitled
 */


#include "Led.h"

/**
 * Led implementation
 */


/**
 * @param pin
 */
Led::Led(gpio_Pin pin)
{
	this->port.setPortMode(gpio_output);
	this->port.writeBit(0); //!< Apaga o LED.

}

/**
 * @return void
 */
void Led::setOn()
{
	this->port.writeBit(1); //!< Acende o LED.

}

/**
 * @return void
 */
void Led::setOff()
{
	this->port.writeBit(0);  //!< Apaga o LED.

}
