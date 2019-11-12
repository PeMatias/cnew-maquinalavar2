/*
 * ControladorMestreBusca2.cpp
 *
 *  Created on: 27/11/2018
 *      Author: pevic
 */

#include "ControladorMestreBusca2.h"

ControladorMestreBusca2::ControladorMestreBusca2()
{
	// TODO Auto-generated constructor stub
	stateMachine = espera;
	status = false;
	statusCE = false;
	data = 0x0105;
	endCE =false;
}

void ControladorMestreBusca::refreshState()
{
	// enCM = 0
	if(this->isEnable() == false) this->stateMachine = espera;
	//enCM = 1
	else
	{
		switch(this->getState())
		{
			case espera:
				this->stateMachine = leitura;
				break;
			case leitura:
				this->stateMachine = atualiza;
				break;
			case atualiza:
				if(this->readData() != 0x6000 )
					this->stateMachine = registra;
				else
					this->stateMachine = fimCM;
				break;
			case registra:
				this->stateMachine = executa;
				if(this->readData() == 0x5007 || this->readData() ==0x1000  ) this->stateMachine = fimCE;
				break;
			case executa:
				this->enableCE();
				if(this->isEndCE() == false) // Não está no fim da etapa
					this->stateMachine = executa;
				else
					this->stateMachine = fimCE;
				break;
			case fimCE:
				this->disableCE();
				this->stateMachine = leitura;
				break;
			case fimCM:
				this->stateMachine = fimCM;
				break;
		}
	}
}

