/**
 * Project Untitled
 */


#ifndef _LED_H
#define _LED_H
#include "mkl_GPIOPort.h"


class Led {
public: 
    
/**
 * @param pin
 */
	/*!
	 * Construtor padrão da classe (apaga o LED).
	 */
	Led(gpio_Pin);
	/*!
	 * Métodos para mudar o estado do LED.
	 */
	void setOn();
	void setOff();

private: 
    mkl_GPIOPort port;
};

#endif //_LED_H
