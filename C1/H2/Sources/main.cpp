/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "MKL25Z4.h"
#include "DownCounterProgramable.h"
#include "DivFreq.h"
#include "Chave2.h"
#include "Botao2.h"
#include "Oscilador.h"
#include "mkl_PIT.h"
#include "Led.h"


using namespace std;
/*
Chave2 enTE(gpio_PTA2); // Chave enTE

Botao2 wrTE(gpio_PTA1); // Botao wrTE
Oscilador clock10h; // Clock de 0.1ms 10Hz
DivFreq clock1h; //Divisor de Frequencia 1H
Led onTE(gpio_PTB18);
DownCounterProgramable TEuni(10); //Temporizador - Unidade
DownCounterProgramable TEdez(10); //Temporizador - Dezena
char dtRI[2] = {'1','7'};

extern "C" {
  void PIT_IRQHandler(void) {
    clock10h.pit.clearInterruptFlag();
    onTE.setOn();
  }
}
void esperaProgramarContagem()
{
	while(wrTE.isOff()) // Aguarda o botão ser pressionado
	{
		TEdez.writeData(true,dtRI[0]);
	    TEuni.writeData(true,dtRI[1]);
	    break;
	}
	TEdez.writeData(true,dtRI[0]);
	TEuni.writeData(true,dtRI[1]);
}
void esperaHabilitarContagem()
{
	 while(TEuni.isCarryOut(1)==1 && TEdez.isCarryOut(1) == 1) // Aguarda o fim da contagem
	 {
		//(carryIn,clk,enTE)
		clock1h.decCounter(1					, clock10h.clock() 					,1);
		TEdez.decCounter(TEuni.isCarryOut(1)	,clock1h.isCarryOut(enTE.isOn())	,enTE.isOn());
		TEuni.decCounter(1						,clock1h.isCarryOut(enTE.isOn())	,enTE.isOn());

	}
}
int main()
{
	//*((volatile unsigned long *) (0xE000E100)) = 0x4; // Disable interrupt #2

    while(true)
    {
    	//onTE.setOn();

    	esperaProgramarContagem();
    	esperaHabilitarContagem();

    }

    return 0;
}*/
////////////////////////////////////////////////////////////////////////////////////
////Teste do pit
DivFreq clock1h; //Divisor de Frequencia 1H

mkl_PITInterruptInterrupt pit(PIT_Ch0);


/*!
 *  Defini��o do objeto led a ser usado.
 */
Led led(gpio_PTB18);


/*!
 *  Configura��o dos objetos PIT e Led
 */
void setup() {
  //led.init();
  pit.enablePeripheralModule();
  //pit.setPeriod(0x30D40);
  pit.setPeriod(0xF4240);
}


/*!
 *  Defini��o da rotina de interrup��o do PIT
 */
extern "C" {
  void PIT_IRQHandler(void) {
    pit.clearInterruptFlag();
	clock1h.decCounter(1,1.,1);
	if(clock1h.isCarryOut(1)) led.setOn();
	else led.setOff();


  }
}

/*!
 *  Configura��o dos objetos PIT e Led
 */
int main(void) {
  setup();
  pit.resetCounter();
  pit.enableTimer();
  //led.invertCurrentState();
  pit.enableInterruptRequests();
  while (1) {
    pit.waitInterruptFlag();
  }

  pit.disableInterruptRequests();

  return 0;
}
