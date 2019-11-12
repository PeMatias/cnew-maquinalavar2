/*
 * GiroControle.cpp
 *
 *  Created on: 04/12/2018
 *      Author: adrie
 */

#include "GiroControle.h"

GiroControle::GiroControle(tpm_Pin pin_direito,tpm_Pin pin_esquerdo) : pwm_direito(pin_direito), pwm_esquerdo(pin_esquerdo){

}

void GiroControle::delayMs(int time) {
  int i;
  int j;
  for (i = 0 ; i < time; i++) {
    for (j = 0; j < 7000; j++) {}
  }
}

void GiroControle::setGiroRapido()
{
	//mkl_TPMPulseWidthModulation pwm_esquerdo(tpm_PTA12);
	  int duty_direito = 150;
	//pwm_direito.setFrequency(tpm_div1024, 999);
	  pwm_direito.setFrequency(tpm_div1024, 999);
	  //pwm_direito.setDutyCycle(duty_direito);
	  pwm_direito.setDutyCycle(duty_direito);
	  pwm_direito.enableOperation();
}

void GiroControle::setGiroLento()
{
		//int duty_direito = 370;
	  int duty_esquerdo = 370;
	  //pwm_direito.setFrequency(tpm_div1024, 999);
	  pwm_esquerdo.setFrequency(tpm_div1024, 999);
	  //pwm_direito.setDutyCycle(duty_direito);
	  pwm_esquerdo.setDutyCycle(duty_esquerdo);
		  pwm_esquerdo.enableOperation();
		  //delayMs(500);
		  //pwm_direito.enableOperation();
		  //pwm_esquerdo.disableOperation();
		  //delayMs(500);
		  //pwm_direito.disableOperation();
	}

void GiroControle::setGiroAlternado()
{
		//while(1){
	  int duty_direito = 370;
	  int duty_esquerdo = 370;
	  pwm_direito.setFrequency(tpm_div1024, 999);
	  pwm_esquerdo.setFrequency(tpm_div1024, 999);
	  pwm_direito.setDutyCycle(duty_direito);
	  pwm_esquerdo.setDutyCycle(duty_esquerdo);
	  pwm_esquerdo.enableOperation();
	  delayMs(300);
	  pwm_direito.enableOperation();
	  pwm_esquerdo.disableOperation();
	  delayMs(300);
	  pwm_direito.disableOperation();
		//}

}

void GiroControle::setGiroZero()
{
	pwm_esquerdo.disableOperation();
	pwm_direito.disableOperation();
}

void GiroControle::enCEAction(uint8_t dtRi){


}

