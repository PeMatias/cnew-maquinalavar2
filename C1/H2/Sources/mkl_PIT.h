/*!
 * @copyright   � 2017 UFAM - Universidade Federal do Amazonas.
 *
 * @brief       Interface de programa��o de aplica��es em C++ para  o Periodic interrupt Timer (MKL25Z).
 *
 * @file        dsf_PIT_ocp.h
 * @version     1.0
 * @date        6 Julho 2017
 *
 * @section     HARDWARES & SOFTWARES
 *              +board        FRDM-KL25Z da NXP.
 *              +processor    MKL25Z128VLK4 - ARM Cortex-M0+.
 *              +peripheral   PIT - Periodic Interrupt Timer.
 *              +compiler     Kinetis� Design Studio IDE
 *              +manual       L25P80M48SF0RM, Rev.3, September 2012
 *              +revisions    Vers�o (data): Descri��o breve.
 *                             ++ 1.0 (6 Julho 2017): Vers�o inicial.
 *
 * @section     AUTHORS & DEVELOPERS
 *              +institution  Universidade Federal do Amazonas
 *              +courses      Engenharia da Computa��o / Engenharia El�trica
 *              +teacher      Miguel Grimm <miguelgrimm@gmail.com>
 *              +student      Vers�o inicial:
 *                             ++ Jose Luis da Silva e Silva <joseluis70123@gmail.com>
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

#ifndef C__USERS_JOSEL_DESKTOP_CPPLINT_DSF_PIT_OCP_H_
#define C__USERS_JOSEL_DESKTOP_CPPLINT_DSF_PIT_OCP_H_

#include <stdint.h>
#ifndef mkl_PIT_H
#define mkl_PIT_H

/*!
 *  Defini��o dos canais do PIT.
 */
typedef enum {
  PIT_Ch0 = 0,  //!< Canal 0 do PIT.
  PIT_Ch1 = 1   //!< Canal 1 do PIT.
} PIT_ChPIT;


/*!
 *  @class    dsf_PIT_ocp
 *
 *  @brief    A classe dsf_PIT_ocp representa o perif�rico Periodic Interrupt Timer da MKL25Z.
 *
 *  @details  Esta classe � usada para a gera��o de interrup��es periodicas,
 *            quando entao uma instru��o � executada. Uso do periferico on-chip
 *            Periodic Interrupt Timer.
 *
 *  @section  EXAMPLES USAGE
 *
 *
 *   Uso dos m�todos para o uso do PIT
 *     +fn dsf_PIT_ocp(channel);
 *     +fn enablePeripheralModule();
 *     +fn setPeriod(time);
 *     +fn resetCounter();
 *     +fn enableTimer();
 *     +fn enableInterruptRequests();
 */
class mkl_PIT {
 public:

  /*!
   * M�todos que afetam os dois canais
   */
  void enablePeripheralClock();
  void enablePeripheralModule();
  void disablePeripheralModule();

  /*!
   * M�todos que afetam somente um canal.
   */
  void setPeriod(uint32_t time);

  /*!
   * M�todos que afetam somente o Timer do PIT
   */
  void enableTimer();
  void disableTimer();
  void resetCounter();
  uint32_t readCounter();

  /*!
   * M�todos que afetam somente a flag que sinaliza  interrup��o
   */
  void waitInterruptFlag();
  bool isInterruptFlagSet();
  void clearInterruptFlag();

  void bindChannel(PIT_ChPIT channel);

  /*!
   *  Endere�o no mapa de mem�ria do Timer Load Value Register - canal n.
   */
  volatile unsigned int *addrLDVALn;

  /*!
   *  Endere�o no mapa de mem�ria do Current Timer Value Register - canal n.
   */
  volatile unsigned int  *addrCVALn;

  /*!
   *  Endere�o no mapa de mem�ria do Timer Control Register - canal n.
   */
  volatile unsigned int *addrTCTRLn;

  /*!
   *  Endere�o no mapa de mem�ria do Timer Flag Register - canal n.
   */
  volatile unsigned int *addrTFLGn;
};

#endif
#endif  //! C__USERS_JOSEL_DESKTOP_CPPLINT_DSF_PIT_OCP_H_
