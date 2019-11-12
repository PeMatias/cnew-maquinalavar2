/**
 * Project Untitled
 */


#include "Debounce.h"
#include "LogicaOnOff.h"

/**
 * Debounce implementation
 */

Debounce::Debounce(tpm_TPMNumberMask tpm):Monoestavel(tpm){



}

SM_Output Debounce::toLogicaOnOff2(bool botao) {
	shortDelay();
	return logicaOnOff2.toMonoestavel2(botao);
}
