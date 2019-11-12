/**
 * Project Untitled
 */


#ifndef _DEBOUNCE_H
#define _DEBOUNCE_H

#include "Monoestavel.h"
#include "LogicaOnOff2.h"

class Debounce: public Monoestavel {

private:

	LogicaOnOff2 logicaOnOff2;

public: 

	Debounce(tpm_TPMNumberMask);
	SM_Output toLogicaOnOff2(bool botao);

};

#endif //_DEBOUNCE_H
