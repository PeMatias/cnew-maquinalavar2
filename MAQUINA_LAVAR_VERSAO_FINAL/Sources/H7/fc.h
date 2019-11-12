/*
 * fc.h
 *
 *  Created on: 22/11/2018
 *      Author: matheussilva
 */

#ifndef SOURCES_FC_H_
#define SOURCES_FC_H_

#include <string>
using std::string;

#include <list>
using namespace std;
#include "MKL25Z4.h"

class fc
{
public:
	fc();

	bool fila_adiciona(uint8_t valor);
	uint8_t fila_remove();
	uint8_t fila_tamanho();
	uint8_t ultimo_valor_fila();
	void writeIsDataFc(bool valor);
	bool getisDataFc();
	void limpaLista();


private:
string dtFC;
bool isDataFc;



};



#endif /* SOURCES_FC_H_ */
