/**
 * Project Untitled
 */


#include "DownCounter.h"

/**
 * DownCounter implementation
 */


/**
 * @param valor
 */
DownCounter::DownCounter(int valor)
{
	this->module = valor;
	this->data = '0' +( valor -1) ;
}

/**
 * @return void
 */
void DownCounter::clearCounter()
{
	this->data = '0';
}

/**
 * @param carryIn
 * @param clk
 * @param enable
 * @return void
 */
void DownCounter::decCounter(bool carryIn, bool clk, bool enable)
{
    if(carryIn == 1 && clk == 1 && enable == 1)
    {
        if(this->data > '0') this->data--;
        else 	            this->data = '0' + (this->module -1);
    }

}

/**
 * @return char
 */
char DownCounter::readCounter()
{
    return this->data;
}

/**
 * @return bool
 */
bool DownCounter::isCarryOut(bool enable)
{
	if(enable == 1  and readCounter() == '0')
	{
		return true;
	}
	return false;
}
