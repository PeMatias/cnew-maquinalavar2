/*!
 * @copyright   � 2017 Universidade Federal do Amazonas.
 *
 * @brief       Implementa��o da API em C++ da classe m�e I2C.
 *
 * @file        mkl_I2CPort.cpp
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

#include "mkl_I2CPort.h"


/*!
 *   @brief    Construtor padr�o da classe.
 *
 *   O construtor padr�o da classe obt�m o n�mero do pino, do GPIO, do I2C usado e do mux a partir
 *   do pino desejado, associa fisicamento o objeto de software ao perif�rico
 *   de hardware, habilita o clock do GPIO, habilita o clock do I2C e habilita o mesmo.
 */
mkl_I2CPort::mkl_I2CPort(i2c_Pin_t pinSCL, i2c_Pin_t pinSDA) {
    uint32_t muxAltMask;
    uint32_t pinNumber;
    uint32_t GPIONumber;
    uint32_t I2CNumber;

    setI2CParameters(pinSCL, pinNumber, GPIONumber, I2CNumber, muxAltMask);
    bindPeripheral(I2CNumber);
    enablePeripheralClock(I2CNumber);
    enableGPIOClock(GPIONumber);
    bindPin(pinNumber, GPIONumber);
    selectMuxAlternative(muxAltMask);
    setI2CParameters(pinSDA, pinNumber, GPIONumber, I2CNumber, muxAltMask);
    bindPin(pinNumber, GPIONumber);
    selectMuxAlternative(muxAltMask);
}

/*!
 *   @brief      Configura a velocidade de transmiss�o do I2C.
 *
 *   Este m�todo configura a velocidade de transmiss�o do I2C no Frequency Divider register.
 *
 *   @param[in]  speed - O valor da velocidade de transmiss�o.
 *
 *   @remarks    Sigla e pagina do Manual de Referencia KL25:
 *               - I2CxF: Frequency Divider register. P�g. 691.
 */
void mkl_I2CPort::baudRate(i2c_baudRate_t speed) {
    disableI2C();
    clearInterruptFlag();
    *addressI2CxF = speed;
    enableI2C();
}

/*!
 *   @brief      Seta o endere�o do escravo.
 *
 *   Este m�todo seta o endere�o do escravo.
 */
void mkl_I2CPort::setSlave(uint8_t address) {
    slaveAddress = address;
}

/*!
 *   @brief      Retorna o endereco do escravo.
 *
 *   Este m�todo retorna do endere�o do escravo.
 *
 *   @return     Endere�o do escravo.
 *
 */
uint8_t mkl_I2CPort::getSlave() {
     return slaveAddress;
}

/*!
 *   @brief      Inicia a transmiss�o com o escravo.
 *
 *   Este m�todo inicia da comunica��o do I2C com o escravo.
 *
 *   @return     A exce��o.
 *
 *   @remarks    Sigla e p�gina do Manual de Referencia KL25:
 *               - I2CxS: I2C Status register. P�g. 694.
 *               - I2CxC1: I2C Control Register 1. P�g. 692.
 *               - I2CxD: I2C Data I/O register. P�g 695.
 */
i2c_Exception_t mkl_I2CPort::startTransmission() {
    while (*addressI2CxS & I2C_S_BUSY_MASK) {
        exception = i2c_erroBusBusy;
        return exception;
    }
    *addressI2CxC1 |= I2C_C1_TX_MASK;
    *addressI2CxC1 |= I2C_C1_MST_MASK;

    *addressI2CxD = (slaveAddress << 1);

    while (!(*addressI2CxS & I2C_S_IICIF_MASK)) {}
    *addressI2CxS |= I2C_S_IICIF_MASK;

    if (*addressI2CxS & I2C_S_ARBL_MASK) {
        *addressI2CxS |= I2C_S_ARBL_MASK;
        exception = i2c_erroArbitrationLost;
        return exception;
    }
    if (*addressI2CxS & I2C_S_RXAK_MASK) {
        exception = i2c_erroNoAck;
        return exception;
    }
}

