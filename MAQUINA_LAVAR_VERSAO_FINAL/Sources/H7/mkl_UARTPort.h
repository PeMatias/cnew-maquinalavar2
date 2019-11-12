/*!
 * @copyright   Â© 2017 Felipe R. Monteiro <rms.felipe@gmail.com>
 * 					   Francisco FÃ©lix <frfelix7@gmail.com>
 *
 * @brief       Interface da classe mkl_UARTPort.
 *
 * @file        mkl_UARTPort.h
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
 *                             	++ Felipe R. Monteiro <rms.felipe@gmail.com>
 * 								++ Francisco FÃ©lix 	  <frfelix7@gmail.com>
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

#ifndef INCLUDES_MKL_UARTPORT_H_
#define INCLUDES_MKL_UARTPORT_H_

#include "mkl_UART.h"

/*!
 *  @class mkl_UARTPort
 *
 *  @brief    Classe de implementaÃ§Ã£o do perifÃ©rico UART para a placa KL25Z128.
 *
 *  @details  Esta classe Ã© usada para configuraÃ§Ã£o do protocolo UART
 *  		  de comunicaÃ§Ã£o. O pino de transmissÃ£o (Tx) do protocolo
 *  		  envia um pacote de bits que serÃ¡ interpretado bit a bit
 *  		  pelo pino receptor. Cada pacote enviado contÃ©m 1 start
 *  		  bit que indica o inÃ­cio da mensagem, 1 ou 2 stop bits para
 *  		  indicar o final da mensagem, 5 a 9 bits de informaÃ§Ã£o e 1
 *  		  bit de paridade para evitar a recepÃ§Ã£o de erros.
 *
 *  @section  EXAMPLES USAGE
 *
 *            Uso dos mÃ©todos de recepÃ§Ã£o.
 *	           +fn bool startBitAvaliable();
 *	           +fn uart_Exception_t waitArrived();
 *             +fn uint8_t receiveNBits();
 *
 *            Uso dos mÃ©todos de transmissÃ£o.
 *	           +fn void sendNBits(uint16_t data);
 *             +fn void cancelSend();
 *             +fn void waitTransfer();
 */
class mkl_UARTPort{
 public:
    mkl_UARTPort();
    /*!
     * Construtor responsÃ¡vel por configurar a porta UART escolhida.
     */
    mkl_UARTPort(uart_PinTx_t pinTx, uart_PinRx_t pinRx);
    /*!
     * MÃ©todo que determina o tamanho do frame.
     */
    void setFrame(uart_LengthData_t length_data,
                  uart_Parity_t parity,
                  uart_StopBit_t stop,
                  uart_FistBit_t fistBit);
    /*!
     * MÃ©todo que determina a taxa de transmissÃ£o.
     */
    void setBaudRate(uint16_t rate);
    /*!
     * MÃ©todo que detecta uma exceÃ§Ã£o durante o envio/recebimento de dados.
     */
    uart_Exception_t exceptionOccurred();
    /*!
     * MÃ©todo que limpa informaÃ§Ãµes residuais da UART.
     */
    void clearPeripheral();
    /*!
     * MÃ©todo que retorna o dado recebido.
     */
    uint8_t receiveNBits();
    /*!
     * MÃ©todo que aguarda chegada de dados.
     */
    uart_Exception_t waitArrived();
    /*!
     * MÃ©todo que inicia processo de disponibilidade.
     */
    bool startBitAvaliable();
    /*!
     * MÃ©todo que envia dados.
     */
    void sendNBits(uint16_t data);
    /*!
     * MÃ©todo que cancela transmissÃ£o de dados.
     */
    void cancelSend();
    /*!
     * MÃ©todo que espera a transferÃªncia de dados ser finalizada.
     */
    void waitTransfer();

 private:
    /*!
     * EndereÃ§o do registrador PortPCRtx no mapa de memÃ³ria.
     */
    volatile uint32_t * addressPortPCRtx;
    /*!
     * EndereÃ§o do registrador PortPCRrx no mapa de memÃ³ria.
     */
    volatile uint32_t * addressPortPCRrx;
    /*!
     * EndereÃ§o do registrador UARTxC1 no mapa de memÃ³ria.
     */
    volatile uint8_t * addressUARTxC1;
    /*!
     * EndereÃ§o do registrador UARTxC2 no mapa de memÃ³ria.
     */
    volatile uint8_t * addressUARTxC2;
    /*!
     * EndereÃ§o do registrador UARTxC3 no mapa de memÃ³ria.
     */
    volatile uint8_t * addressUARTxC3;
    /*!
     * EndereÃ§o do registrador UARTxC4 no mapa de memÃ³ria.
     */
    volatile uint8_t * addressUARTxC4;
    /*!
     * EndereÃ§o do registrador UARTx_BDH no mapa de memÃ³ria.
     */
    volatile uint8_t * addressUARTx_BDH;
    /*!
     * EndereÃ§o do registrador UARTx_BDL no mapa de memÃ³ria.
     */
    volatile uint8_t * addressUARTx_BDL;
    /*!
     * EndereÃ§o do registrador UARTxS1 no mapa de memÃ³ria.
     */
    volatile uint8_t * addressUARTxS1;
    /*!
     * EndereÃ§o do registrador UARTxS2 no mapa de memÃ³ria.
     */
    volatile uint8_t * addressUARTxS2;
    /*!
     * EndereÃ§o do registrador UART_D no mapa de memÃ³ria.
     */
    volatile uint8_t * addressUART_D;
    /*!
     * ExceÃ§Ãµes geradas.
     */
    uart_Exception_t exception;
    /*!
     * Tamanho do dado transmitido.
     */
    uart_LengthData_t lengthData;
};

#endif /* INCLUDES_MKL_UARTPORT_H_ */