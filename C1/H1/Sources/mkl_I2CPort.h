/*!
 * @copyright   � 2017 Universidade Federal do Amazonas.
 *
 * @brief       Interface da API em C++ da classe m�e I2C.
 *
 * @file        mkl_I2CPort.h
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
 
 * @section     LICENSE
 *
 *              GNU General Public License (GNU GPL)
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

#ifndef C__USERS_MSCAS_DESKTOP_CPPLINT_MASTER_MKL_I2CPORT_H_
#define C__USERS_MSCAS_DESKTOP_CPPLINT_MASTER_MKL_I2CPORT_H_

#include "mkl_I2C.h"

/*!
 *  @class    mkl_I2CPort_H
 *
 *  @brief    Classe de implementa��o do perif�rico I2C para a placa KL25Z128.
 *
 *  @details  Esta classe � usada para leitura ou escrita de dados de 8 bits
 *            e usa o perif�rico I2C.
 *
 */

class mkl_I2CPort : public mkl_I2C {
 public:
  explicit mkl_I2CPort(i2c_Pin_t pinSCL = i2c_PTE1,
                         i2c_Pin_t pinSDA = i2c_PTE0);

  /*!
   * M�todo de ajuste da velocidade de transmiss�o.
   */
  void baudRate(i2c_baudRate_t speed);

  /*!
   * M�todos de configura��o do I2C.
   */
  void setSlave(uint8_t address);
  uint8_t getSlave();
  void enableAck();
  void disableAck();

  /*!
   * M�todos comuns de Escrita e Leitura.
   */
  i2c_Exception_t startTransmission();
  i2c_Exception_t startTransmissionTo(uint8_t address);

  /*!
   * M�todos de Escrita.
   */
  void waitTransfer();
  void send8Bits(uint8_t data);
  void stopTransmission();

  /*!
   * M�todos de Leitura.
   */
  i2c_Exception_t selectReceptionMode();
  i2c_Exception_t selectReceptionModeFrom(uint8_t slave);

  /*!
   * Espera a chegada do dado.
   */
  i2c_Exception_t waitArrived();
  /*!
   * Retorna o dado recebido.
   */
  uint8_t receive8Bits();

  /*!
   * M�todo de excess�o.
   */
  i2c_Exception_t ExceptionOcurred();

  uint8_t slaveAddress;
  i2c_Exception_t exception;
};

#endif  //  C__USERS_MSCAS_DESKTOP_CPPLINT_MASTER_MKL_I2CPORT_H_
