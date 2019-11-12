/**
 * Project Untitled
 */


#include "LogicaOnOff2.h"

/**
 * LogicaOnOff2 implementation
 */

SM_Output LogicaOnOff2::toMonoestavel2(bool botao) {

	Monoestavel2 monoestavel2(tpm_TPM1);

	botao ? botaoOnEvent() : botaoOffEvent();

	//if ( botao ) {
	//	botaoOnEvent();
	//} else {
	//	botaoOffEvent();
	//}

	return output;
}
