/*!
 * @copyright   Â© 2017 Felipe R. Monteiro <rms.felipe@gmail.com>
 *                     Francisco FÃ©lix <frfelix7@gmail.com>
 *
 * @brief       ImplementaÃ§Ã£o dos mÃ©todos da classe mkl_HC06BluetoothSlave.
 *
 * @file        mkl_HC06BluetoothSlave.h
 * @version     1.0
 * @date        1 Dezembro 2017
 *
 * @section     HARDWARES & SOFTWARES
 *              +board        FRDM-KL25Z da NXP.
 *              +processor    MKL25Z128VLK4 - ARM Cortex-M0+
 *              +compiler     KinetisÂ® Design Studio IDE
 *              +manual       L25P80M48SF0RM, Rev.3, September 2012
 *              +revisions    VersÃ£o (data): DescriÃ§Ã£o breve.
 *                             ++ 1.0 (1 Dezembro 2017): VersÃ£o inicial.
 *
 * @section     AUTHORS & DEVELOPERS
 *              +institution  Universidade Federal do Amazonas
 *              +courses      Engenharia da ComputaÃ§Ã£o / Engenharia ElÃ©trica
 *              +teacher      Miguel Grimm <miguelgrimm@gmail.com>
 *              +student      VersÃ£o inicial:
 *                              ++ Felipe R. Monteiro <rms.felipe@gmail.com>
 *                              ++ Francisco FÃ©lix    <frfelix7@gmail.com>
 *
 * @section     LICENSE
 *
 *              GNU General Public License (GNU GPL)
 *
 *              Este programa Ã© um software livre; VocÃª pode redistribuÃ­-lo
 *              e/ou modificÃ¡-lo de acordo com os termos do "GNU General Public
 *              License" como publicado pela Free Software Foundation; Seja a
 *              versÃ£o 3 da licenÃ§a, ou qualquer versÃ£o posterior.
 *
 *              Este programa Ã© distribuÃ­do na esperanÃ§a de que seja Ãºtil,
 *              mas SEM QUALQUER GARANTIA; Sem a garantia implÃ­cita de
 *              COMERCIALIZAÃ‡ÃƒO OU USO PARA UM DETERMINADO PROPÃ“SITO.
 *              Veja o site da "GNU General Public License" para mais detalhes.
 *
 * @htmlonly    http://www.gnu.org/copyleft/gpl.html
 */

#include "mkl_HC06BluetoothSlave.h"
#include <cassert>
#include <cstring>

/*!
 *  @fn  mkl_HC06BluetoothSlave
 *
 *  @brief  Configura o perifÃ©rico on-chip UART para
 *          comunicaÃ§Ã£o via rede bluetooth.
 *
 *  @param[in] pinTx - pino TX.
 *             pinRx - pino RX.
 */
mkl_HC06BluetoothSlave::mkl_HC06BluetoothSlave(uart_PinTx_t pinTx,
                                               uart_PinRx_t pinRx) {
	mkl_UART_t uart;
    this->uartPort = mkl_UARTPort(pinTx, pinRx);
    this->uartPort.setFrame(mkl_8bit, mkl_None, mkl_One, mkl_LSB);
    this->uartPort.setBaudRate(9600);

    if ((pinRx == uart_PinRx_t::uart0_PTA1) ||
        (pinRx == uart_PinRx_t::uart0_PTD6) ||
	    (pinRx == uart_PinRx_t::uart0_PTE21)) {
        this->UARTx_IRQn = UART0_IRQn;
        uart = mkl_UART_t::mkl_UART0;
    } else if ((pinRx == uart_PinRx_t::uart1_PTC3) ||
    		   (pinRx == uart_PinRx_t::uart1_PTE1)) {
        this->UARTx_IRQn = UART1_IRQn;
        uart = mkl_UART_t::mkl_UART1;
    } else {
        this->UARTx_IRQn = UART2_IRQn;
        uart = mkl_UART_t::mkl_UART2;
    }
    this->addressUARTxC2 = reinterpret_cast<uint8_t *>(0x4006A003 +
                                                      (0x00001000 * uart));
}

/*!
 *  @fn  setSlaveName
 *
 *  @brief  Nomear o perifÃ©rico.
 *
 *  @param[in] name - string com nome do perifÃ©rco.
 */


void mkl_HC06BluetoothSlave::setSlaveName(char* name) {
    if (name != NULL) {
        this->slaveName = name;
    } else {
        //! error
    }
}

/*!
 *  @fn  setSlavePassword
 *
 *  @brief  Adicionar senha para o perifÃ©rico.
 *
 *  @param[in] code - string com senha.
 */
void mkl_HC06BluetoothSlave::setSlavePassword(char* code) {
    if (code != NULL) {
        this->password = code;
    } else {
        //! error
    }
}

/*!
 *  @fn  enableConnection
 *
 *  @brief  Estabelece uma conexÃ£o.
 */


/*!
 *  @fn  checkException
 *
 *  @brief  Verifica se ocorreu um erro na comunicaÃ§Ã£o.
 *
 *  @return ExceÃ§Ã£o do tipo uart_Exception_t.
 */
uart_Exception_t mkl_HC06BluetoothSlave::checkException() {
    //! TODO(Felipe e Francisco): implementar.
}

/*!
 *  @fn  waitArrivedData
 *
 *  @brief  Espera a chegada de um dado de comunicaÃ§Ã£o e, se
 *          ocorrer alguma erro, retorna dfs_ParityError ou dsf_OverWriteError.
 *
 *  @return ExceÃ§Ã£o do tipo uart_Exception_t.
 */
uart_Exception_t mkl_HC06BluetoothSlave::waitArrivedData() {
    return this->uartPort.waitArrived();
}

/*!
 *  @fn  receive8Bits
 *
 *  @brief  Retorna o dado recebido e armazenado no objeto.
 *
 *  @return Dado de 8 bits.
 */
uint8_t mkl_HC06BluetoothSlave::receive8Bits() {
	//this->uartPort.waitArrived();
    return this->uartPort.receiveNBits();
}

/*!
 *  @fn  receive8Bits
 *
 *  @brief  Envia um dado de 8-bits.
 */
void mkl_HC06BluetoothSlave::send8BitTest(uint8_t bit) {
    this->uartPort.waitTransfer();
    this->uartPort.sendNBits(bit);
}