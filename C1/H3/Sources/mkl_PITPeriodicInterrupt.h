/*!
 * @copyright   � 2017 UFAM - Universidade Federal do Amazonas.
 *
 * @brief       Interface de programa��o de aplica��es em C++ para  o Periodic interrupt Timer (MKL25Z).
 *
 * @file        mkl_PITPeriodicInterrupt.h
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
 
#ifndef SOURCES_MKL_PITPERIODICINTERRUPT_H_
#define SOURCES_MKL_PITPERIODICINTERRUPT_H_

#include <stdint.h>
#include <MKL25Z4.h>
#include "mkl_PIT.h"
/*!
 *  @class     mkl_PITInterruptInterrupt
 *
 *  @brief    A classe implementa o modo de opera��o usando Interrup��o,
 *            da classe  mkl_PIT.
 *
 *  @details  Esta classe � derivada da classe m�e "mkl_PIT" e
 *            implementa o uso de interrup��o.
 *
 *
 */
class mkl_PITInterruptInterrupt : public mkl_PIT {
 public:
	/*!
		 * M�todo construtor padrao da classe
		 */
	 mkl_PITInterruptInterrupt(PIT_ChPIT channel);
	 /*!
	 * M�todos que afetam as interrup��es.
	 */
	 void enableInterruptRequests();
	 void disableInterruptRequests();

};
#endif /* SOURCES_MKL_PITPERIODICINTERRUPT_H_ */
