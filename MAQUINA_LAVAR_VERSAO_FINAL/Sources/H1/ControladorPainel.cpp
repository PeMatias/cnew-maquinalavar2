/*
 * ControladorPainel.cpp
 *
 *  Created on: 14/10/2018
 *      Author: matheussilva
 */

/*
 * DecoderBcdString.cpp
 *
 *  Created on: 10/10/2018
 *      Author: matheussilva
 */

#include "ControladorPainel.h"




ControladorPainel::ControladorPainel(){
	//lcd.clear();
	//lcd.setBlinkOff();
	//lcd.setCursorOff();
}

void ControladorPainel::writeData(mkl_LCD lcd,char TEunid, char TEdez, char NLunid, char NLdez, string tipo,string estado,string lavagem)
{


		if(TEdez == '0')
		{
			TEdez = ' ';
		}

		if(NLdez == '0')
		{
			NLdez = ' ';
		}

		//lcd.clear();
		lcd.setCursor(1, 15);
		lcd.putString(lavagem);


		lcd.setCursor(2, 1);
		lcd.putString(tipo);


		lcd.setCursor(2,11);
		lcd.putString(estado);


		lcd.setCursor(1, 1);
		lcd.putChar('T');
		lcd.setCursor(1, 2);
		lcd.putChar('E');
		lcd.setCursor(1, 3);
		lcd.putChar(':');
		lcd.setCursor(1, 4);
		lcd.putChar(TEdez);
		lcd.setCursor(1, 5);
		lcd.putChar(TEunid);


		lcd.setCursor(1, 8);
		lcd.putChar('N');
		lcd.setCursor(1, 9);
		lcd.putChar('L');
		lcd.setCursor(1, 10);
		lcd.putChar(':');
		lcd.setCursor(1, 11);
		lcd.putChar(NLdez);
		lcd.setCursor(1, 12);
		lcd.putChar(NLunid);
		lcd.setBlinkOff();
		lcd.setCursorOff();

}

string ControladorPainel:: readData()
{
	return str;
	}






