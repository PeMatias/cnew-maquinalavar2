/*!
 * @copyright   © 2017 Universidade Federal do Amazonas.
 *
 * @brief       Interface da API em C++ da classe mãe I2C.
 *
 * @file        mkl_I2C.h
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

#ifndef C__USERS_MSCAS_DESKTOP_CPPLINT_MASTER_MKL_I2C_H_
#define C__USERS_MSCAS_DESKTOP_CPPLINT_MASTER_MKL_I2C_H_

#include <MKL25Z4.h>
#include <stdint.h>

/*!
 * Namespaces associados à mascara do GPIO, alternativa do mux PCR e I2C.
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
 * Namespace associado a configuração da velocidade do I2C.
 */
typedef enum {
    i2c_standard   = 0x1F,
    i2c_fast        = 0x05,
    i2c_highSpeed  = 0x00
} i2c_baudRate_t;

/*!
 * Namespace associado aos erros de exceção.
 */
typedef enum {
    i2c_erroNone = 0,
    i2c_erroNoAck = 0x01,
    i2c_erroArbitrationLost = 0x02,
    i2c_erroBusBusy = 0x03,
} i2c_Exception_t;

/*!
 * Namespace associado as prioridades de interrupção.
 */
typedef enum {
    i2c_priority0 = 0,
    i2c_priority1 = 1,
    i2c_priority2 = 2,
    i2c_priority3 = 3,
} i2c_Priority_t;


/*!
 * Namespace associado ao periférico I2C e seus pinos correspondentes.
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
 *  @brief    Classe de implementação do periférico I2C para a placa KL25Z128.
 *
 *  @details  Esta classe é usada para leitura ou escrita de dados de 8 bits
 *            e usa o periférico I2C.
 *
 */

class mkl_I2C {
 protected:
	/*!
	 * Endereço do registrador Port PCR no mapa de memória.
	 */
    volatile uint32_t *addressPortxPCRn;

	/*!
	 * Endereços dos registradores associados ao periférico IC2.
	 */
    volatile uint8_t *addressI2CxF;
    volatile uint8_t *addressI2CxC1;
    volatile uint8_t *addressI2CxS;
    volatile uint8_t *addressI2CxD;
    volatile uint8_t *addressI2Cx_SMB;

	/*!
     * Métodos de habilitação de clock do periférico e da porta GPIO.
     */
    void enablePeripheralClock(uint32_t I2CNumber);
    void enableGPIOClock(uint32_t GPIONumber);

    /*!
     * Método para habilitar o periférico.
     */
    void enableI2C();

    /*!
     * Método para desabilitar o periférico.
     */
    void disableI2C();

    /*!
     * Método para limpar flag de interrupção do I2C.
     */
    void clearInterruptFlag();

	/*!
	 * Métodos privados de inicialização do periférico.
	 */
    void bindPeripheral(uint32_t I2CNumber);
    void bindPin(uint32_t pinNumber, uint32_t GPIONumber);

    /*!
     * Método de seleção do mux do pino.
     */
    void selectMuxAlternative(uint32_t muxAlt);

    /*!
     * Método de ajuste de parâmetros para endereço base.
     */
    void setI2CParameters(i2c_Pin_t pin, uint32_t &pinNumber,
                          uint32_t &GPIONumber, uint32_t &I2CNumber,
                          uint32_t &muxAltMask);
};

#endif  //  C__USERS_MSCAS_DESKTOP_CPPLINT_MASTER_MKL_I2C_H_


