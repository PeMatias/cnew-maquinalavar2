/*!
 * @copyright   � 2017 UFAM - Universidade Federal do Amazonas.
 *
 * @brief       Interface de programa��o de aplica��es em C++ para o Periodic interrupt Timer (MKL25Z).
 *
 * @file        dsf_PIT_ocp.cpp
 * @version     1.0
 * @date        6 Julho 2017
 *
 * @section     HARDWARES & SOFTWARES
 *              +board        FRDM-KL25Z da NXP.
 *              +processor    MKL25Z128VLK4 - ARM Cortex-M0+.
 *              +peripheral   PIT - Periodic Interrupt Timer.
 *              +compiler     Kinetis� Design Studio IDE.
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

#include "mkl_PIT.h"
#include <MKL25Z4.h>
#include <stdint.h>

/*!
 *   @fn         bindChannel
 *
 *   @brief      Inicializa os ponteiros por canal.
 *
 *   Este m�todo associa ao objeto de software os endere�os de mem�ria dos
 *   registradores alocados para o canal indicado.
 *
 *   @param[in]  channel - canal dsf_Ch0_PIT ou canal dsf_Ch1_PIT usado.
 *   @remarks    Siglas e p�ginas do Manual de Refer�ncia KL25:
 *               - PIT_LDVALn: Timer Load Value Register. P�g. 578.
 *               - PIT_CVALn:  Current Timer Value Register. P�g.578.
 *               - PIT_TCTRLn: Timer Control Register. P�g. 579.
 *               - PIT_TFLGn:  Timer Flag Register. P�g. 580.
 *               - PIT_MCR:    PIT Module Control Register. P�g. 575.
 */
void mkl_PIT::bindChannel(PIT_ChPIT channel) {
  /*!
   * C�lculo do endere�o absoluto do LDVALn para o PIT.
   * Address: LDVAL0 = 0x40037100 e LDVAL1 = 0x40037110
   * addrLDVALn= 0x40037100(base)+ 0x10*channel, onde channel= 0 ou 1
   */
  addrLDVALn = (volatile unsigned int *)(0x40037100 + 0x10*channel);

  /*!
   * C�lculo do endere�o absoluto do LCVALn para o PIT.
   * Address: LCVAL0 = 0x40037104 LCVAL1 = 0x40037114.
   * addrCVALn = 0x40037104(base) + 0x10*channel,onde channel=0 ou 1
   */
  addrCVALn = (volatile unsigned int *)(0x40037104 + 0x10*channel);

  /*!
   * C�lculo do endere�o absoluto do TCTRLn para o PIT.
   * Address: TCTRL0 = 0x40037108 e TCTRL1 = 0x40037118.
   * addrTCTRLn = 0x40037108(base) + 0x10*channel,onde channel= 0 ou 1
   */
  addrTCTRLn = (volatile unsigned int *)(0x40037108 + 0x10*channel);

  /*!
   * C�lculo do endere�o absoluto do TFLGn para o PIT.
   * Address: TFLG0 = 0x4003710C e TFLG1 = 0x4003711C.
   * addrTFLGn = 0x4003710C(base) + 0x10*channel,onde channel= 0 ou 1
   */
  addrTFLGn = (volatile unsigned int *)(0x4003710C + 0x10*channel);
}


/*!
 *   @fn         enablePeripheralClock
 *
 *   @brief      Habilita o clock do M�dulo.
 *
 *   Este m�todo habilita a opera��o do m�dulo, habilitando o clock
 *   de opera��o do perif�rico.
 *
 *   @remarks  Siglas e p�ginas do Manual de Refer�ncia KL25:
 *	        - SIM_SCGC6: System Clock Gating Control Register 6. P�g. 207.
 */
void mkl_PIT::enablePeripheralClock() {
  SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;
}


/*!
 *   @fn         enablePeripheralModule
 *
 *   @brief      Habilita o clock dos Timers.
 *
 *   Este m�todo habilita a opera��o do barramento de clock, habilitando o clock
 *   de opera��o dos Timers dos 2 canais/
 *
 *   @remarks  Siglas e p�ginas do Manual de Refer�ncia KL25:
 *             - PIT_MCR: PIT Module Control Register. P�g. 575.
 */
void mkl_PIT::enablePeripheralModule() {
  /*!
   *  Ajusta '0' no MDIS do MCR.
   */
  PIT_MCR &= ~PIT_MCR_MDIS_MASK;
}


/*!
 *   @fn       disablePeripheralModule
 *
 *   @brief    Desabilita a opera��o dos Timers
 *
 *   Este m�todo desabilita a opera��o dos Timers, desligando o clock de
 *   opera��o dos 2 canais dos timers.
 *
 *   @warning  Desabilita todos os Timers para ambos os canais.
 *
 *   @remarks  Siglas e p�ginas do Manual de Refer�ncia KL25:
 *            - PIT_MCR: PIT Module Control Register. P�g. 575.
 */
void mkl_PIT::disablePeripheralModule() {
  /*!
   *  Ajusta '1' no MDIS do MCR.
   */
  PIT_MCR |= PIT_MCR_MDIS_MASK;
}


