/*
 * fc.cpp
 *
 *  Created on: 22/11/2018
 *      Author: matheussilva
 */



#include "fc.h"

list<uint8_t> lista;
list<uint8_t>::iterator it;

fc::fc(){};



bool fc::fila_adiciona(uint8_t valor)
{
    if(lista.size()>=5)
    {
        return false;
    }
    else
    {
       lista.push_back(valor);

        return true;
    }
}



uint8_t fc::fila_remove()
{
	uint8_t valor_removido;
    if(lista.size() == 0)
    {
    	valor_removido = 0b00010000;
        return valor_removido; //retorna 16 em binario caso lista estiver vazia e fracassou
    }
    else
    {
    	valor_removido = lista.front();
         lista.pop_front();
         return valor_removido;

    }

}

uint8_t fc::ultimo_valor_fila()
{

	uint8_t ultimo_valor;
	ultimo_valor = lista.front();
	return ultimo_valor;

}

uint8_t fc::fila_tamanho()
{
    return lista.size();
}

void fc::writeIsDataFc(bool valor)
{
	isDataFc = valor;
}

bool fc::getisDataFc()
{
	return isDataFc;
}

void fc::limpaLista()
{
	lista.clear();
	}



