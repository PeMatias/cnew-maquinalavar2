/*!
 * @copyright   � 2017 Universidade Federal do Amazonas.
 *
 * @brief       Implementa��o da API em C++ da classe m�e I2C.
 *
 * @file        mkl_I2C.cpp
 * @version     1.0
 * @date        07 Dezembro 2017
 *
 * @section     HARDWARES & SOFTWARES
 *              +board        FRDM-KL25Z da NXP.
 *              +processor    MKL25Z128VLK4 - ARM Cortex-M0+
 *              +compiler     Kinetis� Design Studio IDE
 *              +manual       L25P80M48SF0RM, Rev.3, September 2012
 *              +revisions    Vers�o (data): Descri��o breve.
 *                             ++ 1.0 (07 Dezembro 2017): Vers�o inicial.
 *
 * @section     AUTHORS & DEVELOPERS
 *              +institution  Universidade Federal do Amazonas
 *              +courses      Engenharia da Computa��o / Engenharia El�trica
 *              +teacher      Miguel Grimm <miguelgrimm@gmail.com>
 *              +student      Vers�o inicial:
 *                             ++ Leticia Flores <leticia.flors@gmail.com>
 * 							   ++ Matheus de Sousa Castro <matheus.sousa110@gmail.com>
 * 							   ++ Stephanie Lopes <stephanielopees@gmail.com>
 * 						       ++ Victoria da Silva Leite <victoria_leite@hotmail.com>
 *
 * @section     LICENSE
 *
 *              GNU General Public License (GNU GPL).
 *
 *              Este programa � um software livre; Voc� pode redistribu�-lo
 *              e/ou modific�-lo de acordo com os termos do "GNU General Public
 *              License" como publicado pela Free Software Foundation; Seja a
 *              vers�o 3 da licen�a, ou qualquer vers�o posterior.
 *
 *              Este programa � distribu�do na esperan�a de que seja �til,
 *              mas SEM QUALQUER GARANTIA; Sem a garantia impl�cita de
 *              COMERCIALIZA��O OU USO PARA UM DETERMINADO PROP�SITO.
 *              Veja o site da "GNU General Public License" para mais detalhes.
 *
 * @htmlonly    http://www.gnu.org/copyleft/gpl.html
 */

#include "mkl_I2C.h"

/*!
 *  @fn         enablePeripheralClock
 *
 *  @brief      Habilita o clock do perif�rico de hardware.
 *
 *  Este m�todo habilita o clock do perif�rico I2C solicitado.
 *
 *  @remarks    Sigla e pagina do Manual de Referencia KL25:
 *               - SCGC4: System Cock Gating Control Register 4. P�g.204.
 */
void mkl_I2C::enablePeripheralClock(uint32_t I2CNumber) {
    SIM_SCGC4 |= (SIM_SCGC4_I2C0_MASK << I2CNumber);
}


/*!
 *  @fn         enableGPIOClock
 *
 *  @brief      Habilita o clock do GPIO do pino.
 *
 *  Este m�todo habilita o clock do perif�rico GPIO do pino passado por
 *  par�metro.
 *
 *  @param[in]  GPIONumber - o n�mero do GPIO correspondente ao pino.
 *
 *  @remarks    Sigla e pagina do Manual de Referencia KL25:
 *              - SCGC5: System Cock Gating Control Register 5. P�g.206.
 */
void mkl_I2C::enableGPIOClock(uint32_t GPIONumber) {
    SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK << GPIONumber;
}


/*!
 *  @fn         enableI2C
 *
 *  @brief      Habilita o periferico I2C.
 *
 *  Este m�todo escreve no registrador de configura��o C1 do periferico I2C.
 *
 *  @remarks    Sigla e pagina do Manual de Referencia KL25:
 *              - I2CxC1(D3): ACK
 *              - I2CxC1(D4): modo transmi��o
 *              - I2CxC1(D5): modo master
 *              - I2CxC1(D7): Habilita/desabilita o i2c. P�g.692
 */
void mkl_I2C::enableI2C() {
    *addressI2CxC1 = 0x80;
    // *addressI2CxC1 |= I2C_C1_TX_MASK;
}


/*!
 *  @fn         disableI2C
 *
 *  @brief      Desabilita o periferico I2C.
 *
 *  Este m�todo escreve no registrador de configura��o C1 do periferico I2C.
 *
 *  @remarks    Sigla e pagina do Manual de Referencia KL25:
 *              - I2CxC1(D3): ACK
 *              - I2CxC1(D4): modo transmi��o
 *              - I2CxC1(D5): modo master
 *              - I2CxC1(D7): Habilita/desabilita o i2c. P�g.692
 */
void mkl_I2C::disableI2C() {
    *addressI2CxC1 = 0;
    // *addressI2CxC1 &= ~I2C_C1_TX_MASK;
}


/*!
 *  @fn			clearInterruptFlag
 *
 * 	@brief		Limpa o flag de interrup��o
 *
 * 	Este m�todo escreve no registrador S do perif�rico I2C.
 *
 * 	@remarks	Sigla e pagina do Manual de Referencia KL25:
 * 				- I2CxS(D1): Limpa o flag de interrup��o. P�g. 695
 */
void mkl_I2C::clearInterruptFlag() {
    *addressI2CxS |= I2C_S_IICIF_MASK;
}

