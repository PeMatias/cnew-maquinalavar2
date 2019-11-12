/*!
 * @copyright   � 2017 Universidade Federal do Amazonas.
 *
 * @brief       Interface da API em C++ da classe m�e I2C.
 *
 * @file        mkl_I2C.h
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

#ifndef C__USERS_MSCAS_DESKTOP_CPPLINT_MASTER_MKL_I2C_H_
#define C__USERS_MSCAS_DESKTOP_CPPLINT_MASTER_MKL_I2C_H_

#include <MKL25Z4.h>
#include <stdint.h>

/*!
 * Namespaces associados � mascara do GPIO, alternativa do mux PCR e I2C.
 */
typedef enum {
    i2c_GPIOA = 0,
    i2c_GPIOB = 1 << 8,
    i2c_GPIOC = 2 << 8,
    i2c_GPIOD = 3 << 8,
    i2c_GPIOE = 4 << 8
}i2c_GPIOMask;

typedef enum {
    i2c_muxAlt1 = 1 << 16,
    i2c_muxAlt2 = 2 << 16,
    i2c_muxAlt4 = 4 << 16,
    i2c_muxAlt6 = 6 << 16
}i2c_muxAltMask;

typedef enum {
    mkl_I2C0 = 0 << 24,
    mkl_I2C1 = 1 << 24
}mkl_I2C_t;

/*!
 * Namespace associado a configura��o da velocidade do I2C.
 */
typedef enum {
    i2c_standard   = 0x1F,
    i2c_fast        = 0x05,
    i2c_highSpeed  = 0x00
} i2c_baudRate_t;

/*!
 * Namespace associado aos erros de exce��o.
 */
typedef enum {
    i2c_erroNone = 0,
    i2c_erroNoAck = 0x01,
    i2c_erroArbitrationLost = 0x02,
    i2c_erroBusBusy = 0x03,
} i2c_Exception_t;

/*!
 * Namespace associado as prioridades de interrup��o.
 */
typedef enum {
    i2c_priority0 = 0,
    i2c_priority1 = 1,
    i2c_priority2 = 2,
    i2c_priority3 = 3,
} i2c_Priority_t;


/*!
 * Namespace associado ao perif�rico I2C e seus pinos correspondentes.
 */
typedef enum {
    i2c_PTC1 = 1|i2c_GPIOC|i2c_muxAlt2|mkl_I2C1,    //!< SDA
    i2c_PTC2 = 2|i2c_GPIOC|i2c_muxAlt2|mkl_I2C1,    //!< SCL
    i2c_PTC8 = 8|i2c_GPIOC|i2c_muxAlt2|mkl_I2C0,    //!< SDA
    i2c_PTC9 = 9|i2c_GPIOC|i2c_muxAlt2|mkl_I2C0,    //!< SCL
    i2c_PTC10 = 10|i2c_GPIOC|i2c_muxAlt2|mkl_I2C1,  //!< SDA
    i2c_PTC11 = 11|i2c_GPIOC|i2c_muxAlt2|mkl_I2C1,  //!< SCL
    i2c_PTE0 = 0|i2c_GPIOE|i2c_muxAlt6|mkl_I2C1,    //!< SDA
    i2c_PTE1 = 1|i2c_GPIOE|i2c_muxAlt6|mkl_I2C1,    //!< SCL
} i2c_Pin_t;


/*!
 *  @class    mkl_I2C_H
 *
 *  @brief    Classe de implementa��o do perif�rico I2C para a placa KL25Z128.
 *
 *  @details  Esta classe � usada para leitura ou escrita de dados de 8 bits
 *            e usa o perif�rico I2C.
 *
 */

class mkl_I2C {
 protected:
	/*!
	 * Endere�o do registrador Port PCR no mapa de mem�ria.
	 */
    volatile uint32_t *addressPortxPCRn;

	/*!
	 * Endere�os dos registradores associados ao perif�rico IC2.
	 */
    volatile uint8_t *addressI2CxF;
    volatile uint8_t *addressI2CxC1;
    volatile uint8_t *addressI2CxS;
    volatile uint8_t *addressI2CxD;
    volatile uint8_t *addressI2Cx_SMB;

	/*!
     * M�todos de habilita��o de clock do perif�rico e da porta GPIO.
     */
    void enablePeripheralClock(uint32_t I2CNumber);
    void enableGPIOClock(uint32_t GPIONumber);

    /*!
     * M�todo para habilitar o perif�rico.
     */
    void enableI2C();

    /*!
     * M�todo para desabilitar o perif�rico.
     */
    void disableI2C();

    /*!
     * M�todo para limpar flag de interrup��o do I2C.
     */
    void clearInterruptFlag();

	/*!
	 * M�todos privados de inicializa��o do perif�rico.
	 */
    void bindPeripheral(uint32_t I2CNumber);
    void bindPin(uint32_t pinNumber, uint32_t GPIONumber);

    /*!
     * M�todo de sele��o do mux do pino.
     */
    void selectMuxAlternative(uint32_t muxAlt);

    /*!
     * M�todo de ajuste de par�metros para endere�o base.
     */
    void setI2CParameters(i2c_Pin_t pin, uint32_t &pinNumber,
                          uint32_t &GPIONumber, uint32_t &I2CNumber,
                          uint32_t &muxAltMask);
};

#endif  //  C__USERS_MSCAS_DESKTOP_CPPLINT_MASTER_MKL_I2C_H_


