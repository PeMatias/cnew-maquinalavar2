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
	this->enable = false;
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
void DownCounter::decCounter(bool carryIn, bool clk)
{
    if(carryIn == 1 && clk == 1 && isEnable())
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
bool DownCounter::isEnable()
{
	return this->enable;
}
/**
 * @return bool
 */
bool DownCounter::isCarryOut()
{
	if( isEnable() && readCounter() == '0')
	{
		return true;
	}
	return false;
}

void DownCounter::setEnable(bool valor)
{
	this->enable = valor;
}




