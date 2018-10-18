/**
 * Project Untitled
 */


#include "Logica.h"


/**
 * Logica implementation
 */

 // @param empty
 // @param full

Logica::Logica(char *dtRI): Comparador()
{
	max[0] = dtRI[0];
	max[1] = dtRI[1];
}

bool Logica::isEmpty(char *nivel)
{
	writeData1(nivel);
	writeData2(min);
	return isEqual();

}

bool Logica::isFull(char *nivel)
{
	writeData1(nivel);
	writeData2(max);
	return isEqual();
}

bool Logica::isEOC(char *nivel)
{
    return isEmpty(nivel) && isFull(nivel);
}

void Logica::writeMax(char *valor)
{
	this->max[0] = valor[0];
	this->max[1] = valor[1];
}


