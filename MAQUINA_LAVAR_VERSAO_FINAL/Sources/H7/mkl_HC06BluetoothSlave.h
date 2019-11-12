/*!
 * @copyright   Â© 2017 Felipe R. Monteiro <rms.felipe@gmail.com>
 *                     Francisco FÃ©lix <frfelix7@gmail.com>
 *
 * @brief       Interface da classe mkl_HC06BluetoothSlave.
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

#ifndef INCLUDES_MKL_HC06BLUETOOTHSLAVE_H_
#define INCLUDES_MKL_HC06BLUETOOTHSLAVE_H_

#include "mkl_UARTPort.h"
#include "mkl_UARTInterrupt.h"

/*!
 *  @class mkl_HC06BluetoothSlave
 *
 *  @brief    Classe de implementaÃ§Ã£o do perifÃ©rico bluetooth para a placa KL25Z128.
 *
 *  @details  Classe para configuraÃ§Ã£o do perifÃ©rico bluetooth HC06.
 *
 *  @section  EXAMPLES USAGE
 *
 *            Uso dos mÃ©todos de configuraÃ§Ã£o.
 *             +fn mkl_HC06BluetoothSlave(uart_PinTx_t::uart0_PTA2, uart_PinRx_t::uart0_PTA1);
 *             +fn setSlaveName("bluetooth");
 *             +fn setSlavePassword ("123");
 */
class mkl_HC06BluetoothSlave : public mkl_UARTInterrupt {
 public:
    /*!
     * Configura o perifÃ©rico on-chip UART para comunicaÃ§Ã£o via rede bluetooth.
     */
    mkl_HC06BluetoothSlave(uart_PinTx_t pinTx, uart_PinRx_t pinRx);
    /*!
     * Configura um nome para o perifÃ©rico.
     */
    void setSlaveName(char* name);
    /*!
     * Configura uma senha para o perifÃ©rico.
     */
    void setSlavePassword(char* code);
    /*!
     * Verifica se ocorreu um erro na comunicaÃ§Ã£o.
     */
    uart_Exception_t checkException();
    /*!
     * Espera a chegada de um dado de comunicaÃ§Ã£o e, se
     * ocorrer alguma erro, retorna dfs_ParityError ou dsf_OverWriteError.
     */
    uart_Exception_t waitArrivedData();
    /*!
     * Retorna o dado recebido.
     */
    uint8_t receive8Bits();
    /*!
     * Envia um dado de 8-bits.
     */
    void send8BitTest(uint8_t bit);

 private:
    /*!
     * Nome do perifÃ©rico.
     */
    volatile char* slaveName;
    /*!
     * Senha do perifÃ©rico.
     */
    volatile char* password;
    /*!
     * Canal de comunicaÃ§Ã£o.
     */
    mkl_UARTPort uartPort;
};

#endif /* INCLUDES_MKL_HC06BLUETOOTHSLAVE_H_ */