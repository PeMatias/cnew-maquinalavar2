/**
 * Project Untitled
 */


#ifndef _BOTAO2_H
#define _BOTAO2_H

#include "Botao.h"
#include "mkl_GPIOPort.h"


class Botao2: public Botao {
public: 
    
/**
 * @param pin
 */
	Botao2(gpio_Pin pin);
};

#endif //_BOTAO2_H
