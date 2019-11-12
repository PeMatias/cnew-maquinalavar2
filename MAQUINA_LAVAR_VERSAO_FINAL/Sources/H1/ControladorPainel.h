/*
 * ControladorPainel.h
 *
 *  Created on: 16/10/2018
 *      Author: matheussilva
 */

#ifndef SOURCES_CONTROLADORPAINEL_H_
#define SOURCES_CONTROLADORPAINEL_H_


#include <string>
using std::string;

#include "mkl_LCD.h"

#include "MKL25Z4.h"

class ControladorPainel
{
public:
	ControladorPainel();

void writeData(mkl_LCD lcd,char TEunid, char TEdez, char NLunid, char NLdez, string tipo,string estado, string lavagem);
string readData();


private:
string str;

};




#endif /* SOURCES_CONTROLADORPAINEL_H_ */
