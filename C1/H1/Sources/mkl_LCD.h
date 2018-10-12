/*!
 * @copyright   Â© 2017 Salmiakki UFAM
 *
 * @brief       Interface da API em C++ para Display LCD utilizando I2C.
 *
 * @file        mkl_LCD.h
 * @version     1.0
 * @date        28 Novembro 2017
 *
 * @section     HARDWARES & SOFTWARES
 *              +board        FRDM-KL25Z da NXP.
 *              +processor    MKL25Z128VLK4 - ARM Cortex-M0+
 *              +peripherals  MÃ³dulo I2C para LCD, Display LCD
 *              +compiler     KinetisÂ® Design Studio IDE
 *              +manual       L25P80M48SF0RM, Rev.3, September 2012
 *              +revisions    VersÃ£o (data): DescriÃ§Ã£o breve.
 *                             ++ 1.0 (28 Novembro 2017): VersÃ£o inicial.
 *
 * @section     AUTHORS & DEVELOPERS
 *              +institution  Universidade Federal do Amazonas
 *              +courses      Engenharia da ComputaÃ§Ã£o
 *              +teacher      Miguel Grimm <miguelgrimm@gmail.com>
 *              +student      VersÃ£o inicial:
 *                             ++ JoÃ£o Danilo Pinto Junior <joaodanilo1992@gmail.com>
 *                             ++ Edson Nascimento Silva Neto <netosilvan78gmail.com>
 *                             ++ Pedro Henrique dos Santos Iunes <pedrohsiunes@gmail.com>
 *                             ++ Rebeca Nunes Rodrigues <rebeca.n.rod@gmail.com>
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

#ifndef SOURCES_LIB_LCD_MKL_LCD_H_
#define SOURCES_LIB_LCD_MKL_LCD_H_

#include <stdint.h>
#include "mkl_I2CPort.h"
#include <string>

using std::string;

/*!
 * DefiniÃ§Ã£o dos comandos recebidos pelo LCD
*/
typedef enum {
clearDisplay = 0x01 << 0,
 returnHome = 0x01 << 1,
 entryModeSet = 0x01 << 2,
 displayControl = 0x01 << 3,
 cursorShift = 0x01 << 4,
 functionSet = 0x01 << 5,
 setCGRAMAddr = 0x01 << 6,
 setDDRAMAddr = 0x01 << 7
} lcdCommand;

/*!
 * DefiniÃ§Ã£o das opÃ§Ãµes de cada comando do LCD
*/
typedef enum {
increment = 0x00,
 decrement = 0x01 << 1,
 shiftDecrement = 0x00,
shiftIncrement = 0x01 << 0
} entryModeSetOption;

typedef enum {
displayOn = 0x01 << 2,
 displayOff = 0x00,
 cursorOn = 0x01 << 1,
 cursorOff = 0x00,
 blinkOn = 0x01 << 0,
 blinkOff = 0x00
} displayControlOption;

typedef enum {
displayMove = 0x01 << 3,
 cursorMove = 0x00,
 moveRight = 0x01 << 2,
 moveLeft = 0x00
} cursorShiftOption;

typedef enum {
mode8Bits = 0x01 << 4,
 mode4Bits = 0x00,
 mode2Lines = 0x01 << 3,
 mode4Lines = 0x01 << 3,
 mode1Line = 0x00,
 mode16Cols = 16,
 mode20Cols = 20,
 mode5x10Dots = 0x01 << 2,
 mode5x8Dots = 0x00
} functionSetOption;

/*!
 * DefiniÃ§Ã£o das opÃ§Ãµes de luz de fundo
 */
typedef enum {
backLightOn = 0x01 << 3, backLightOff = 0x00
} backLightOption;

/*!
 * DefiniÃ§Ã£o dos sinais de controle do LCD
 */
typedef enum {
En = 0x01 << 2, Rw = 0x01 << 1, Rs = 0x01 << 0
} controlSignals;

/*!
 *   @brief    Classe de implementaÃ§Ã£o do perifÃ©rico Display LCD com I2C para a
 *             placa KL25Z128.
 *
 *   @details  Esta classe Ã© usada para configuraÃ§Ã£o, ajustes e escrita em
 *             Display LCD. Utiliza o perifÃ©rico I2C.
 *
 *   @section  EXAMPLES USAGE
 *
 *             Uso dos mÃ©todos de ajustes.
 *              +fn setDisplayOn();
 *              +fn setCursorOn();
 *
 *             Uso dos mÃ©todos de acessos/cursor
 *              +fn setCursor(int8_t col, uint8_t row);
 *
 *             Uso dos mÃ©todos de escrita.
 *              +fn write(string);
 */
class mkl_LCD {
 public:
  /*!
   * MÃ©todo de configuraÃ§Ã£o
   */
  mkl_LCD(functionSetOption numLines, functionSetOption numCols,
    functionSetOption numPixels, i2c_Pin_t SCLPin, i2c_Pin_t SCAPin,
    uint8_t I2CAddress);

  /*!
   * MÃ©todos de escrita
   */
  void putChar(char data);
  void putString(string data);

  /*!
   * MÃ©todos de acessos/cursor
   */
  void clear();
  void home();
  void setCursor(uint8_t col, uint8_t row);

  /*!
   * MÃ©todos de ajustes
   */
  void setBacklightOn();
  void setBacklightOff();
  void setDisplayOff();
  void setDisplayOn();
  void setCursorOff();
  void setCursorOn();
  void setBlinkOff();
  void setBlinkOn();

  /*!
   * MÃ©todos de rolagem
   */
  void scrollDisplayLeft();
  void scrollDisplayRight();
  void leftToRight();
  void rightToLeft();
  void autoScroll();
  void noAutoScroll();

 private:
  /*!
   * MÃ©todo privado de inicializaÃ§Ã£o
   */
  void initialize();

  /*!
   *  MÃ©todos privados de comunicaÃ§Ã£o I2C
   */
  void sendCommand(uint8_t command);
  void pulseEnable(uint8_t data);
  void delayMicroSeconds(uint32_t microSeconds);
  void delay(uint32_t milliSeconds);
  void sendI2C(uint8_t data);
  void writeNibble(uint8_t data, uint8_t control);

 private:
  /*!
   *  EndereÃ§o para comunicaÃ§Ã£o I2C
   */
  uint8_t _I2CAddress;

  /*!
   * NÃºmero de linhas, colunas e de pixels do display LCD
   */
  functionSetOption _numLines;
  functionSetOption _numCols;
  functionSetOption _numPixels;

  /*!
   * Instancia da classe I2C
   */

  mkl_I2CPort _I2C;

  /*!
   * Variaveis de ajustes e configuracao
   */
  backLightOption _backLight = backLightOn;
  uint8_t _displayControl;
  uint8_t _entryModeSet;
};
#endif  // SOURCES_LIB_LCD_MKL_LCD_H_