/*!
 *   @fn         setPeriod
 *
 *   @brief      seta o valor de fundo de escala de um canal.
 *
 *   Este m�todo define o valor de in�cio de um canal, onde o timer
 *   ir� decrementar o valor corrente at� alcan�ar 0.
 *
 *   @param[in]  time - n�mero de ciclos de clock convertido em hexadecimal,
 *               de acordo com o periodo desejado.
 *               N�mero de ciclos de clock (LDVALn) = Per�odo(desejado)*20MHz - 1.
 *
 *   @remarks    Sigla e p�gina do Manual de Refer�ncia KL25:
 *               - LDVALn: Timer Load Value Register. P�g. 578..
 */
void mkl_PIT::setPeriod(uint32_t time) {
  /*!
   *  Ajusta LDVALn com "time".
   */
  *addrLDVALn = time;
}


/*!
 *   @fn       readCounter
 *
 *   @brief    L� a contagem de um canal
 *
 *   Este m�todo retorna o valor corrente da contagem de um canal do timer.
 *
 *   @return   O valor do registrador que possui o valor corrente (CVALn) do canal.
 *
 *   @remarks  Siglas e p�ginas do Manual de Refer�ncia KL25:
 *             - PIT_CVALn: Current Timer Value Register. P�g.578.
 */
uint32_t mkl_PIT::readCounter() {
  /*!
   *  L� e retorna o valor de CVALn
   */
  return *addrCVALn;
}
/*!
 *   @fn         enableTimer
 *
 *   @brief      Habilita a opera��o de um canal.
 *
 *   Este m�todo habilita a opera��o de contagem decrescente de um canal do timer.
 *
 *   @remarks  Siglas e p�ginas do Manual de Refer�ncia KL25:
 *	       - PIT_TCTRLn: Timer Control Register. P�g. 579.
 */
void mkl_PIT::enableTimer() {
  /*!
   *  Ajusta '1' no campo TEN.
   */
  *addrTCTRLn |= PIT_TCTRL_TEN_MASK;
}


/*!
 *   @fn         disableTimer
 *
 *   @brief      desabilita a opera��o de um canal.
 *
 *   Este m�todo desabilita a opera��o de contagem de um canal do Timer.
 *
 *   @remarks  Siglas e p�ginas do Manual de Refer�ncia KL25:
 *	       - PIT_TCTRLn: Timer Control Register. P�g. 579.
 */
void mkl_PIT::disableTimer() {
  /*!
   *  Ajusta '0' no campo TEN.
   */
  *addrTCTRLn &= ~PIT_TCTRL_TEN_MASK;
}


/*!
 *   @fn         resetCounter
 *
 *   @brief      reseta o valor do contador de um canal do Timer.
 *
 *   Este m�todo reseta o valor do contador de um canal. Caso se queira carregar
 *   um novo valor de in�cio em LDVALn, � necess�rio que se desabilite e habilite os Timers.
 *
 *   @remarks  Siglas e p�ginas do Manual de Refer�ncia KL25:
 *             - Timers. P�g. 581.
 */
void mkl_PIT::resetCounter() {
  disableTimer();
  enableTimer();
}

/*!
 *   @fn       waitInterruptFlag
 *
 *   @brief    Aguarda a gera��o de uma interrup��o de um canal.
 *
 *   Este m�todo espera a ocorr�ncia de uma interrup��o de um canal, monitorando a
 *   a flag de interrup��o at� que esta se torne verdadeira.
 *
 *   @remarks  Siglas e p�ginas do Manual de Refer�ncia KL25:
 *             - PIT_TFLGn: Timer Flag Register. P�g.580.
 */

void mkl_PIT::waitInterruptFlag() {
  while ( !isInterruptFlagSet() ) { }
}

/*!
 *   @fn       clearInterruptFlag
 *
 *   @brief    limpa a flag de interrup��o de um canal.
 *
 *   Este m�todo limpa o registrador de flag de interrup��o de um canal,
 *   o que deve ser feito antes de configurar interrup��es.
 *
 *
 *   @remarks  Siglas e p�ginas do Manual de Refer�ncia KL25:
 *             - PIT_TFLGn: Timer Flag Register. P�g.580.
 */
void mkl_PIT::clearInterruptFlag() {
  *addrTFLGn |= PIT_TFLG_TIF_MASK;
}


/*!
 *   @fn       delay
 *
 *   @brief    Espera estourar a temporiza��o de um canal.
 *
 *   Este m�todo espera o registrador de flag de interrup��o sinalizar que
 *   expirou a temporiza��o programada de um canal, sendo a gera��o de
 *   interrup��es desabilitadas.
 *
 *   @param[in]  time - n�mero de ciclos de clock convertido em hexadecimal,
 *               de acordo com o per�odo desejado.
 *               N�mero de ciclos de clock (LDVALn) = Per�do(desejado)*20MHz - 1.
 */

/*!
 *   @fn       isInterruptFlagSet
 *
 *   @brief    retorna verdadeiro quando ocorre uma interrup��o de um canal.
 *
 *   Este m�todo retorna verdadeiro caso seja gerado uma interrup��o por um canal,
 *   onde a flag de interrup��o � setada quando ocorre uma interrup��o.
 *
 *   @return   True, caso haja uma interrup��o.
 *             False, caso ainda n�o tenha ocorrido uma interrup��o.
 *
 *   @remarks  Siglas e p�ginas do Manual de Refer�ncia KL25:
 *             - PIT_TFLGn: Timer Flag Register. P�g.580.
 */

bool mkl_PIT::isInterruptFlagSet(){
	if ( *addrTFLGn && PIT_TFLG_TIF_MASK ) {
	    return true;
	  }
	    return false;
}
