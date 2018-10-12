/**
 * Project Untitled
 */


#ifndef _BOTAO_H
#define _BOTAO_H
#include "mkl_GPIOPort.h"


class Botao {
public: 
    
/**
 * @param pin
 */
	Botao(gpio_Pin pin);
    
	bool isOn();
    
	bool isOff();
private: 
    mkl_GPIOPort port;
};

#endif //_BOTAO_H
