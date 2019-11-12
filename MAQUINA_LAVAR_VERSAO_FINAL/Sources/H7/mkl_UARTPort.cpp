/*!
 * @copyright   Â© 2017 Felipe R. Monteiro <rms.felipe@gmail.com>
 *         Francisco FÃ©lix <frfelix7@gmail.com>
 *
 * @brief       ImplementaÃ§Ã£o dos mÃ©todos da classe mkl_UARTPort.
 *
 * @file        mkl_UARTPort.cpp
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

#include "mkl_UARTPort.h"

mkl_UARTPort::mkl_UARTPort() {
    //! TODO(Felipe): implementar.
}

/*!
 *  @fn  mkl_UARTPort
 *
 *  @brief  Configura o perifÃ©rico.
 *
 *  @param[in]  pinTx - pino de transferÃªncia.
 *     pinRx - pino de recepÃ§Ã£o.
 *
 *  @remarks  Siglas e pÃ¡ginas do Manual de ReferÃªncia K25F:
 *            - UARTx: Universal Asynchronous Receiver/Transmitter.
 *            - SimSCGC: System Device Gating Control Register. PÃ¡g. 307 - 319.
 *            - PortPCRtx: Pin Control Register n Transmitter. PÃ¡g. 282.
 *            - PortPCRrx: Pin Control Register n Receiver. PÃ¡g. 282.
 *            - UARTx_BDH: UART Baud Rate Register High. PÃ¡g. 1541.
 *            - UARTx_BDL: UART Baud Rate Register Low. PÃ¡g. 1542.
 *            - UARTxS1: UART Status Register 1. PÃ¡g. 1546.
 *            - UARTxS2: UART Status Register 2. PÃ¡g. 1549.
 *            - UARTxC1: UART Control Register 1. PÃ¡g. 1543.
 *            - UARTxC2: UART Control Register 2. PÃ¡g. 1544.
 *            - UARTxC3: UART Control Register 3. PÃ¡g. 1551.
 *            - UARTxC4: UART Control Register 4. PÃ¡g. 1554.
 */
