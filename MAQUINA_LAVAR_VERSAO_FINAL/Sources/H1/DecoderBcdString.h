/*
 * DecoderBcdString.h
 *
 *  Created on: 16/10/2018
 *      Author: matheussilva
 */

#ifndef SOURCES_DECODERBCDSTRING_H_
#define SOURCES_DECODERBCDSTRING_H_


/*
 * DecoderBcdString.h
 *
 *  Created on: 10/10/2018
 *      Author: matheussilva
 */


#include <string>
using std::string;


class DecoderBcdString
{
public:
	DecoderBcdString();

void writeData(char value);
string readData();


private:
string funcao;

};



#endif /* SOURCES_DECODERBCDSTRING_H_ */
