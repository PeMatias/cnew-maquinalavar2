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
}

/**
 * @return void
 */
void Led::setOn() {
    return;
}

/**
 * @return void
 */
void Led::setOff() {
    return;
}
