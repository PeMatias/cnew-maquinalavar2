/**
 * Project Untitled
 */


#include "Monoestavel.h"

/**
 * Monoestavel implementation
 */

Monoestavel::Monoestavel(tpm_TPMNumberMask tpm) : tpmdelay(tpm) {

	tpmdelay.setFrequency(tpm_Div::tpm_div128);
}

/*bool Monoestavel::isTrigged() {
	return false;
}*/

void Monoestavel::shortDelay() {
	tpmdelay.waitDelay(MAX_CYCLES);
	//tpmdelay.waitDelay(MAX_CYCLES);
}

void Monoestavel::veryShortDelay() {
	tpmdelay.waitDelay(8000);
}

void Monoestavel::longDelay() {
	tpmdelay.waitDelay(MAX_CYCLES);
	tpmdelay.waitDelay(MAX_CYCLES);
	tpmdelay.waitDelay(MAX_CYCLES);
}
