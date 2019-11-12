/*
 * ControladorH7.cpp
 *
 *  Created on: Dec 13, 2018
 *      Author: Guilherme
 */

#include <H7/ControladorH7.h>

namespace std {

ControladorH7::ControladorH7() {
	// TODO Auto-generated constructor stub

	estadoH7 = DESLIGADA;
	dtFC = 0x00;
	endCM = false;
	H8inicioLavagem = false;

}

void ControladorH7::delayMs(uint16_t n) {
	for (uint16_t i = 0; i < n; i++)
		for (uint16_t j = 0; j < 7000; j++) {}
}

uint16_t ControladorH7::getDtFc() {
	return dtFC;
}

void ControladorH7::setDtFc(uint16_t dtFc) {
	dtFC = dtFc;
}

bool ControladorH7::isEndCm() {
	return endCM;
}

void ControladorH7::setEndCm(bool endCm) {
	endCM = endCm;
}

EstadosH7 ControladorH7::getEstadoH7() {
	return estadoH7;
}

bool ControladorH7::isH8inicioLavagem() {
	return H8inicioLavagem;
}

void ControladorH7::setH8inicioLavagem(bool h8inicioLavagem_) {
	H8inicioLavagem = h8inicioLavagem_;
}

SaidasH7 ControladorH7::getSaidaH7() {
	return saidaH7;
}

void ControladorH7::writeOutputs(){

	switch(this->getEstadoH7()){
		case DESLIGADA:

			saidaH7.enCM = false;
			saidaH7.wrPC = false;
			saidaH7.lcd = false;
			saidaH7.buzzer = false;
			saidaH7.perdaBT = false;
			saidaH7.standbye = true;
			break;
		case ESPERA_LAVAGEM:
			saidaH7.enCM = false;
			saidaH7.wrPC = false;
			saidaH7.lcd = true;
			saidaH7.buzzer = true;
			saidaH7.perdaBT = false;
			saidaH7.standbye = false;
			break;
		case ESCREVE_PC:
			saidaH7.enCM = false;
			saidaH7.wrPC = true;
			saidaH7.lcd = true;
			saidaH7.buzzer = false;
			saidaH7.perdaBT = false;
			saidaH7.standbye = false;
			break;
		case LAVAGEM_AUTOMATICA:
			saidaH7.enCM = true;
			saidaH7.wrPC = false;
			saidaH7.lcd = true;
			saidaH7.buzzer = false;
			saidaH7.perdaBT = false;
			saidaH7.standbye = false;
			break;
		case FIM_LAVAGEM:
			saidaH7.enCM = false;
			saidaH7.wrPC = false;
			saidaH7.lcd = false;
			saidaH7.buzzer = true;
			saidaH7.perdaBT = false;
			saidaH7.standbye = false;
			break;
	}

}

void ControladorH7::refreshEstado(){

	Led buzzer(gpio_PTC0);
	buzzer.setOff();

	switch(this->getEstadoH7()){
		case DESLIGADA:
			if ( dtFC == 0x10 ){
				buzzer.setOn();
				delayMs(50);
				buzzer.setOff();
				estadoH7 = ESPERA_LAVAGEM;
			} else {
				estadoH7 = DESLIGADA;
			}
			break;
		case ESPERA_LAVAGEM:
			if ( dtFC == 0x70 || dtFC == 0x50 )
				estadoH7 = ESCREVE_PC;
			else
				estadoH7 = ESPERA_LAVAGEM;
			break;
		case ESCREVE_PC:
			if ( H8inicioLavagem )
				estadoH7 = LAVAGEM_AUTOMATICA;
			else
				estadoH7 = ESCREVE_PC;
			break;
		case LAVAGEM_AUTOMATICA:
			if ( endCM )
				estadoH7 = FIM_LAVAGEM;
			else
				estadoH7 = LAVAGEM_AUTOMATICA;
			break;
		case FIM_LAVAGEM:
			buzzer.setOn();
			delayMs(200);
			buzzer.setOff();
			estadoH7 = DESLIGADA;
			break;
	}
}

} /* namespace std */
