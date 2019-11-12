/**
 * Project Untitled
 */

#include "mkl_GPIOPort.h"

#ifndef _LED_H
#define _LED_H

class Led {
protected:
	mkl_GPIOPort port;

public:

	/**
	 * @param gpioPin
	 */
	Led(gpio_Pin);

	void setOn();

	void setOff();

	void tooggle();

	void set(bool state);

};

#endif //_LEDBUZZER_H
