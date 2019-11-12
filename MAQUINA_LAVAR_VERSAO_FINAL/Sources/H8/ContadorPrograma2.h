/*
 * ContadorPrograma2.h
 *
 *  Created on: 20/11/2018
 *      Author: pevic
 */

#ifndef SOURCES_CONTADORPROGRAMA2_H_
#define SOURCES_CONTADORPROGRAMA2_H_

#include "ContadorPrograma.h"

class ContadorPrograma2: public ContadorPrograma {
public:
	ContadorPrograma2();
private:

	volatile uint8_t data;
};

#endif /* SOURCES_CONTADORPROGRAMA2_H_ */
