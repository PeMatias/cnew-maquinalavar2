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
    this->enable = false;
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
}/*
void DownCounterProgramable::decCounter(bool carryIn, bool clk)
{
    if(carryIn == 1 && clk == 1 && this->enable)
    {
        if(this->data > '0') this->data--;
    }

}*/
