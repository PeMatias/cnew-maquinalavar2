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
#include "H3/UpDownCounter.h"
#include "DivFreq.h"
#include "Chave2.h"
#include "Botao2.h"
#include "Oscilador.h"
#include "mkl_PIT.h"
#include "Led2.h"
#include "H3/Logica.h"
#include "H2/Temporizador.h"
#include "H3/Simulador.h"
#include "H4/Debounce.h"
#include "H1/DecoderBcdAscii.h"
#include "H1/DecoderBcdString.h"
#include "H1/ControladorPainel.h"
#include "H1/mkl_LCD.h"
#include "H6/ControladorH6.h"
#include "H5/mkl_TPMPulseWidthModulation.h"
#include "H5/GiroControle.h"
#include "H8/Monitor.h"
#include "H7/MonitorH7.h"
#include "H7/mkl_HC06BluetoothSlave.h"
#include "H7/ControladorH7.h"

// LCD
uint8_t deviceAddress = 0x27;
mkl_LCD lcd(mode2Lines, mode16Cols, mode5x8Dots, i2c_PTE1, i2c_PTE0,deviceAddress);

ControladorPainel painel;

DecoderBcdAscii decodUnidNL;
DecoderBcdAscii decodDezNL;
DecoderBcdAscii decodUnidTE;
DecoderBcdAscii decodDezTE;
DecoderBcdString decodStrTipo;
DecoderBcdString decodStrEstado;
DecoderBcdString decodStrLavagem;

// Oscilador e divisor de frequ�ncia x
Oscilador clock10h; // Clock de 0.1ms 10Hz
DivFreq clock1h; //Divisor de Frequencia 1H
DownCounter clock2h(5);

// Led da placa
Led2 ledClock(gpio_PTB18);

// Para enviar o WrTE uma �nica vez
bool wrTe = true;

// Variaveis do LCD
char str = 0x01; // string para mostrar etapas de lavagens
char est = 0x30; // string para mostrar estado pause continue beep
char lav = 0x20; // string para mostrar lavagem LE ou LD

// Historias
ControladorH6 ctrH6 = ControladorH6(tpm_PTD4,tpm_PTA12);
Temporizador temporizador(10);
Simulador simulador(10);
char  Ri[2] = { '1', '2' };
bool direcaoMotor = true;
bool updown = true;
Monitor mon;
//int simuladorTemp = 0;
mkl_HC06BluetoothSlave bt(uart0_PTA2, uart0_PTA1);  //! Bluetooth na UART 0
uart_Exception_t exc;  //! Armazenar exceção
ControladorH7 ctrH7;
bool onOffCM = false;
bool wrPc = false;
bool enCm = false;
bool buzzer = false;
bool statusLCD = false;

Led ledBuzzer(gpio_PTC0);
Led perdaBT(gpio_PTC3);

void delayMs(uint16_t n) {
	for (uint16_t i = 0; i < n; i++)
		for (uint16_t j = 0; j < 7000; j++) {}
}

void uint8ToChar(int valor, char * ch){
	ch[0] = valor / 10 + 48;
	ch[1] = valor % 10 + 48;
}

// Aplica as altera��es no LCD
void setLCD(bool blcd){
	if ( blcd ){
		if ( !statusLCD ){
			lcd.setBacklightOn();
			lcd.setDisplayOn();
			lcd.clear();
			statusLCD = true;
		}
	} else {
		if ( statusLCD ){
			lcd.setBacklightOff();
			lcd.setDisplayOff();
			lcd.clear();
			statusLCD = false;
			str = 0x20; // string para mostrar etapas de lavagens
			est = 0x30; // string para mostrar estado pause continue beep
			lav = 0x20; // string para mostrar lavagem LE ou LD
		}
	}
}

/*!
 *   @fn setupBluetooth
 *
 *   @brief      Realiza a configuração do periférico Bluetooth.
 *
 *   @details    Prioridade 0 e modo de interrupção no RX.
 */
void setupBluetooth() {
	bt.setInterruptMode(uart_Rx);
	bt.setPriority(uart_Priority0);
	bt.enableInterrupt();
}

/*!
 *   @fn UART0_IRQHandler
 *
 *   @brief      Rotina de serviço de interrupção.
 *
 *   @details    Recebe os dados através da UART.
 */
