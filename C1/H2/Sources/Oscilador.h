/**
 * Project Untitled
 */


#ifndef _OSCILADOR_H
#define _OSCILADOR_H
#include <mkl_PITPeriodicInterrupt.h>
#include "mkl_PIT.h"


class Oscilador {
public: 
    
	Oscilador();
    
	bool clock();

public:
	mkl_PITInterruptInterrupt pit = mkl_PITInterruptInterrupt(PIT_Ch0);
};

#endif //_OSCILADOR_H
