/*!
 * @copyright   © 2017 UFAM - Universidade Federal do Amazonas.
 *
 * @brief       Interface da classe "mkl_TPMPulseWidthModulation.h".
 *
 * @file        mkl_TPMPulseWidthModulation.h
 * @version     1.0
 * @date        02 Agosto 2017
 *
 * @section     HARDWARES & SOFTWARES
 *              +board        FRDM-KL25Z da NXP.
 *              +processor    MKL25Z128VLK4 - ARM Cortex-M0+.
 *              +compiler     Kinetis® Design Studio IDE.
 *              +manual       L25P80M48SF0RM, Rev.3, September 2012.
 *              +revisions    Versão (data): Descrição breve.
 *                             ++ 1.0 (20 Agosto 2017): Versão inicial.
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

#ifndef MKL_TPMPulseWidthModulation_H
#define MKL_TPMPulseWidthModulation_H

#include <stdint.h>
#include <MKL25Z4.h>
#include "mkl_TPM.h"

/*!
 *  @class    mkl_TPMPulseWidthModulation.
 *
 *  @brief    A classe implementa o serviço PWM do periférico TPM.
 *
 *  @details  Esta classe implementa o serviço PWM utilizando os
 *            periféricos TPM0, TPM1 ou TPM2 e os pinos correspondentes e
 *            herdando da classe mãe "mkl_TPM".
 *
 *  @section  EXAMPLES USAGE
 *
 *            Uso dos métodos para geração de sinal PWM.
 *
 *              +fn setFrequency(tpm_div16, 999);
 *              +fn setDutyCycle(750);
 *              +fn enableOperation();
 */
class mkl_TPMPulseWidthModulation : public mkl_TPM {
 public:
  /*!
   * Método construtor padrão da classe.
   */
  explicit mkl_TPMPulseWidthModulation(tpm_Pin pin = tpm_PTC1);

  /*!
   * Métodos de configuração de frequência e duty cycle do sinal.
   */
  void setFrequency(tpm_Div divBase, uint16_t MODRegister);
  void setDutyCycle(uint16_t CnVRegister);

  /*!
   * Método de habilitar a operação PWM.
   */
  void enableOperation();

  /*!
   * Método de desabilitar a operação PWM.
   */
  void disableOperation();

 private:
  /*!
   * Método de seleção do modo de operação PWM.
   */
  void setPWMOperation();
};

#endif  //  MKL_TPMPulseWidthModulation_H_
