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
	Led(gpio_Pin pin);
    
	void setOn();
    
	void setOff();
private: 
    mkl_GPIOPort port;
};

#endif //_LED_H
