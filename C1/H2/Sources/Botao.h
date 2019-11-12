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
	/*!
		 * M�todo para realizar a leitura do estado do bot�o: true ou false.
	 */
	bool read();

private: 
    mkl_GPIOPort port;
};

#endif //_BOTAO_H
