/*!
 * @copyright   Â© 2017 Felipe R. Monteiro <rms.felipe@gmail.com>
 * 					   Francisco FÃ©lix <frfelix7@gmail.com>
 *
 * @brief       DefiniÃ§Ãµes para a comunicaÃ§Ã£o via UART.
 *
 * @file        mkl_UART.h
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

#ifndef INCLUDE_MKL_UART_H_
#define INCLUDE_MKL_UART_H_

#include <cstddef>
#include "MKL25Z4.h"

/*!
 * DefiniÃ§Ã£o de pinos implementados para transferÃªncia
 * */
typedef enum {
    uart0_PTA2 = 0,
    uart1_PTC4 = 1,
    uart2_PTD3 = 2,
    uart0_PTD7 = 3,
    uart1_PTE0 = 4,
    uart2_PTD5 = 5,
    uart0_PTE20 = 6,
    uart2_PTE22 = 7
} uart_PinTx_t;

/*!
 * DefiniÃ§Ã£o de pinos implementados para recepÃ§Ã£o
 * */
typedef enum {
    uart0_PTA1 = 0,
    uart1_PTC3 = 1,
    uart2_PTD2 = 2,
    uart0_PTD6 = 3,
    uart1_PTE1 = 4,
    uart2_PTD4 = 5,
    uart0_PTE21 = 6,
    uart2_PTE23 = 7
} uart_PinRx_t;

/*!
 * DefiniÃ§Ã£o do tamanho da dado
 * */
typedef enum {
    mkl_7bit = 7,
    mkl_8bit = 8,
    mkl_9bit = 9
} uart_LengthData_t;

/*!
 * DefiniÃ§Ã£o dos tipos de paridade
 * */
typedef enum {
    mkl_Odd = 0,
    mkl_Even = 1,
    mkl_None = 2
} uart_Parity_t;

/*!
 * DefiniÃ§Ã£o dos tipos de parada
 * */
typedef enum {
    mkl_One = 1,
    mkl_Two = 2
} uart_StopBit_t;

/*!
 * DefiniÃ§Ã£o do bit mais significativo
 * */
typedef enum {
    mkl_LSB = 0,
    mkl_MSB = 1
} uart_FistBit_t;

/*!
 * DefiniÃ§Ã£o dos canais UART implementados
 * */
typedef enum {
    mkl_UART0 = 0,
    mkl_UART1 = 1,
    mkl_UART2 = 2
} mkl_UART_t;

/*!
 * DefiniÃ§Ã£o dos tipos de exceÃ§Ã£o
 * */
typedef enum {
    mkl_Ok = 0,
    mkl_OverWriteError = 1,
    mkl_ParityError = 2,
    mkl_TimeOutError = 3,
    mkl_FramingError = 4,
    mkl_NoiseError = 5,
    mkl_OverrunError = 6
} uart_Exception_t;

/*!
 * DefiniÃ§Ã£o das prioridades na interrupÃ§Ã£o
 * */
typedef enum {
    uart_Priority0 = 0,
    uart_Priority1 = 1,
    uart_Priority2 = 2,
    uart_Priority3 = 3
} uart_Priority_t;

/*!
 * DefiniÃ§Ã£o dos modos de interrupÃ§Ã£o
 * */
typedef enum {
    uart_Rx = 0,
    uart_Tx = 1,
    uart_TxRx = 2,
    uart_None = 3
} uart_InterruptMode_t;

#endif /* INCLUDE_MKL_UART_H_ */