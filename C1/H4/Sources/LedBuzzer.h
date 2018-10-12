/**
 * Project Untitled
 */


#include "mkl_GPIOPort.h"

#ifndef _LEDBUZZER_H
#define _LEDBUZZER_H

class LedBuzzer {
protected: 
    mkl_GPIOPort port;
    
/**
 * @param gpioPin
 */
LedBuzzer(gpio_Pin);
    
void turnOn();
    
void turnOff();
};

#endif //_LEDBUZZER_H
