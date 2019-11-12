/*
 * monitor.cpp
 *
 *  Created on: 25/11/2018
 *      Author: matheussilva
 */



#include "MonitorH7.h"


	MonitorH7::MonitorH7(){};



	void MonitorH7::setup()
	{
		cc.writeRdBt(false);
		cc.writeOnOffCm(false); // 0
		cc.writeEnCm(false); // 0
		fila.writeIsDataFc(true); // 1
		cc.writeWrPc(true); //1
		cc.writeBeep(false);
		controleMaquinaEstado = esperaa;
		fila.limpaLista();
	}
	void MonitorH7::readInputs()  //botao é endcm
	{

	}

	void MonitorH7::executeServices(int botao,bool &ledVerde,bool &ledVermelho, bool &ledAzul,bool &buzzer)
	{
		switch(controleMaquinaEstado)
				{
					case esperaa:
						//cc.delay(500);
						cc.writeBeep(false);
						buzzer = cc.getBeep();
						if(cb.getFullBt() == true)
						{
							controleMaquinaEstado = leituraBT;
						}

						break;
					case liga:

						cc.writeOnOffCm(true); // ligado
						ledVerde = cc.getOnOffCm();
						fila.writeIsDataFc(false);

						if (fila.getisDataFc()== false)
						{
							controleMaquinaEstado = esperaa;
						}

						break;

					case leituraBT:
						cb.writeFullBt(false);
						cc.writeRdBt(true);
						fila.fila_adiciona(cb.writeData());
						//cc.writeWrFc(true);

						cc.writeBeep(true);
						buzzer = cc.getBeep();


						if(cc.getRdBt() == true)
						{
							controleMaquinaEstado = leituraFC;
						}

						break;

					case leituraFC:
							//cc.delay(200);
							cc.writeBeep(false);
							buzzer = cc.getBeep();
							cc.writeRdBt(false);
							//cc.writeRdFc(true);
							fila.writeIsDataFc(true);
							cc.writeRecebeDtFc(fila.fila_remove());

							if(fila.getisDataFc() == true)
							{
								if(cc.getRecebeDtFc() == 0x80 || cc.getRecebeDtFc() == 0x70)
								{
									cc.writeWrPc(true);
									ledAzul = cc.getWrPc();
									controleMaquinaEstado = escreveMemoria;
								}
								if(cc.getRecebeDtFc() == 0x90 && cc.getOnOffCm() == false) // desligado
								{
									controleMaquinaEstado = liga;
								}

								if(cc.getRecebeDtFc() == 0x90 && cc.getOnOffCm() == true) //ligada
								{
									controleMaquinaEstado = desliga;
								}
							}


						break;
					case escreveMemoria:
						//cc.delay(200);
						cc.writeWrPc(false);
						ledAzul = cc.getWrPc();
						if(cc.getWrPc() == false)
						{
							controleMaquinaEstado = lavagem;
						}

						break;

					case lavagem:

						//implementar beep caso tiver em uma lavagem e chegar um novo comando.
						if(cb.getFullBt() == true)
						{
							//perda de dado, implementar mais um led
							cc.writeBeep(true);
							buzzer = cc.getBeep();
							//cc.delay(300);
							cc.writeBeep(false);
							buzzer = cc.getBeep();
							cb.writeFullBt(false);
						}

						if(botao == 0 && cc.getEnCm() == false) // 0 botao clicado vai para 0
						{
							controleMaquinaEstado = desliga;
						}
						if(botao == 1 && cc.getEnCm() == false ) //1 botao livre esta em modo 1 / encm ativado
						{
							controleMaquinaEstado = lavagem;
						}

						fila.writeIsDataFc(false);
						cc.writeEnCm(true);
						ledVermelho = cc.getEnCm();
						break;
					case desliga:
						//fila.writeIsDataFc(false);
						cc.writeEnCm(false); //desligado
						cc.writeOnOffCm(false); // desligado
						cc.writeWrPc(false);
						ledVermelho = cc.getEnCm();
						ledVerde = cc.getOnOffCm();
						ledAzul = cc.getWrPc();
						//beep para finalizacao de lavagem / verificar se beep é ativo em false ou true
						cc.writeBeep(true);
						buzzer = cc.getBeep();

						if(cc.getOnOffCm() == false)
						{
							controleMaquinaEstado = esperaa;
						}
						break;
				}
	}

	//teste de leds:
	/*
 	 led verde maquina ligada ou desligada onOffcm
	 led azul wrPc
	 led vermelho enCm

	 */

	void MonitorH7::delay(uint32_t milliSeconds)
	{
		uint32_t i;
		uint32_t j;

			for (i = 0; i < milliSeconds; i++) {
			for (j = 0; j < 1500; j++) {}
			}

	}



	//void monitor::reset(); //necessario implementar
