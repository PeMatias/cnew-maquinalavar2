/*
 * Monitor.cpp
 *
 *  Created on: 27/11/2018
 *      Author: pevic
 */

#include "Monitor.h"


Monitor::Monitor() {
	// TODO Auto-generated constructor stu
	dtFC = 0x20;
	dtPC = 0x00;
}

void Monitor :: setup()
{
	saidas.enCE = false;
	saidas.endCM = false;
	saidas.buzzer = false;
	dtFC = 0x20;
	dtPC = 0x00;
	cm.disable();
}
void Monitor::readInputs(bool wrPC, bool enCM, bool endCE, uint8_t dtFC_ )
{
	//Entradas wrPC, enCM
	if(wrPC and !enCM and !endCE )
	{
		atual = inicioLavagem; //Serviço atual
		dtFC = dtFC_;
	}
	else if( !wrPC and enCM )
	{
		atual = executaLavagem;
		cm.setEndCE( endCE );
	}
	/*else if(!wrPC  and !enCM and !endCE )
	{
		atual = fimLavagem;
	}*/


}

void Monitor::executeService()
{
	if(atual == inicioLavagem)
	{
		decoder.writeData(dtFC);
		dtPC = decoder.readData();
		pc.writeData(dtPC);
	}
	else if(atual == executaLavagem)
	{
		if(!cm.isEnable()) cm.enable();
		switch(cm.getState())
		{
			case espera:
				break;
			case leitura:
				dtAddr = pc.readData();
				mem.writeAddr(dtAddr);
				dtRAM = mem.readData();
				break;
			case atualiza:
				cm.writeData(dtRAM);
				pc.incCounter(1);
				break;
			case registra:
				ri.writeData(dtRAM);
				break;
			case executa:
				break;
			case fimCE:
				break;
			case fimCM:
				pc.reset();
				atual = fimLavagem;
				break;
		}

	}
	else if(atual == fimLavagem)
	{
		cm.disable();
		atual = reset;
		dtFC = 0x20;
		//dtPC = 0x00;
	}
}

SaidasH8 Monitor::getSaidas(){
	return saidas;
}

void Monitor::writeOutputs()
{
	switch(cm.getState())
			{
				case espera:
					saidas.enCE = false;
					saidas.endCM = false;
					saidas.buzzer = true;
					break;
				case leitura:
					saidas.enCE = false;
					saidas.endCM = false;
					saidas.buzzer = true;
					break;
				case atualiza:
					saidas.enCE = false;
					saidas.endCM = false;
					saidas.buzzer = true;
					break;
				case registra:
					saidas.enCE = false;
					saidas.endCM = false;
					saidas.buzzer = true;
					break;
				case executa:
					if(cm.isEnableCE()) saidas.enCE = true;
					else  saidas.enCE = false;
					//saidas.enCE = true;
					saidas.buzzer = true;
					saidas.endCM = false;
					break;
				case fimCE:
					if(cm.readData()== 0x5007)
					{
						saidas.buzzer = false;
						//for(int i=1500000; i >0; i--);
					}
					saidas.enCE = false;
					saidas.endCM = false;
					saidas.buzzer = true;
					break;
				case fimCM:
					saidas.buzzer = true;
					saidas.enCE = false;
					saidas.endCM = true;
					break;
			}
		cm.refreshState();

}