mkl_UARTPort::mkl_UARTPort(uart_PinTx_t pinTx, uart_PinRx_t pinRx) {
    SIM->SOPT2 |= 0x04000000;

    if (pinTx == uart0_PTA2  ||
            pinTx == uart0_PTE20 ||
            pinTx == uart0_PTD7) {  //! UART0
        addressUARTxC1     =     reinterpret_cast<uint8_t *>(0x4006A002);
        addressUARTxC2     =     reinterpret_cast<uint8_t *>(0x4006A003);
        addressUARTxC3     =     reinterpret_cast<uint8_t *>(0x4006A006);
        addressUARTxC4     =     reinterpret_cast<uint8_t *>(0x4006A00A);
        addressUARTx_BDH   =     reinterpret_cast<uint8_t *>(0x4006A000);
        addressUARTx_BDL   =     reinterpret_cast<uint8_t *>(0x4006A001);
        addressUARTxS1     =     reinterpret_cast<uint8_t *>(0x4006A004);
        addressUARTxS2     =     reinterpret_cast<uint8_t *>(0x4006A005);
        addressUART_D      =     reinterpret_cast<uint8_t *>(0x4006A007);

        SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;

        //! ConfiguraÃ§Ã£o do pino TX.
        if (pinTx == uart0_PTA2) {
            addressPortPCRtx = reinterpret_cast<uint32_t *>(0x40049008);
            SIM_SCGC5 |=  SIM_SCGC5_PORTA_MASK;
            *addressPortPCRtx |= PORT_PCR_MUX(2);
        } else if (pinTx == uart0_PTE20) {
            addressPortPCRtx = reinterpret_cast<uint32_t *>(0x4004D050);
            SIM_SCGC5 |=  SIM_SCGC5_PORTE_MASK;
            *addressPortPCRtx |= PORT_PCR_MUX(4);
        } else if (pinTx == uart0_PTD7) {
            addressPortPCRtx = reinterpret_cast<uint32_t *>(0x4004C01C);
            SIM_SCGC5 |=  SIM_SCGC5_PORTD_MASK;
            *addressPortPCRtx |= PORT_PCR_MUX(3);
        }

        //! ConfiguraÃ§Ã£o do pino RX.
        if (pinRx == uart0_PTA1) {
            addressPortPCRrx = reinterpret_cast<uint32_t *>(0x40049004);
            SIM_SCGC5 |=  SIM_SCGC5_PORTA_MASK;
            *addressPortPCRrx |= PORT_PCR_MUX(2);
        } else if (pinRx == uart0_PTE21) {
            addressPortPCRrx = reinterpret_cast<uint32_t *>(0x4004D054);
            SIM_SCGC5 |=  SIM_SCGC5_PORTE_MASK;
            *addressPortPCRrx |= PORT_PCR_MUX(4);
        } else if (pinRx == uart0_PTD6) {
            addressPortPCRrx = reinterpret_cast<uint32_t *>(0x4004C018);
            SIM_SCGC5 |=  SIM_SCGC5_PORTD_MASK;
            *addressPortPCRrx |= PORT_PCR_MUX(3);
        }
    } else if (pinTx == uart1_PTC4 || pinTx == uart1_PTE0) {  //! UART1
        addressUARTxC1     =     reinterpret_cast<uint8_t *>(0x4006B002);
        addressUARTxC2     =     reinterpret_cast<uint8_t *>(0x4006B003);
        addressUARTxC3     =     reinterpret_cast<uint8_t *>(0x4006B006);
        addressUARTxC4     =     reinterpret_cast<uint8_t *>(0x4006B008);
        addressUARTx_BDH   =     reinterpret_cast<uint8_t *>(0x4006B000);
        addressUARTx_BDL   =     reinterpret_cast<uint8_t *>(0x4006B001);
        addressUARTxS1     =     reinterpret_cast<uint8_t *>(0x4006B004);
        addressUARTxS2     =     reinterpret_cast<uint8_t *>(0x4006B005);
        addressUART_D      =     reinterpret_cast<uint8_t *>(0x4006B007);

        SIM_SCGC4 |= SIM_SCGC4_UART1_MASK;

        //! ConfiguraÃ§Ã£o do pino TX.
        if (pinTx == uart1_PTC4) {
            addressPortPCRtx = reinterpret_cast<uint32_t *>(0x4004B010);
            SIM_SCGC5 |=  SIM_SCGC5_PORTC_MASK;
            *addressPortPCRtx |= PORT_PCR_MUX(3);
        } else if (pinTx == uart1_PTE0) {
            addressPortPCRtx = reinterpret_cast<uint32_t *>(0x4004D000);
            SIM_SCGC5 |=  SIM_SCGC5_PORTE_MASK;
            *addressPortPCRtx |= PORT_PCR_MUX(3);
        }

        //! ConfiguraÃ§Ã£o do pino RX.
        if (pinRx == uart1_PTC3) {
            addressPortPCRrx = reinterpret_cast<uint32_t *>(0x4004B00C);
            SIM_SCGC5 |=  SIM_SCGC5_PORTC_MASK;
            *addressPortPCRrx |= PORT_PCR_MUX(3);
        } else if (pinRx == uart1_PTE1) {
            addressPortPCRrx = reinterpret_cast<uint32_t *>(0x4004D004);
            SIM_SCGC5 |=  SIM_SCGC5_PORTE_MASK;
            *addressPortPCRrx |= PORT_PCR_MUX(2);
        }
    } else if (pinTx == uart2_PTD3 ||
               pinTx == uart2_PTD5 ||
               pinTx == uart2_PTE22) {  //! UART2
        addressUARTxC1     =     reinterpret_cast<uint8_t *>(0x4006C002);
        addressUARTxC2     =     reinterpret_cast<uint8_t *>(0x4006C003);
        addressUARTxC3     =     reinterpret_cast<uint8_t *>(0x4006C006);
        addressUARTxC4     =     reinterpret_cast<uint8_t *>(0x4006C008);
        addressUARTx_BDH   =     reinterpret_cast<uint8_t *>(0x4006C000);
        addressUARTx_BDL   =     reinterpret_cast<uint8_t *>(0x4006C001);
        addressUARTxS1     =     reinterpret_cast<uint8_t *>(0x4006C004);
        addressUARTxS2     =     reinterpret_cast<uint8_t *>(0x4006C005);
        addressUART_D      =     reinterpret_cast<uint8_t *>(0x4006C007);

        SIM_SCGC4 |= SIM_SCGC4_UART2_MASK;

        //! ConfiguraÃ§Ã£o do pino TX.
        if (pinTx == uart2_PTD3) {
            addressPortPCRtx = reinterpret_cast<uint32_t *>(0x4004C00C);
            SIM_SCGC5 |=  SIM_SCGC5_PORTD_MASK;
            *addressPortPCRtx |= PORT_PCR_MUX(3);
        } else if (pinTx == uart2_PTD5) {
            addressPortPCRtx = reinterpret_cast<uint32_t *>(0x4004C014);
            SIM_SCGC5 |=  SIM_SCGC5_PORTD_MASK;
            *addressPortPCRtx |= PORT_PCR_MUX(3);
        } else if (pinTx == uart2_PTE22) {
            addressPortPCRtx = reinterpret_cast<uint32_t *>(0x4004D058);
            SIM_SCGC5 |=  SIM_SCGC5_PORTE_MASK;
            *addressPortPCRtx |= PORT_PCR_MUX(4);
        }

        // ConfiguraÃ§Ã£o do pino RX.
        if (pinRx == uart2_PTD2) {
            addressPortPCRrx = reinterpret_cast<uint32_t *>(0x4004C008);
            SIM_SCGC5 |=  SIM_SCGC5_PORTD_MASK;
            *addressPortPCRrx |= PORT_PCR_MUX(3);
        } else if (pinRx == uart2_PTD4) {
            addressPortPCRrx = reinterpret_cast<uint32_t *>(0x4004C010);
            SIM_SCGC5 |=  SIM_SCGC5_PORTD_MASK;
            *addressPortPCRrx |= PORT_PCR_MUX(3);
        } else if (pinRx == uart2_PTE23) {
            addressPortPCRrx = reinterpret_cast<uint32_t *>(0x4004D05C);
            SIM_SCGC5 |=  SIM_SCGC5_PORTE_MASK;
            *addressPortPCRrx |= PORT_PCR_MUX(4);
        }
    }
    *addressUARTxC1 = 0;
}

