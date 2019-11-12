/*
 * ControladorH6.cpp
 *
 *  Created on: Dec 9, 2018
 *      Author: Guilherme
 */

#include <H6/ControladorH6.h>

ControladorH6::ControladorH6(tpm_Pin pin_direito,tpm_Pin pin_esquerdo): onAgua(gpio_PTC1),onDreno(gpio_PTC2),onSabao(gpio_PTC7),pwm_direito(pin_direito), pwm_esquerdo(pin_esquerdo)
{
	enCE = 0;
	endTE = 0;
	endNL = 0;
}

void ControladorH6::espera(){
	saida.UpDown = false;
	saida.enNL = false;
	saida.enTE = false;
	saida.endCE = false;
	onAgua.setOff();
	onSabao.setOff();
	onDreno.setOff();
	pwm_esquerdo.disableOperation();
	pwm_direito.disableOperation();
}

void ControladorH6::fim(){
	pwm_esquerdo.disableOperation();
	pwm_direito.disableOperation();
	saida.UpDown = false;
	saida.enNL = false;
	saida.enTE = false;
	saida.endCE = true;
	onAgua.setOff();
	onSabao.setOff();
	onDreno.setOff();
	//status = 0;
}


void ControladorH6::setup(uint8_t dtRi){

	// Verifica qual os valores do dtRi
	if( dtRi == 0x01 ) 	// if(dtRI == 0xb00000011) TORN. SABAO
		T_Sabao();

	else if(dtRi == 0x03 ) // if(dtRI == 0xb00000001) TORN. AGUA
		T_Agua();

	else if (dtRi == 0x02 || dtRi == 0x04 )  // if(dtRI == 0xb00000010 || 0xb00000100 ) DRENO AGUA OU SABAO
		Dreno();

	else if ( dtRi == 0x05 || dtRi == 0x07 )  // if(dtRI == 0xb00000101 || 0xb00000111 ) AGITACAO OU ENXAGUE
		AgitacaoEnxague();

	else if (dtRi == 0x06 )  // if(dtRI == 0xb00000110 ) MOLHO
		Molho();

	else if (dtRi == 0x08 ) // Passa Facil
		setGiroLento();

	else if ( dtRi == 0x09 ) // Passa Normal
		setGiroRapido();

	else {
		// ????
	}
}
/*

bool ControladorH6::endNLAction(){
	//if ( saida.enNL ){
		status = 6;
		executeService();
		return true;
	//} else {
	//	return false;
	//}
}

bool ControladorH6::endTEAction(){
	//if ( saida.enTE ){
		status = 6;
		executeService();
		return true;
	//} else {
	//	return false;
	//}
}*/


SaidasH6 ControladorH6::getSaidasH6(){
	return saida;
}

void ControladorH6::setGiroRapido()
{
	//mkl_TPMPulseWidthModulation pwm_esquerdo(tpm_PTA12);
	  int duty_direito = 590;
	//pwm_direito.setFrequency(tpm_div1024, 999);
	  pwm_direito.setFrequency(tpm_div1024, 999);
	  //pwm_direito.setDutyCycle(duty_direito);
	  pwm_direito.setDutyCycle(duty_direito);
	  pwm_direito.enableOperation();
	  pwm_esquerdo.disableOperation();

	saida.UpDown = false;
	saida.enNL = false;
	saida.enTE = true;
	saida.endCE = false;
	onAgua.setOff();
	onSabao.setOff();
	onDreno.setOff();
}

void ControladorH6::setGiroLento()
{
			//int duty_direito = 370;
		  int duty = 700;
		  pwm_esquerdo.setFrequency(tpm_div1024, 999);
		  pwm_esquerdo.setDutyCycle(duty);
		  //pwm_direito.setFrequency(tpm_div1024, 999);
		  //pwm_direito.setDutyCycle(duty);
		  pwm_esquerdo.enableOperation();
		  pwm_direito.disableOperation();

	  /*if ( direcao ){
		  pwm_esquerdo.enableOperation();
		  pwm_direito.disableOperation();
	  } else {
		  pwm_direito.enableOperation();
		  pwm_esquerdo.disableOperation();
	  }*/
		saida.UpDown = false;
		saida.enNL = false;
		saida.enTE = true;
		saida.endCE = false;
		onAgua.setOff();
		onSabao.setOff();
		onDreno.setOff();

}

void ControladorH6::setDirecaoMotor(bool direcao){
	 if ( direcao ){
		 pwm_esquerdo.enableOperation();
		 pwm_direito.disableOperation();
	 }else{
		 pwm_direito.enableOperation();
		 pwm_esquerdo.disableOperation();
	 }
}

void ControladorH6::AgitacaoEnxague()
{

	  setDirecaoMotor(true);

	  int duty = 700;
	  pwm_esquerdo.setFrequency(tpm_div1024, 999);
	  pwm_esquerdo.setDutyCycle(duty);
	  pwm_direito.setFrequency(tpm_div1024, 999);
	  pwm_direito.setDutyCycle(duty);

	  saida.UpDown = false;
	  saida.enNL = false;
	  saida.enTE = true;
		saida.endCE = false;
	  onAgua.setOff();
	  onSabao.setOff();
      onDreno.setOff();

}

void ControladorH6::Molho()
{
	pwm_esquerdo.disableOperation();
	pwm_direito.disableOperation();
	saida.UpDown = false;
	saida.enNL = false;
	saida.enTE = true;
	saida.endCE = false;
	onAgua.setOff();
	onSabao.setOff();
	onDreno.setOff();
}

void ControladorH6::T_Agua(){

	pwm_esquerdo.disableOperation();
	pwm_direito.disableOperation();
	saida.UpDown = true;
	saida.enNL = true;
	saida.enTE = false;
	saida.endCE = false;
	onAgua.setOn();
	onSabao.setOff();
	onDreno.setOff();

}

void ControladorH6::T_Sabao(){
	pwm_esquerdo.disableOperation();
	pwm_direito.disableOperation();
	saida.UpDown = true;
	saida.enNL = true;
	saida.enTE = false;
	saida.endCE = false;
	onAgua.setOff();
	onSabao.setOn();
	onDreno.setOff();

}

void ControladorH6::Dreno(){
	pwm_esquerdo.disableOperation();
	pwm_direito.disableOperation();
	saida.UpDown = false;
	saida.enNL = true;
	saida.enTE = false;
	saida.endCE = false;
	onAgua.setOff();
	onSabao.setOff();
	onDreno.setOn();
}

EstadosCtr ControladorH6::getEstado()
{
	return estados;
}

bool ControladorH6::isEnable()
{
	return enCE;
}

bool ControladorH6::eoc()
{
	return this->endNL or this->endTE;
}



void ControladorH6::refreshEstado(){
	switch(this->getEstado()){
		case(ESPERA):
			if( this->isEnable() ) estados = SETUP;
			else estados = ESPERA;
			break;
		case(SETUP):
			estados = EXECUTA;
			break;
		case(EXECUTA):
			if(this->eoc()) estados = FIM;
			else estados = EXECUTA;
			break;
		case(FIM):
			if( this->isEnable() ) estados = FIM;
			else estados = ESPERA;
			break;
	}
}

void ControladorH6::writeOutputs(){
	switch(this->getEstado())
	{
	case(ESPERA):
		espera();
		break;
	case(SETUP):
		setup(this->dtRi);
		break;
	case(EXECUTA):
		break;
	case(FIM):
		fim();
		break;
	}
}
