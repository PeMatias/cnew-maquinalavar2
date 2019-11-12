/*!
 * @copyright   © 2017 Universidade Federal do Amazonas.
 *
 * @brief       Implementação da API em C++ da classe mãe I2C.
 *
 * @file        mkl_I2C.cpp
 * @version     1.0
 * @date        07 Dezembro 2017
 *
 * @section     HARDWARES & SOFTWARES
 *              +board        FRDM-KL25Z da NXP.
 *              +processor    MKL25Z128VLK4 - ARM Cortex-M0+
 *              +compiler     Kinetis® Design Studio IDE
 *              +manual       L25P80M48SF0RM, Rev.3, September 2012
 *              +revisions    Versão (data): Descrição breve.
 *                             ++ 1.0 (07 Dezembro 2017): Versão inicial.
 *
 * @section     AUTHORS & DEVELOPERS
 *              +institution  Universidade Federal do Amazonas
 *              +courses      Engenharia da Computação / Engenharia Elétrica
 *              +teacher      Miguel Grimm <miguelgrimm@gmail.com>
 *              +student      Versão inicial:
 *                             ++ Leticia Flores <leticia.flors@gmail.com>
 * 							   ++ Matheus de Sousa Castro <matheus.sousa110@gmail.com>
 * 							   ++ Stephanie Lopes <stephanielopees@gmail.com>
 * 						       ++ Victoria da Silva Leite <victoria_leite@hotmail.com>
 *
 * @section     LICENSE
 *
 *              GNU General Public License (GNU GPL).
 *
 *              Este programa é um software livre; Você pode redistribuí-lo
 *              e/ou modificá-lo de acordo com os termos do "GNU General Public
 *              License" como publicado pela Free Software Foundation; Seja a
 *              versão 3 da licença, ou qualquer versão posterior.
 *
 *              Este programa é distribuído na esperança de que seja útil,
 *              mas SEM QUALQUER GARANTIA; Sem a garantia implícita de
 *              COMERCIALIZAÇÃO OU USO PARA UM DETERMINADO PROPÓSITO.
 *              Veja o site da "GNU General Public License" para mais detalhes.
 *
 * @htmlonly    http://www.gnu.org/copyleft/gpl.html
 */

#include "mkl_I2C.h"

/*!
 *  @fn         enablePeripheralClock
 *
 *  @brief      Habilita o clock do periférico de hardware.
 *
 *  Este método habilita o clock do periférico I2C solicitado.
 *
 *  @remarks    Sigla e pagina do Manual de Referencia KL25:
 *               - SCGC4: System Cock Gating Control Register 4. Pág.204.
 */
void mkl_I2C::enablePeripheralClock(uint32_t I2CNumber) {
    SIM_SCGC4 |= (SIM_SCGC4_I2C0_MASK << I2CNumber);
}


/*!
 *  @fn         enableGPIOClock
 *
 *  @brief      Habilita o clock do GPIO do pino.
 *
 *  Este método habilita o clock do periférico GPIO do pino passado por
 *  parâmetro.
 *
 *  @param[in]  GPIONumber - o número do GPIO correspondente ao pino.
 *
 *  @remarks    Sigla e pagina do Manual de Referencia KL25:
 *              - SCGC5: System Cock Gating Control Register 5. Pág.206.
 */
void mkl_I2C::enableGPIOClock(uint32_t GPIONumber) {
    SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK << GPIONumber;
}


/*!
 *  @fn         enableI2C
 *
 *  @brief      Habilita o periferico I2C.
 *
 *  Este método escreve no registrador de configuração C1 do periferico I2C.
 *
 *  @remarks    Sigla e pagina do Manual de Referencia KL25:
 *              - I2CxC1(D3): ACK
 *              - I2CxC1(D4): modo transmição
 *              - I2CxC1(D5): modo master
 *              - I2CxC1(D7): Habilita/desabilita o i2c. Pág.692
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
 *  Este método escreve no registrador de configuração C1 do periferico I2C.
 *
 *  @remarks    Sigla e pagina do Manual de Referencia KL25:
 *              - I2CxC1(D3): ACK
 *              - I2CxC1(D4): modo transmição
 *              - I2CxC1(D5): modo master
 *              - I2CxC1(D7): Habilita/desabilita o i2c. Pág.692
 */
void mkl_I2C::disableI2C() {
    *addressI2CxC1 = 0;
    // *addressI2CxC1 &= ~I2C_C1_TX_MASK;
}


/*!
 *  @fn			clearInterruptFlag
 *
 * 	@brief		Limpa o flag de interrupção
 *
 * 	Este método escreve no registrador S do periférico I2C.
 *
 * 	@remarks	Sigla e pagina do Manual de Referencia KL25:
 * 				- I2CxS(D1): Limpa o flag de interrupção. Pág. 695
 */
void mkl_I2C::clearInterruptFlag() {
    *addressI2CxS |= I2C_S_IICIF_MASK;
}