/*!
 *  @fn  setFrame
 *
 *  @brief  Determinar o tamanho do frame.
 *
 *  @param[in]  lengthData   - tamanho do dado.
 *     uart_Parity_t  - valor de paridade.
 *      uart_StopBit_t  - valor para parada.
 *      uart_FistBit_t  - valor do primeiro bit.
 */
void mkl_UARTPort::setFrame(uart_LengthData_t lengthData,
        uart_Parity_t parity,
        uart_StopBit_t stop,
        uart_FistBit_t fistBit) {
    this->lengthData = lengthData;

    /*!
     * Unable RX and TX for register 2
     */
    *addressUARTxC2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);

    /*!
     * Stop configuration 1-bit
     */
    if (stop == mkl_One) {
        *addressUARTx_BDH &= ~UART_BDH_SBNS_MASK;
    } else {  //! 2-bit
        *addressUARTx_BDH |= UART_BDH_SBNS_MASK;
    }
    if (parity == mkl_None) {  //! parity off
        *addressUARTxC1 &= ~UART_C1_PE_MASK;
        if (lengthData == mkl_8bit) {  //! 8-bit
            *addressUARTxC1 &= ~UART_C1_M_MASK;
        } else if (lengthData == mkl_9bit) {  //! 9-bit
            *addressUARTxC1 |= UART_C1_M_MASK;
        } else {
            //! error
        }
    } else {  //! parity on
        *addressUARTxC1 |= UART_C1_PE_MASK;
        if (lengthData == mkl_7bit) {  //! 7-bit
            *addressUARTxC1 &= ~UART_C1_M_MASK;
            *addressUARTxC4 &= ~UART0_C4_M10_MASK;
        } else if (lengthData == mkl_8bit) {  //! 8-bit
            *addressUARTxC1 |= UART_C1_M_MASK;
            *addressUARTxC4 &= ~UART0_C4_M10_MASK;
        } else {  //! 9-bit
            *addressUARTxC1 |= UART_C1_M_MASK;
            *addressUARTxC4 |= UART0_C4_M10_MASK;
        }
        /*!
         * ConfiguraÃ§Ã£o do tipo de paridade
         */
        if (parity == mkl_Even) {
            *addressUARTxC1 &= ~UART_C1_PT_MASK;
        } else {  //! dsf_Odd
            *addressUARTxC1 |= UART_C1_PT_MASK;
        }
    }
    /*!
     * ConfiguraÃ§Ã£o do bit mais significativo
     */
    if (fistBit == mkl_LSB) {
        //! *addressUARTxS2 &= ~UART_S2_MSBF_MASK;
    } else {
        //! *addressUARTxS2 |= UART_S2_MSBF_MASK;
    }
    *addressUARTxC2 |= (UART_C2_TE_MASK |UART_C2_RE_MASK);
}

