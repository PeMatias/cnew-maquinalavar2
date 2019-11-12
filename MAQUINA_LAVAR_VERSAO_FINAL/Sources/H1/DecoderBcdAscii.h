/*
 * DecoderBcdAscii.h
 *
 *  Created on: 14/10/2018
 *      Author: matheussilva
 */

#ifndef SOURCES_DECODERBCDASCII_H_
#define SOURCES_DECODERBCDASCII_H_


#include <string>
using std::string;

/*
 * DecoderBcdAscii.h
 *
 *  Created on: 10/10/2018
 *      Author: matheussilva
 */


//#include "mkl_LCD.h"
//#include "MKL25Z4.h"
class DecoderBcdAscii
{
public:
	DecoderBcdAscii();

void writeData(char value);
char readData();
void setCarryIn(int carryin);

private:
char caractere;
int carry;
};

#endif /* SOURCES_DECODERBCDASCII_H_ */

