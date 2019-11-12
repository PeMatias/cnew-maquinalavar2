/**
 * Project Untitled
 */

#include "mkl_TPMDelay.h"

#ifndef _MONOESTAVEL_H
#define _MONOESTAVEL_H

#define MAX_CYCLES 0xFFFF

class Monoestavel {
private:
    mkl_TPMDelay tpmdelay;

public:

	Monoestavel(tpm_TPMNumberMask tpm);

	//bool isTrigged();

	void veryShortDelay();

	void shortDelay();

	void longDelay();

};

#endif //_MONOESTAVEL_H
