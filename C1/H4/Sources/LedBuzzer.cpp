/**
 * Project Untitled
 */


#include "LedBuzzer.h"

/**
 * LedBuzzer implementation
 */


/**
 * @param gpioPin
 */
LedBuzzer::LedBuzzer(gpio_Pin pin) : port(pin) {

	port.setPortMode(gpio_output);
	port.writeBit(0); //!< Apaga o LED.
}

/**
 * @return void
 */
void LedBuzzer::turnOn() {
    port.writeBit(1);
}

/**
 * @return void
 */
void LedBuzzer::turnOff() {
    port.writeBit(0);
}