/*!
 *   @brief      Inicia a transmiss�o com o escravo.
 *
 *   Este m�todo inicia da comunica��o do I2C com o escravo.
 *
 *   @return     A exce��o.
 *
 *   @remarks    Sigla e p�gina do Manual de Referencia KL25:
 *               - I2CxS: I2C Status register. P�g. 694.
 *               - I2CxC1: I2C Control Register 1. P�g. 692.
 *               - I2CxD: I2C Data I/O register. P�g 695.
 */
i2c_Exception_t mkl_I2CPort::startTransmissionTo(uint8_t address) {
    while (*addressI2CxS & I2C_S_BUSY_MASK) {
        exception = i2c_erroBusBusy;
        return exception;
    }
    *addressI2CxC1 |= I2C_C1_TX_MASK;
    *addressI2CxC1 |= I2C_C1_MST_MASK;

    *addressI2CxD = (address << 1);

    while (!(*addressI2CxS & I2C_S_IICIF_MASK)) {}
    *addressI2CxS |= I2C_S_IICIF_MASK;

    if (*addressI2CxS & I2C_S_ARBL_MASK) {
        *addressI2CxS |= I2C_S_ARBL_MASK;
        exception  = i2c_erroArbitrationLost;
        return exception;
    }
    if (*addressI2CxS & I2C_S_RXAK_MASK) {
        exception = i2c_erroNoAck;
        return exception;
    }
}

/*!
 *   @brief      Termina o processo de escrita.
 *
 *   Este m�todo termina a transmi��o de escrita usando o registrador
 *   de controle I2CxC1.
 *
 *   @remarks    Sigla e p�gina do Manual de Referencia KL25:
 *               - I2CxC1: I2C Control Register 1. P�g. 692.
 */
void mkl_I2CPort::stopTransmission() {
    *addressI2CxC1 &= ~0x30;
}

/*!
 *   @brief      Manda o dado para o I2C.
 *
 *   Este m�todo envia de dados para o I2C usando o registrador
 *   de dados de entrada e sa�da I2CxD.
 *
 *   @remarks    Sigla e p�gina do Manual de Referencia KL25:
 *               - I2CxD: I2C Data I/O register. P�g 695.
 *
 */
void mkl_I2CPort::send8Bits(uint8_t data) {
    *addressI2CxD = data;
}

/*!
 *   @brief      Espera a trasmiss�o do dado acabar.
 *
 *   Este m�todo espera do t�rmino de transmiss�o de dados.
 *
 *   @remarks    Sigla e p�gina do Manual de Referencia KL25:
 *               - I2CxS: I2C Status register. P�g. 694.
 *
 */
void mkl_I2CPort::waitTransfer() {
    while (!(*addressI2CxS & I2C_S_IICIF_MASK)) {}
    *addressI2CxS |= I2C_S_IICIF_MASK;

    if (*addressI2CxS & I2C_S_RXAK_MASK) {
        exception = i2c_erroNoAck;
    }
}

/*!
 *   @brief      Seleciona o modo de leitra do I2C.
 *
 *   Este m�todo seleciona o modo de leitura do I2C e manda o endere�o do slave,
 *   conforme o protocolo de I2C.
 *
 *   @return     A exce��o.
 *
 *   @remarks    Sigla e p�gina do Manual de Referencia KL25:
 *               - I2CxC1: I2C Control Register 1. P�g. 692.
 *               - I2CxD: I2C Data I/O register. P�g 695.
 *               - I2CxS: I2C Status register. P�g. 694.
 *               - I2Cx_SMB: I2C SMBus Control and Status register. P�g. 699.
 *
 */
i2c_Exception_t mkl_I2CPort:: selectReceptionMode() {
    volatile unsigned char dummy;

    *addressI2CxC1 |= I2C_C1_RSTA_MASK;

    *addressI2CxD = (slaveAddress << 1) | 1;

    while (!(*addressI2CxS & I2C_S_IICIF_MASK)) {}
    *addressI2CxS |= I2C_S_IICIF_MASK;

    if (*addressI2CxS & I2C_S_RXAK_MASK) {
        exception = i2c_erroNoAck;
        return exception;
    }
    *addressI2CxC1 &= ~0x18;

    *addressI2CxC1 |= I2C_C1_TXAK_MASK;
    dummy = *addressI2CxD;

    *addressI2Cx_SMB |= I2C_SMB_FACK_MASK;
}

