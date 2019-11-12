/**
 * Project Untitled
 */


#include "Led.h"

/**
 * LedBuzzer implementation
 */


/**
 * @param gpioPin
 */
Led::Led(gpio_Pin pin) : port(pin) {

	port.setPortMode(gpio_output);
	setOff();
}

/**
 * @return void
 */
void Led::setOn() {
    port.writeBit(1);
}

/**
 * @return void
 */
void Led::setOff() {
    port.writeBit(0);
}

void Led::tooggle(){
	port.toogleBit();
}


void Led::set(bool state) {
    if ( state )
    	setOn();
    else
    	setOff();
}