/*!
 *  @fn  setBaudRate
 *
 *  @brief  MÃ©todo que determina a taxa de transmissÃ£o.
 *
 *  @param[in] rate - taxa de transmissÃ£o.
 */
void mkl_UARTPort::setBaudRate(uint16_t rate) {
    uint16_t baudRateModuloDivisor;

    /*!
     * Habilitar RX e TX para o registrador 2
     */
    *addressUARTxC2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);

    /*!
     * Calcular as configuraÃ§Ãµes da taxa de transmissÃ£o
     */
    baudRateModuloDivisor = (uint16_t)((21000*1000)/(rate * 16));
    *addressUARTx_BDH = (*addressUARTx_BDH & ~(UART_BDH_SBR(0x1F))) |
                        (((baudRateModuloDivisor & 0x1F00) >> 8));
    *addressUARTx_BDL = (uint8_t)(baudRateModuloDivisor & UART_BDL_SBR_MASK);

    /*!
     * Habilitar recepÃ§Ã£o e transmissÃ£o
     */
    *addressUARTxC2 |= (UART_C2_TE_MASK |UART_C2_RE_MASK);
}

/*!
 *  @fn  waitTransfer
 *
 *  @brief  Espera transferÃªncia de dados.
 *
 *  @remarks  Siglas e pÃ¡ginas do Manual de ReferÃªncia K25F:
 *            - UARTx: Universal Asynchronous Receiver/Transmitter.
 *            - UARTxS1: UART Status Register 1. PÃ¡g. 1546.
 *            - UARTxC2: UART Control Register 2. PÃ¡g. 1544.
 */
void mkl_UARTPort::waitTransfer() {
    while (!(*addressUARTxS1 & UART_S1_TDRE_MASK)) {}
}

/*!
 *  @fn  sendNBits
 *
 *  @brief  Envia um dado de 16 bits.
 *
 *  @param[in] data - mensagem de dados.
 *
 *  @remarks  Siglas e pÃ¡ginas do Manual de ReferÃªncia K25F:
 *            - UARTx: Universal Asynchronous Receiver/Transmitter.
 *            - UARTxS1: UART Status Register 1. PÃ¡g. 1546.
 *            - UARTxC3: UART Control Register 3. PÃ¡g. 1551.
 *            - UART3_D: UART 3 Data Register 3. PÃ¡g. 1552.
 */
void mkl_UARTPort::sendNBits(uint16_t data) {
    bool dataM = 0;
    uint8_t dataL = data & 0xFF;

    if (*addressUARTxS1 & UART_S1_TDRE_MASK) {
        if (lengthData == mkl_9bit) {
            dataM = static_cast<bool>(data & (1<<8));
            if (dataM == true) {
                *addressUARTxC3|= UART_C3_T8_MASK;
            } else {
                *addressUARTxC3 &= ~UART_C3_T8_MASK;
            }
        }
        *addressUART_D = dataL;
    }
}

/*!
 *  @fn  exceptionOccurred
 *
 *  @brief  MÃ©todo que detecta uma exceÃ§Ã£o durante o envio/recebimento de dados.
 *
 *  @return exceÃ§Ã£o.
 */
uart_Exception_t mkl_UARTPort::exceptionOccurred() {
    return this->exception;
}

/*!
 *  @fn  clearPeripheral
 *
 *  @brief  Limpa informaÃ§Ãµes residuais da UART.
 *
 *  @remarks  Siglas e pÃ¡ginas do Manual de ReferÃªncia K25F:
 *            - UARTx: Universal Asynchronous Receiver/Transmitter.
 *            - UARTxC2: UART Control Register 2. PÃ¡g. 1544.
 */
