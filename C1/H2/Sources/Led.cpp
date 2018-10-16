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
Led::Led(gpio_Pin pin):port(pin)
{
	port.setPortMode(gpio_output);
	port.writeBit(1); //!< Apaga o LED.

}

/**
 * @return void
 */
void Led::setOn()
{
	port.writeBit(0); //!< Acende o LED.

}

/**
 * @return void
 */
void Led::setOff()
{
	port.writeBit(1);  //!< Apaga o LED.

}
