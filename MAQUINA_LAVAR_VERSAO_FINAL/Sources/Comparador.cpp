/**
 * Project Untitled
 */

#include <cstdint>
#include "Comparador.h"
#include <string.h>


Comparador::Comparador()
{
	data1[0] ='0';
	data1[1] ='0';
	data2[0] ='0';
	data2[1] ='0';
}



bool Comparador::isEqual()
{
	return  10*data1[0]+data1[1] == 10*data2[0]+data2[1];
}

bool Comparador::isGreat()
{
    return 10*data1[0]+data1[1] > 10*data2[0]+data2[1] ;
}

bool Comparador::isLess()
{
    return 10*data1[0]+data1[1] < 10*data2[0]+data2[1];
}

void Comparador::writeData1(char valor[])
{
	data1[0] = valor[0];
	data1[1] = valor[1];
}

void Comparador::writeData2(char valor[])
{
	data2[0] = valor[0];
	data2[1] = valor[1];
}