void mkl_UARTPort::clearPeripheral() {
    /*!
     * Desabilita RX e TX para registrador 2.
     */
    *addressUARTxC2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);
    this->exception = uart_Exception_t::mkl_Ok;
    this->lengthData = uart_LengthData_t::mkl_8bit;
}

/*!
 *  @fn  receiveNBits
 *
 *  @brief  Recebe dados para UART.
 *
 *  @return mensagem de dados de 8 bits.
 *
 *  @remarks  Siglas e pÃ¡ginas do Manual de ReferÃªncia K25F:
 *            - UARTx: Universal Asynchronous Receiver/Transmitter.
 *            - UARTxC3: UART Control Register 3. PÃ¡g. 1551.
 *            - UART3_D: UART 3 Data Register 3. PÃ¡g. 1552.
 */
uint8_t mkl_UARTPort::receiveNBits() {
    /*!
     * Guarda a informaÃ§Ã£o do dado.
     */
    uint16_t data;

    /*!
     * Verifica a permissÃ£o para enviar o dado.
     */
    bool dataM;

    /*!
     * Guarda o tamannho do dado a ser enviado.
     */
    uint8_t dataL;

    /*!
     * Verifica o tamanho do dado para envio e entÃ£o habilita a recepÃ§Ã£o na porta
     */
    if (*addressUARTxS1& UART_S1_RDRF_MASK) {
        if (this->lengthData == mkl_9bit) {
            dataM = static_cast<bool>(*addressUARTxC3 & UART_C3_R8_MASK);
            data = *addressUART_D;
            data |= (dataM << 8);
        } else {
            data = *addressUART_D;
        }
    }
    return data;
}

/*!
 *  @fn  waitArrived
 *
 *  @brief  MÃ©todo que aguarda chegada de dados.
 *
 *  @return mkl_Ok - Tipo de exceÃ§Ã£o.
 *  @return mkl_OverWriteError - Tipo de exceÃ§Ã£o.
 *  @return mkl_ParityError - Tipo de exceÃ§Ã£o.
 *  @return mkl_TimeOutError - Tipo de exceÃ§Ã£o.
 *  @return mkl_FramingError - Tipo de exceÃ§Ã£o.
 *  @return mkl_NoiseError - Tipo de exceÃ§Ã£o.
 *  @return mkl_OverrunError - Tipo de exceÃ§Ã£o.
 *
 *  @remarks  Siglas e pÃ¡ginas do Manual de ReferÃªncia K25F:
 *            - UARTx: Universal Asynchronous Receiver/Transmitter.
 *            - UARTxS1: UART Status Register 1. PÃ¡g. 1546.
 */
uart_Exception_t mkl_UARTPort::waitArrived() {
    /*!
     * Habilita porta de TX da UART.
     */
    *addressUARTxC2 &= ~UART_C2_SBK_MASK;

    /*!
     * Aguarda em loop atÃ© a mensagem ser transmitida.
     */
    while (!(*addressUARTxS1 & UART_S1_RDRF_MASK)) {}

    return this->exception;
}

/*!
 *  @fn  startBitAvaliable
 *
 *  @brief  Verifica a disponibilidade do bit de inicializaÃ§Ã£o.
 *
 *  @return true - boolean value.
 *  @return false - boolean value.
 *
 *  @remarks  Siglas e pÃ¡ginas do Manual de ReferÃªncia K25F:
 *            - UARTx: Universal Asynchronous Receiver/Transmitter.
 *            - UARTxS1: UART Status Register 1. PÃ¡g. 1546.
 */
bool mkl_UARTPort::startBitAvaliable() {
    if (*addressUARTxS1 & UART_S1_RDRF_MASK) {
        return true;
    }
    return false;
}

/*!
 *  @fn  cancelSend
 *
 *  @brief  Cancela envio de dados.
 *
 *  @remarks  Siglas e pÃ¡ginas do Manual de ReferÃªncia K35F:
 *            - UARTx: Universal Asynchronous Receiver/Transmitter.
 *            - UARTxC2: UART Control Register 2. PÃ¡g. 1544.
 */
void mkl_UARTPort::cancelSend() {
    /*!
     * Desbilita porta de TX da UART.
     */
    *addressUARTxC2 |= UART_C2_SBK_MASK;
}