/*!
 *  @fn         bindPeripheral
 *
 *  @brief      Associa o objeto de software ao perif�rico de hardware.
 *
 *  Este m�todo associa ao objeto de software o perif�rico de hardware,
 *  utilizando a inicializa��o dos ponteiros para os endere�os de mem�ria
 *  dos registradores correspondentes.
 *
 *  @param[in]  I2CNumber - o n�mero do I2C ultilizado.
 *
 *  @remarks    Sigla e pagina do Manual de Refer�ncia KL25:
 *              - I2CxF: Frequency Divider Register. P�g.691.
 *              - I2CxC1: Control Register 1. P�g.692.
 *              - I2CxS: Status Register. P�g.694.
 *              - I2CxD: Data I/O Register. P�g.695.
 *              - I2CxSMB: Control and Status register. P�g.699.
 */
void mkl_I2C::bindPeripheral(uint32_t I2CNumber) {
    uint32_t baseAddress;

	/*!
	 * C�lculo do endere�o base do I2C do par�metro "I2CBaseAddress".
	 * Address(hexa): I2C0 = 40066000 I2C1 = 40067000.
	 * I2CBaseAddress = 0x400FF000 (Base I2C0) + 0x1000*(0 e 1) (Offset).
	 *
	 */
    baseAddress = I2C0_BASE + (uint32_t)(0x1000*I2CNumber);


	/*!
	 * C�lculo do endere�o absoluto do IC2xF para o I2C.
	 * Address(hexa): I2C0 = 40066000 I2C1 = 40067000.
	 * addressIC2xF = address base (Base) + 0x1 (Offset).
	 */
    addressI2CxF = (volatile uint8_t *)(baseAddress + 0x1);

	/*!
	 * C�lculo do endere�o absoluto do I2CxC1 para o I2C.
	 * Address(hexa): I2C0 = 40066000 I2C1 = 40067000.
	 * addressI2CxC1 = address base (Base) + 0x2 (Offset).
	 */
    addressI2CxC1 = (volatile uint8_t *)(baseAddress + 0x2);

	/*!
	 * C�lculo do endere�o absoluto do I2CxS para o I2C.
	 * Address(hexa): I2C0 = 40066000 I2C1 = 40067000.
	 * addressI2CxS = address base (Base) + 0x3 (Offset).
	 */
    addressI2CxS = (volatile uint8_t *)(baseAddress + 0x3);

	/*!
	 * C�lculo do endere�o absoluto do I2CxD para o I2C.
	 * Address(hexa): I2C0 = 40066000 I2C1 = 40067000.
	 * addressI2CxD = address base (Base) + 0x4 (Offset).
	 */
    addressI2CxD = (volatile uint8_t *)(baseAddress + 0x4);

	/*!
	 * C�lculo do endere�o absoluto do I2CxSMB para o I2C.
	 * Address(hexa): I2C0 = 40066000 I2C1 = 40067000.
	 * addressI2CxSMB = address base (Base) + 0x8 (Offset).
	 */
    addressI2Cx_SMB = (volatile uint8_t *)(baseAddress + 0x8);
}


/*!
 *   @fn         bindPin
 *
 *   @brief      Associa o pino do objeto ao perif�rico de hardare.
 *
 *   Este m�todo associa o pino do objeto de software ao pino do perif�rico.
 *
 *   @param[in]  pinNumber - o n�mero do pino do objeto de software.
 *   			 GPIONumber - o n�mero do GPIO.
 *
 *   @remarks    Sigla e pagina do Manual de Referencia KL25:
 *               - PCR: Pin Control Register. P�g.183.
 */
void mkl_I2C::bindPin(uint32_t pinNumber, uint32_t GPIONumber) {
	/*!
	 * C�lculo do endere�o absoluto do PCR para o I2C.
	 * addressPortxPCRn = 0x40049000 (Base) + 0x1000*(0,1,2,3,4 ou 5)
	 *                   + 4*(0,1,2,3,4,...,30) (Offset).
	 */
    addressPortxPCRn = (volatile uint32_t *) (0x40049000
                                            + 0x1000*GPIONumber + 4*pinNumber);
}

/*!
 *   @fn         selectMuxAlternative
 *
 *   @brief      Seleciona a alternativa de trabalho do pino.
 *
 *   Este m�todo seleciona o modo de opera��o do pino correspondente para o
 *   modo de opera��o I2C.
 *
 *   @param[in]  muxAlt - alternativa de opera��o do pino para o canal e I2C
 *                        especificados.
 *
 *   @remarks    Sigla e pagina do Manual de Referencia KL25:
 *               - PCR: Pin Control Register. P�g.183.
 */
void mkl_I2C::selectMuxAlternative(uint32_t muxAlt) {
    *addressPortxPCRn = PORT_PCR_MUX(muxAlt);
}


/*!
 *   @fn         setTPMParameters
 *
 *   @brief      Ajusta os par�metros do IC2.
 *
 *   Este m�todo ajusta os par�metros do I2C (n�meros de pino, GPIO,
 *   I2C) e a m�scara de sele��o do mux, de acordo com o membro
 *   da enum passado no construtor.
 *
 *   @param[in]  pin - pino passado para o construtor.
 *               pinNumber - n�mero do pino.
 *               GPIONumber - n�mero do GPIO.
 *               I2CNumber - n�mero do I2C.
 *               muxAltMask - m�scara de sele��o do mux.
 */
void mkl_I2C::setI2CParameters(i2c_Pin_t pin, uint32_t &pinNumber,
        uint32_t &GPIONumber, uint32_t &I2CNumber, uint32_t &muxAltMask) {
  pinNumber = pin & 0x00FF;
  GPIONumber = (pin >> 8) & 0x00FF;
  muxAltMask = (pin >> 16) & 0x00FF;
  I2CNumber = (pin >> 24) & 0x00FF;
}
