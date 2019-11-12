/*
 * DecoderBcdString.cpp
 *
 *  Created on: 10/10/2018
 *      Author: matheussilva
 */

#include "DecoderBcdString.h"


DecoderBcdString::DecoderBcdString(){}

void DecoderBcdString:: writeData(char value)
{
	switch(value)
		{
			case 0x10:
				funcao = " CYCLONEW";
			break;
			case 0x20:
				funcao = "  ";
			break;

			case 0x30 :
				funcao = "  ";
			break;

			case 0x40:
				funcao = "Beep";
			break;

			case 0x60:
				funcao = "Fim";
			break;

			case 0x70:
				funcao = "LE";
			break;

			case 0x50:
				funcao = "LD";
			break;

			//=======================================
			case 0x01:
			funcao = "T.Sabao  ";
			break;

			case 0x04:
			funcao = "DrenoAgua    ";
			break;

			case 0x03 :
				funcao = "T.Agua     ";
			break;

			case 0x02:
				funcao = "DrenoSabao   ";
			break;

			case 0x05:
				funcao = "Agitacao   ";
			break;

			case 0x06:
				funcao = "Molho      ";
			break;

			case 0x07:
				funcao = "Enxague    ";
			break;

			case 0x08:
				funcao = "PassaFacil  ";
			break;

			case 0x09:
				funcao = "PassaNormal  ";
			break;

			}
		}

string DecoderBcdString:: readData()
{
	return funcao;
	}