extern "C" {
	void UART0_IRQHandler() {
		lav = bt.receive8Bits();
		if ( lav == 0x70 || lav == 0x50 || lav == 0x10  ){
			ledBuzzer.setOn();
			delayMs(80);
			ledBuzzer.setOff();
		} else {
			lav = 0x20;
			ledBuzzer.setOn();
			delayMs(120);
			ledBuzzer.setOff();
		}

		if ( ( lav == 0x70 || lav == 0x50 || lav == 0x10 ) && ( ctrH7.getEstadoH7() == LAVAGEM_AUTOMATICA ) ){
			perdaBT.setOn();
			delayMs(50);
			perdaBT.setOff();
		}

	}
}

void lcd_action(){

	if ( statusLCD ){
		decodStrTipo.writeData(str);
		decodStrEstado.writeData(est);
		decodStrLavagem.writeData(mon.dtFC);

		decodUnidNL.writeData(simulador.getUni());
		decodDezNL.writeData(simulador.getDez());
		decodUnidTE.writeData(temporizador.getUni());
		decodDezTE.writeData(temporizador.getDez());

		painel.writeData(lcd,decodUnidTE.readData(),decodDezTE.readData(),
				decodUnidNL.readData(),decodDezNL.readData(),decodStrTipo.readData(),
				decodStrEstado.readData(),decodStrLavagem.readData());
	}

}

void readInputs(){
	//(bool wrPC, bool enCM, bool endCE, uint8_t dtFC_ )
	mon.readInputs(ctrH7.getSaidaH7().wrPC,ctrH7.getSaidaH7().enCM,ctrH6.getSaidasH6().endCE,lav);
}

void selectServices(){

	ctrH7.setDtFc(lav);
	ctrH7.setEndCm(mon.getSaidas().endCM);
	ctrH7.setH8inicioLavagem(mon.atual == inicioLavagem );
	ctrH7.writeOutputs();
	ctrH7.refreshEstado();

	// Hist�ria 8, Controlador Mestre
	  mon.executeService();
	  mon.writeOutputs();
	  uint16_t valor = mon.ri.readData();
	  str = (valor>>8)>>0;
	  //lav = mon.dtFC;
	  uint8ToChar((valor - ((valor >> 8) << 8)),Ri);
	  ctrH6.dtRi = str;
	  ctrH6.enCE = mon.cm.isEnableCE();
	  ctrH6.writeOutputs();
	  if ( ctrH6.getSaidasH6().enTE ){
	  		temporizador.setEnableTemporizador(true);
	  		//simuladorTemp = 2;
	  		if ( wrTe ){
	  			temporizador.writeData(Ri[0],Ri[1]);
	  			wrTe = false;
	  		}
	  	}else {
	  		temporizador.setEnableTemporizador(false);
	  		wrTe = true;
	  		//simuladorTemp = 0;
	  	}
	  if ( ctrH6.getSaidasH6().enNL ){
	  		simulador.setEnableSimulador(true);
	  		simulador.setUpDown(ctrH6.getSaidasH6().UpDown);
	  		simulador.setDtRi(Ri);
	          //simuladorTemp = 1;
	  	}else {
	  		simulador.setEnableSimulador(false	);
	  		//simuladorTemp = 0;
	  	}
	  ctrH6.endTE =  temporizador.isFimTemporizacao();
	  ctrH6.endNL =  simulador.isFimSimulacao();
	  ctrH6.refreshEstado();
	  setLCD(ctrH7.getSaidaH7().lcd);
}

extern "C" {
  void PIT_IRQHandler(void)
  {
	// Realiza a contagem
    clock10h.pit.clearInterruptFlag();
    clock1h.decCounter(1,1);
    clock2h.decCounter(1,1);

    simulador.contar(clock1h.isCarryOut());
    temporizador.contar(clock1h.isCarryOut());

	if ( clock2h.isCarryOut() ){
		  direcaoMotor = !direcaoMotor;
		  if ( str == 0x05 || str == 0x07  ){
			  ctrH6.setDirecaoMotor(direcaoMotor);
		  }
	}
  }
}

int main(void)
{

	lcd.setBacklightOff();
	lcd.setDisplayOff();
	lcd.clear();

	__disable_irq();
	setupBluetooth();  //! Configura o periférico bluetooth
	__enable_irq();

	  clock10h.pit.enableInterruptRequests();
	  clock1h.enable = true;
	  clock2h.enable = true;
	  while (true){

		  readInputs();
		  selectServices();
		  lcd_action();
		  ledClock.set(!ctrH7.getSaidaH7().standbye);

	  }
	  clock10h.pit.disableInterruptRequests();

    return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
