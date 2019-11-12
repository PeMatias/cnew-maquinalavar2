/**
 * Project Untitled
 */

#include "UpDownCounter.h"

/**
 * UpDownCounter implementation
 */

UpDownCounter::UpDownCounter(int valor) : DownCounter(valor)
{
	this->data = '0';
	this->enable = false;
}

void UpDownCounter::incCounter(bool carryIn, bool clk)
{
    if(carryIn == 1 && clk == 1 && isEnable() )
    {
        if(this->data < '9') this->data++;
        else 	            this->data = '0';
    }
}

bool UpDownCounter::isCarryOut()
{
	if( isEnable() && (readCounter() == '0 ' || readCounter() == '9'))
	{
		return true;
	}
	return false;
}

