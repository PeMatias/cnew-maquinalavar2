/**
 * Project Untitled
 */


#ifndef _MONOESTAVEL2_H
#define _MONOESTAVEL2_H

#include "Monoestavel.h"
#include "LogicaOnOff.h"
#include "Led.h"

class Monoestavel2: public Monoestavel  {

public: 

	Monoestavel2(tpm_TPMNumberMask tpm) : Monoestavel(tpm){};
	SM_Output toLedBuzzer(SM_Output);

};

#endif //_MONOESTAVEL2_H
