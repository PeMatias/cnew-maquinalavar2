/**
 * Project Untitled
 */


#ifndef _CHAVE_H
#define _CHAVE_H
#include "mkl_GPIOPort.h"

class Chave {
public: 
    
/**
 * @param pin
 */
	Chave(gpio_Pin pin);
    
	bool isOn();
    
	bool isOff();
private: 
    mkl_GPIOPort port;
};

#endif //_CHAVE_H
