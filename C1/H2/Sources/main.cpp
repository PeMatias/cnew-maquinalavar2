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
#include "Led2.h"


using namespace std;

Chave2 enTE(gpio_PTA2); // Chave enTE
Botao2 wrTE(gpio_PTA1); // Botao wrTE
Oscilador clock10h; // Clock de 0.1ms 10Hz
DivFreq clock1h; //Divisor de Frequencia 1H
Led2 onTE(gpio_PTB18);
Led2 ledClock(gpio_PTB19);
DownCounterProgramable TEuni(10); //Temporizador - Unidade
DownCounterProgramable TEdez(10); //Temporizador - Dezena


extern "C" {
  void PIT_IRQHandler(void)
  {
    clock10h.pit.clearInterruptFlag();
    //Habilita clock de 1Hz
    clock1h.enable = true;
	clock1h.decCounter(1,1);
	if(clock1h.isCarryOut()) ledClock.setOn();
	else ledClock.setOff();

	//Verifica a botão e programa os contadores
	if(wrTE.isOn())
	{
		TEdez.writeData(true,'1');
		TEuni.writeData(true,'5');
	}

	//Verificar o enable count
	TEdez.enable = enTE.isOn();
	TEuni.enable = enTE.isOn();

	//Contagem Habilitada
	TEdez.decCounter(TEuni.isCarryOut()	,clock1h.isCarryOut());
	TEuni.decCounter(1					,clock1h.isCarryOut());
	if(TEuni.isCarryOut()&& TEdez.isCarryOut())
	{
		onTE.setOn();
		TEdez.clearCounter();
		TEuni.clearCounter();
	}
	else onTE.setOff();


  }
}
int main()
{
	//*((volatile unsigned long *) (0xE000E100)) = 0x4; // Disable interrupt #2

	  clock10h.pit.enableInterruptRequests();
	  while (1)
	  {
		  clock10h.pit.waitInterruptFlag();
		  //esperaProgramarContagem();
	  }
	  clock10h.pit.disableInterruptRequests();


    return 0;
}
