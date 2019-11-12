/*
 * DecoderBcdAscii.cpp
 *
 *  Created on: 14/10/2018
 *      Author: matheussilva
 */


/*
 * DecoderBcdAscii.cpp
 *
 *  Created on: 10/10/2018
 *      Author: matheussilva
 */

#include "DecoderBcdAscii.h"


DecoderBcdAscii::DecoderBcdAscii(){

}

void DecoderBcdAscii:: writeData(char value)
{

      caractere = (value);
}


char DecoderBcdAscii:: readData()
{
	return caractere;
}

void DecoderBcdAscii:: setCarryIn(int carryin)
{
	carry = carryin;
	}





