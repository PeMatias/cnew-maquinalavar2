/**
 * Project Untitled
 */
/*
extern "C"
	{
	  void PIT_IRQHandler(void)
	  {
	    pit.clearInterruptFlag();
	  }
	}*/
#include "Oscilador.h"


/**
 * Oscilador implementation
 */

Oscilador::Oscilador()
{
	this->pit = mkl_PITInterruptInterrupt(PIT_Ch0);
	this->pit.enablePeripheralModule();
	this->pit.setPeriod(1000000);//10ms
	this->pit.resetCounter();
	this->pit.enableInterruptRequests();

}

/**
 * @return bool
 */
bool Oscilador::clock()
{
	return false;
}
