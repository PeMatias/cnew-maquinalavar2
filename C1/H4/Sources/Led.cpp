/*!
 * Implementação da classe LED.
 */

#include "led.h"

Led::Led(gpio_Pin pin) : port(pin) {

	port.setPortMode(gpio_output);
	port.writeBit(0); //!< Apaga o LED.

}

void Led::setOn(){
	port.writeBit(1); //!< Acende o LED.
}

void Led::setOff(){
	port.writeBit(0);  //!< Apaga o LED.
}