/*!
 *  @fn         bindPeripheral
 *
 *  @brief      Associa o objeto de software ao periférico de hardware.
 *
 *  Este método associa ao objeto de software o periférico de hardware,
 *  utilizando a inicialização dos ponteiros para os endereços de memória
 *  dos registradores correspondentes.
 *
 *  @param[in]  I2CNumber - o número do I2C ultilizado.
 *
 *  @remarks    Sigla e pagina do Manual de Referência KL25:
 *              - I2CxF: Frequency Divider Register. Pág.691.
 *              - I2CxC1: Control Register 1. Pág.692.
 *              - I2CxS: Status Register. Pág.694.
 *              - I2CxD: Data I/O Register. Pág.695.
 *              - I2CxSMB: Control and Status register. Pág.699.
 */
void mkl_I2C::bindPeripheral(uint32_t I2CNumber) {
    uint32_t baseAddress;

	/*!
	 * Cálculo do endereço base do I2C do parâmetro "I2CBaseAddress".
	 * Address(hexa): I2C0 = 40066000 I2C1 = 40067000.
	 * I2CBaseAddress = 0x400FF000 (Base I2C0) + 0x1000*(0 e 1) (Offset).
	 *
	 */
    baseAddress = I2C0_BASE + (uint32_t)(0x1000*I2CNumber);


	/*!
	 * Cálculo do endereço absoluto do IC2xF para o I2C.
	 * Address(hexa): I2C0 = 40066000 I2C1 = 40067000.
	 * addressIC2xF = address base (Base) + 0x1 (Offset).
	 */
    addressI2CxF = (volatile uint8_t *)(baseAddress + 0x1);

	/*!
	 * Cálculo do endereço absoluto do I2CxC1 para o I2C.
	 * Address(hexa): I2C0 = 40066000 I2C1 = 40067000.
	 * addressI2CxC1 = address base (Base) + 0x2 (Offset).
	 */
    addressI2CxC1 = (volatile uint8_t *)(baseAddress + 0x2);

	/*!
	 * Cálculo do endereço absoluto do I2CxS para o I2C.
	 * Address(hexa): I2C0 = 40066000 I2C1 = 40067000.
	 * addressI2CxS = address base (Base) + 0x3 (Offset).
	 */
    addressI2CxS = (volatile uint8_t *)(baseAddress + 0x3);

	/*!
	 * Cálculo do endereço absoluto do I2CxD para o I2C.
	 * Address(hexa): I2C0 = 40066000 I2C1 = 40067000.
	 * addressI2CxD = address base (Base) + 0x4 (Offset).
	 */
    addressI2CxD = (volatile uint8_t *)(baseAddress + 0x4);

	/*!
	 * Cálculo do endereço absoluto do I2CxSMB para o I2C.
	 * Address(hexa): I2C0 = 40066000 I2C1 = 40067000.
	 * addressI2CxSMB = address base (Base) + 0x8 (Offset).
	 */
    addressI2Cx_SMB = (volatile uint8_t *)(baseAddress + 0x8);
}


/*!
 *   @fn         bindPin
 *
 *   @brief      Associa o pino do objeto ao periférico de hardare.
 *
 *   Este método associa o pino do objeto de software ao pino do periférico.
 *
 *   @param[in]  pinNumber - o número do pino do objeto de software.
 *   			 GPIONumber - o número do GPIO.
 *
 *   @remarks    Sigla e pagina do Manual de Referencia KL25:
 *               - PCR: Pin Control Register. Pág.183.
 */
void mkl_I2C::bindPin(uint32_t pinNumber, uint32_t GPIONumber) {
	/*!
	 * Cálculo do endereço absoluto do PCR para o I2C.
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
 *   Este método seleciona o modo de operação do pino correspondente para o
 *   modo de operação I2C.
 *
 *   @param[in]  muxAlt - alternativa de operação do pino para o canal e I2C
 *                        especificados.
 *
 *   @remarks    Sigla e pagina do Manual de Referencia KL25:
 *               - PCR: Pin Control Register. Pág.183.
 */
void mkl_I2C::selectMuxAlternative(uint32_t muxAlt) {
    *addressPortxPCRn = PORT_PCR_MUX(muxAlt);
}


/*!
 *   @fn         setTPMParameters
 *
 *   @brief      Ajusta os parâmetros do IC2.
 *
 *   Este método ajusta os parâmetros do I2C (números de pino, GPIO,
 *   I2C) e a máscara de seleção do mux, de acordo com o membro
 *   da enum passado no construtor.
 *
 *   @param[in]  pin - pino passado para o construtor.
 *               pinNumber - número do pino.
 *               GPIONumber - número do GPIO.
 *               I2CNumber - número do I2C.
 *               muxAltMask - máscara de seleção do mux.
 */
void mkl_I2C::setI2CParameters(i2c_Pin_t pin, uint32_t &pinNumber,
        uint32_t &GPIONumber, uint32_t &I2CNumber, uint32_t &muxAltMask) {
  pinNumber = pin & 0x00FF;
  GPIONumber = (pin >> 8) & 0x00FF;
  muxAltMask = (pin >> 16) & 0x00FF;
  I2CNumber = (pin >> 24) & 0x00FF;
}
