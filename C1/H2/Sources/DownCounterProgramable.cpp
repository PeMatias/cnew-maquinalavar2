/**
 * Project Untitled
 */


#include "DownCounterProgramable.h"

/**
 * DownCounterProgramable implementation
 */

/**
 * @param int valor
 */
DownCounterProgramable::DownCounterProgramable(int valor) : DownCounter(valor)
{
    this->data = '0';
}

/**
 * @param writeTE
 * @return void
 */
void DownCounterProgramable::writeData(bool writeTE, char valor)
{
    if(writeTE == 1)
    {
    	this->data = valor;
    }
}