/*!
 *   @brief      Seleciona o modo de leitra do I2C.
 *
 *   Este m�todo seleciona o modo de leitura do I2C e manda o endere�o do slave,
 *   conforme o protocolo de I2C, podendo escolher o endere�o.
 *
 *   @return     A exce��o.
 *
 *   @remarks    Sigla e p�gina do Manual de Referencia KL25:
 *               - I2CxC1: I2C Control Register 1. P�g. 692.
 *               - I2CxD: I2C Data I/O register. P�g 695.
 *               - I2CxS: I2C Status register. P�g. 694.
 *               - I2Cx_SMB: I2C SMBus Control and Status register. P�g. 699.
 */
i2c_Exception_t mkl_I2CPort:: selectReceptionModeFrom(uint8_t slave) {
    volatile unsigned char dummy;

    *addressI2CxC1 |= I2C_C1_RSTA_MASK;

    *addressI2CxD = (slave << 1) | 1;

    while (!(*addressI2CxS & I2C_S_IICIF_MASK)) {}
    *addressI2CxS |= I2C_S_IICIF_MASK;

    if (*addressI2CxS & I2C_S_RXAK_MASK) {
        exception = i2c_erroNoAck;
        return exception;
    }

    *addressI2CxC1 &= ~0x18;

    *addressI2CxC1 |= I2C_C1_TXAK_MASK;
    dummy = *addressI2CxD;

    *addressI2Cx_SMB |= I2C_SMB_FACK_MASK;
}

/*!
 *   @brief      Espera o enderen�o do slave ser enviado.
 *
 *   Este m�todo configura a espera pelo enderen�o do slave a ser enviado
 *   e espera a confima��o ultilizando o registrador de status.
 *
 *   @remarks    Sigla e p�gina do Manual de Referencia KL25:
 *               - I2CxS: I2C Status register. P�g. 694.
 */
i2c_Exception_t mkl_I2CPort::waitArrived() {
    *addressI2CxC1 |= I2C_C1_TXAK_MASK;

    while (!(*addressI2CxS & I2C_S_IICIF_MASK)) {}
    *addressI2CxS |= I2C_S_IICIF_MASK;

    *addressI2CxC1 &= ~I2C_C1_MST_MASK;
}

/*!
 *   @brief      L� o dado do escravo.
 *
 *   Este m�todo realiza a leitura do dado do escravo, retornando
 *   o dado no registrador I2CxD.
 *
 *   @return     O dado no registrador I2CxD.
 *
 *   @remarks    Sigla e p�gina do Manual de Referencia KL25:
 *               - I2CxD: I2C Data I/O register. P�g 695.
 *
 */
uint8_t mkl_I2CPort::receive8Bits() {
    return *addressI2CxD;
}

/*!
 *   @brief      Habilita o I2C a trabalhar com o Ack.
 *
 *   Este m�todo habilita o I2C a trabalhar com o Ack, atrav�s
 *   o registrador I2CxC1.
 *
 *   @remarks    Sigla e p�gina do Manual de Referencia KL25:
 *               - I2CxC1: I2C Control Register 1. P�g. 692.
 */
void mkl_I2CPort::enableAck() {
    *addressI2CxC1 |= I2C_C1_TXAK_MASK;
}

/*!
 *   @brief      Desabilita o Ack.
 *
 *   Este m�todo desabilita o Ack atrav�s do registrador I2Cxc1.
 *
 *   @remarks    Sigla e p�gina do Manual de Referencia KL25:
 *               - I2CxC1: I2C Control Register 1. P�g. 692.
 *
 */
void mkl_I2CPort::disableAck() {
    *addressI2CxC1 &= ~I2C_C1_TXAK_MASK;
}

/*!
 *   @brief      Retorna a exce��o.
 *
 *   Este m�todo configura a ocorr�ncia de exce��o e retorna o valor da mesma.
 *
 *   @return     A exce��o.
 *
 */
i2c_Exception_t mkl_I2CPort::ExceptionOcurred() {
    return exception;
}
