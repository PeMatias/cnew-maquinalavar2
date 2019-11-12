/*!
 * @copyright   © 2017 UFAM - Universidade Federal do Amazonas.
 *
 * @brief       Implementação da classe "mkl_TPMPulseWidthModulation".
 *
 * @file        mkl_TPMPulseWidthModulation.cpp
 * @version     1.0
 * @date        06 Agosto 2017
 *
 * @section     HARDWARES & SOFTWARES
 *              +board        FRDM-KL25Z da NXP.
 *              +processor    MKL25Z128VLK4 - ARM Cortex-M0+.
 *              +compiler     Kinetis® Design Studio IDE.
 *              +manual       L25P80M48SF0RM, Rev.3, September 2012.
 *              +revisions    Versão (data): Descrição breve.
 *                             ++ 1.0 (06 Agosto 2017): Versão inicial.
 *
 * @section     AUTHORS & DEVELOPERS
 *              +institution  Universidade Federal do Amazonas.
 *              +courses      Engenharia da Computação / Engenharia Elétrica.
 *              +teacher      Miguel Grimm <miguelgrimm@gmail.com>
 *              +student      Versão inicial:
 *                             ++ Hamilton Nascimento <hdan_neto@hotmail.com>
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

#include <stdint.h>
#include <MKL25Z4.h>
#include "mkl_TPMPulseWidthModulation.h"

/*!
 *   @fn         mkl_TPMPulseWidthModulation.
 *
 *   @brief      Construtor padrão da classe mkl_TPMPulseWidthModulation.
 *
 *   Este método é o construtor padrão da classe, que realiza a associação
 *   física do periférico ao objeto de software, inicializa o periférico e os
 *   pinos associados.
 *
 *   @param[in]  pin - pino de saída do sinal PWM gerado.
 *
 */
mkl_TPMPulseWidthModulation::mkl_TPMPulseWidthModulation(tpm_Pin pin) {
  uint8_t muxAltMask;
  uint8_t pinNumber;
  uint8_t GPIONumber;
  uint8_t chnNumber;
  uint8_t TPMNumber;
  uint8_t *baseAddress;

  setTPMParameters(pin, pinNumber, GPIONumber, chnNumber,
                   TPMNumber, muxAltMask);
  setBaseAddress(TPMNumber, &baseAddress);
  bindPeripheral(baseAddress);
  bindChannel(baseAddress, chnNumber);
  bindPin(GPIONumber, pinNumber);
  enablePeripheralClock(TPMNumber);
  enableGPIOClock(GPIONumber);
  selectMuxAlternative(muxAltMask);
}

/*!
 *   @fn         setFrequency.
 *
 *   @brief      Ajusta a frequência de operação do sinal PWM desejado.
 *
 *   Ajusta a frequência de operação do sinal PWM considerando a seguinte
 *   expressão:
 *
 *   generated_frequency = 20.94*10^6/((MODRegister + 1)*2^(divBase));
 *
 *   @param[in]  divBase - fator de divisão.
 *               MODRegister - valor do registrador TPMxMOD.
 *
 *   @remarks    Sigla e pagina do Manual de Referencia KL25:
 *               - TPMxMOD: Status Control Register. Pág.554.
 */
void mkl_TPMPulseWidthModulation::setFrequency(tpm_Div divBase,
                                               uint16_t MODRegister) {
  /*!
   * Desabilita operação (recomendação do fabricante).
   */
  disableOperation();
  /*!
   * Ajusta a frequência do divisor Prescale.
   */
  *addressTPMxSC = divBase;
  /*!
   * Ajusta o registrador Modulo.
   */
  *addressTPMxMOD = MODRegister;

}

/*!
 *   @fn         setDutyCycle.
 *
 *   @brief      Ajusta o duty cycle do PWM.
 *
 *   Este método ajusta o duty cycle considerando a seguinte expressão:
 *   duty_cycle = 100 - (CnVRegister/(MODRegister + 1))*100, onde:
 *   CnVRegister: valor passado por parâmetro para este método.
 *   MODRegister: valor passado por parâmetro no método setFrequency.
 *
 *   @param[in]  CnVRegister - valor desejado para o registrador TPMxCnV.
 *
 *   @remarks    Sigla e pagina do Manual de Referencia KL25:
 *               - TPMxCnV: Channel Value Register. Pág. 557.
 */
void mkl_TPMPulseWidthModulation::setDutyCycle(uint16_t CnVRegister) {
  /*!
   * Desabilita medição (recomendação do fabricante).
   */
  disableOperation();
  /*!
   * Ajusta o duty cycle.
   */
  *addressTPMxCnV = CnVRegister;

}

/*!
 *   @fn         enableOperation.
 *
 *   @brief      Habilita a operação do PWM.
 *
 *   Este método inicia a operação do PWM tendo como saída o pino
 *   fornecido no construtor.
 *
 *   @remarks    Sigla e pagina do Manual de Referencia KL25:
 *               - TPMxSC: Status Control Register. Pág.552.
 */
void mkl_TPMPulseWidthModulation::enableOperation() {
  /*!
   * Ajusta o módulo TPM para operar no modo PWM.
   */
  setPWMOperation();
  /*!
   * Habilita a operação escrevendo "10" no campo CMOD (Clock Mode Selection)
   * do registrador SC.
   */
  *addressTPMxSC |= 0x08;
}

/*!
 *   @fn         disableOperation.
 *
 *   @brief      Desabilita a operação corrente do PWM.
 *
 *   @remarks    Sigla e pagina do Manual de Referencia KL25:
 *               - TPMxSC: Status Control Register. Pág.552.
 */
void mkl_TPMPulseWidthModulation::disableOperation() {
  *addressTPMxSC &= ~0x08;
}

/*!
 *   @fn         setPWMOperation.
 *
 *   @brief      Ajusta o módulo TPM para operar no modo PWM.
 *
 *   Este método realiza a configuração dos registrador de controle de
 *   status do canal para a realização da operação de PWM.
 *
 *   @remarks    Sigla e pagina do Manual de Referencia KL25:
 *               - TPMxCnSC: Channel Status and Control Register. Pág.555.
 */
void mkl_TPMPulseWidthModulation::setPWMOperation() {
  *addressTPMxCnSC = 0x20 | 0x08;
}
