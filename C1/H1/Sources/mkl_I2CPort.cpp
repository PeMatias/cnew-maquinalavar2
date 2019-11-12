/*!
 * @copyright   © 2017 Universidade Federal do Amazonas.
 *
 * @brief       Implementação da API em C++ da classe mãe I2C.
 *
 * @file        mkl_I2CPort.cpp
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

#include "mkl_I2CPort.h"


/*!
 *   @brief    Construtor padrão da classe.
 *
 *   O construtor padrão da classe obtém o número do pino, do GPIO, do I2C usado e do mux a partir
 *   do pino desejado, associa fisicamento o objeto de software ao periférico
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
 *   @brief      Configura a velocidade de transmissão do I2C.
 *
 *   Este método configura a velocidade de transmissão do I2C no Frequency Divider register.
 *
 *   @param[in]  speed - O valor da velocidade de transmissão.
 *
 *   @remarks    Sigla e pagina do Manual de Referencia KL25:
 *               - I2CxF: Frequency Divider register. Pág. 691.
 */
void mkl_I2CPort::baudRate(i2c_baudRate_t speed) {
    disableI2C();
    clearInterruptFlag();
    *addressI2CxF = speed;
    enableI2C();
}

/*!
 *   @brief      Seta o endereço do escravo.
 *
 *   Este método seta o endereço do escravo.
 */
void mkl_I2CPort::setSlave(uint8_t address) {
    slaveAddress = address;
}

/*!
 *   @brief      Retorna o endereco do escravo.
 *
 *   Este método retorna do endereço do escravo.
 *
 *   @return     Endereço do escravo.
 *
 */
uint8_t mkl_I2CPort::getSlave() {
     return slaveAddress;
}

/*!
 *   @brief      Inicia a transmissão com o escravo.
 *
 *   Este método inicia da comunicação do I2C com o escravo.
 *
 *   @return     A exceção.
 *
 *   @remarks    Sigla e página do Manual de Referencia KL25:
 *               - I2CxS: I2C Status register. Pág. 694.
 *               - I2CxC1: I2C Control Register 1. Pág. 692.
 *               - I2CxD: I2C Data I/O register. Pág 695.
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
 *   @brief      Inicia a transmissão com o escravo.
 *
 *   Este método inicia da comunicação do I2C com o escravo.
 *
 *   @return     A exceção.
 *
 *   @remarks    Sigla e página do Manual de Referencia KL25:
 *               - I2CxS: I2C Status register. Pág. 694.
 *               - I2CxC1: I2C Control Register 1. Pág. 692.
 *               - I2CxD: I2C Data I/O register. Pág 695.
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
 *   Este método termina a transmição de escrita usando o registrador
 *   de controle I2CxC1.
 *
 *   @remarks    Sigla e página do Manual de Referencia KL25:
 *               - I2CxC1: I2C Control Register 1. Pág. 692.
 */
void mkl_I2CPort::stopTransmission() {
    *addressI2CxC1 &= ~0x30;
}

/*!
 *   @brief      Manda o dado para o I2C.
 *
 *   Este método envia de dados para o I2C usando o registrador
 *   de dados de entrada e saída I2CxD.
 *
 *   @remarks    Sigla e página do Manual de Referencia KL25:
 *               - I2CxD: I2C Data I/O register. Pág 695.
 *
 */
void mkl_I2CPort::send8Bits(uint8_t data) {
    *addressI2CxD = data;
}

/*!
 *   @brief      Espera a trasmissão do dado acabar.
 *
 *   Este método espera do término de transmissão de dados.
 *
 *   @remarks    Sigla e página do Manual de Referencia KL25:
 *               - I2CxS: I2C Status register. Pág. 694.
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
 *   Este método seleciona o modo de leitura do I2C e manda o endereço do slave,
 *   conforme o protocolo de I2C.
 *
 *   @return     A exceção.
 *
 *   @remarks    Sigla e página do Manual de Referencia KL25:
 *               - I2CxC1: I2C Control Register 1. Pág. 692.
 *               - I2CxD: I2C Data I/O register. Pág 695.
 *               - I2CxS: I2C Status register. Pág. 694.
 *               - I2Cx_SMB: I2C SMBus Control and Status register. Pág. 699.
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
 *   Este método seleciona o modo de leitura do I2C e manda o endereço do slave,
 *   conforme o protocolo de I2C, podendo escolher o endereço.
 *
 *   @return     A exceção.
 *
 *   @remarks    Sigla e página do Manual de Referencia KL25:
 *               - I2CxC1: I2C Control Register 1. Pág. 692.
 *               - I2CxD: I2C Data I/O register. Pág 695.
 *               - I2CxS: I2C Status register. Pág. 694.
 *               - I2Cx_SMB: I2C SMBus Control and Status register. Pág. 699.
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
 *   @brief      Espera o enderenço do slave ser enviado.
 *
 *   Este método configura a espera pelo enderenço do slave a ser enviado
 *   e espera a confimação ultilizando o registrador de status.
 *
 *   @remarks    Sigla e página do Manual de Referencia KL25:
 *               - I2CxS: I2C Status register. Pág. 694.
 */
i2c_Exception_t mkl_I2CPort::waitArrived() {
    *addressI2CxC1 |= I2C_C1_TXAK_MASK;

    while (!(*addressI2CxS & I2C_S_IICIF_MASK)) {}
    *addressI2CxS |= I2C_S_IICIF_MASK;

    *addressI2CxC1 &= ~I2C_C1_MST_MASK;
}

/*!
 *   @brief      Lê o dado do escravo.
 *
 *   Este método realiza a leitura do dado do escravo, retornando
 *   o dado no registrador I2CxD.
 *
 *   @return     O dado no registrador I2CxD.
 *
 *   @remarks    Sigla e página do Manual de Referencia KL25:
 *               - I2CxD: I2C Data I/O register. Pág 695.
 *
 */
uint8_t mkl_I2CPort::receive8Bits() {
    return *addressI2CxD;
}

/*!
 *   @brief      Habilita o I2C a trabalhar com o Ack.
 *
 *   Este método habilita o I2C a trabalhar com o Ack, através
 *   o registrador I2CxC1.
 *
 *   @remarks    Sigla e página do Manual de Referencia KL25:
 *               - I2CxC1: I2C Control Register 1. Pág. 692.
 */
void mkl_I2CPort::enableAck() {
    *addressI2CxC1 |= I2C_C1_TXAK_MASK;
}

/*!
 *   @brief      Desabilita o Ack.
 *
 *   Este método desabilita o Ack através do registrador I2Cxc1.
 *
 *   @remarks    Sigla e página do Manual de Referencia KL25:
 *               - I2CxC1: I2C Control Register 1. Pág. 692.
 *
 */
void mkl_I2CPort::disableAck() {
    *addressI2CxC1 &= ~I2C_C1_TXAK_MASK;
}

/*!
 *   @brief      Retorna a exceção.
 *
 *   Este método configura a ocorrência de exceção e retorna o valor da mesma.
 *
 *   @return     A exceção.
 *
 */
i2c_Exception_t mkl_I2CPort::ExceptionOcurred() {
    return exception;
}
