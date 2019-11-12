/*!
 * @copyright   Â© 2017 Salmiakki UFAM
 *
 * @brief       Interface da API em C++ para Display LCD utilizando I2C.
 *
 * @file        mkl_LCD.cpp
 * @version     1.0
 * @date        28 Novembro 2017
 *
 * @section     HARDWARES & SOFTWARES
 *              +board        FRDM-KL25Z da NXP.
 *              +processor    MKL25Z128VLK4 - ARM Cortex-M0+
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

#include "mkl_LCD.h"
#include "mkl_I2CPort.h"

/*!
 *    @brief      MÃ©todo de configuraÃ§Ã£o do display LCD
 *
 *    Este mÃ©todo constrÃ³i o objeto mkl_LCD e define o nÃºmero de linhas, colunas e pixels
 *    e seleciona os pinos e o endereÃ§o para comunicaÃ§Ã£o I2C.
 *
 *    @param[i]   numLines - opÃ§Ã£o de nÃºmero de linhas do display.
 *                numCols - opÃ§Ã£o de nÃºmeoro de colunas do display.
 *                numPixels - opÃ§Ã£o de nÃºmero de colunas do display.
 *                SCLPin - pino para sinal de clock do I2C.
 *                SCAPin - pino para sinal de dados do I2C.
 *                I2CAddress - endereÃ§o do mÃ³dulo de comunicaÃ§Ã£o I2C.
 */
mkl_LCD::mkl_LCD(functionSetOption numLines, functionSetOption numCols,
  functionSetOption numPixels, i2c_Pin_t SCLPin, i2c_Pin_t SCAPin,
  uint8_t I2CAddress) {
_numLines = numLines;
_numPixels = numPixels;
_numCols = numCols;

_I2C = mkl_I2CPort(SCLPin, SCAPin);
//_I2C = mkl_I2CMasterPort(SCLPin, SCAPin);
_I2CAddress = I2CAddress;
_I2C.baudRate(i2c_highSpeed);
//_I2C.baudRate(i2c_highSpeed);
_I2C.setSlave(_I2CAddress);

initialize();
}

/*!
 *   @brief      MÃ©todo de pausa do programa
 *
 *   Interrompe o programa para o periodo de tempo (em milissegundos) especificado
 *   como parametro.
 *
 *   @param[in]  milliSeconds - o nÃºmero de milissegundos para fazer uma pausa
 */
void mkl_LCD::delay(uint32_t milliSeconds) {
uint32_t i;
uint32_t j;

for (i = 0; i < milliSeconds; i++) {
for (j = 0; j < 1500; j++) {}
}
}

/*!
 *   @brief      MÃ©todo de pausa do programa
 *
 *   Interrompe o programa para o periodo de tempo (em microssegundos)
 *   especificado como parametro.
 *
 *   @param[in]  microSeconds - o nÃºmero de microssegundos para fazer uma pausa
 */
void mkl_LCD::delayMicroSeconds(uint32_t microSeconds) {
uint32_t i;
uint32_t j;
uint32_t k;

for (i = 0; i < (microSeconds); i++) {
for (j = 0; j < 0; j++) {}
}
}

/*!
 *    @brief      Envia dados ao mÃ³dulo I2C
 *
 *    Este metodo inicia a transmissÃ£o I2C, envia os 8bits no formato dados e
 *    variavel de plano de fundo. Espera a transferencia dos dados e encerra a
 *    transmissao.
 *
 *    @param[in]  data - dados a serem transmitidos ao modulo I2C para serem
 *                        enviados ao display.
 */
void mkl_LCD::sendI2C(uint8_t data) {
_I2C.startTransmission();
_I2C.send8Bits(data | _backLight);
_I2C.waitTransfer();
_I2C.stopTransmission();
}

/*!
 *   @brief      Escreve 4 bits para o display
 *
 *   Este metodo envia informacoes de dados e controle para o display via I2C.
 *
 *   @param[in]  data - dados a serem enviados
 *               control - indica o tipo de dado enviado
 *                         control pode ser:
 *                         1 ou controlSignals::Rs para envio de dados
 *                         0 para envio de comandos
 */
void mkl_LCD::writeNibble(uint8_t data, uint8_t control) {
data &= 0xF0;
control &= 0x0F;
sendI2C(data | control);
delayMicroSeconds(50);
sendI2C(data | control | En);

delayMicroSeconds(1);

sendI2C(data & ~En);
delayMicroSeconds(50);
}

/*!
 *   @brief      escreve caractere no display
 *
 *   Este metodo envia ao display o caracter
 *
 *   @param[in]  data - caracter a ser escrito no display
 */
void mkl_LCD::putChar(char data) {
writeNibble(data & 0xF0, Rs);
writeNibble(data << 4, Rs);
//delayMicroSeconds(50);
}

/*!
 *   @brief      escreve cadeira de caracteres no display
 *
 *   Este metodo envia ao display os caracteres da variavel de entrada
 *
 *   @param[in]  data - String a ser escrita no display
 */
void mkl_LCD::putString(string data) {
uint32_t i;

for (i = 0; i < data.length(); i++) {
  putChar(data[i]);
}
}

/*!
 *   @brief      envia comando ao display
 *
 *   Este metodo Ã© utilizado pelos mÃ©todos de ajustes e de acessos/cursor. Envia
 *   instruÃ§Ãµes de comando ao display
 *
 *   @param[in]  command - valor inteiro que corresponde a um comando
 */
void mkl_LCD::sendCommand(uint8_t command) {
	writeNibble(command & 0xF0, 0);

	writeNibble(command << 4, 0);

	/*if(command < 4)
	delayMicroSeconds(2000);
	else
	delayMicroSeconds(50);

	writeNibble(command << 4, 0);

	if(command < 4)
	delayMicroSeconds(2000);
	else
	delayMicroSeconds(50);*/
}

/*!
 *   @brief      inicializa o display
 *
 *   Este metodo realiza a inicializaÃ§Ã£o do display. Configura o formato do
 *   display, os parÃ¢metros de ajustes e retornar o cursor para home.
 */
void mkl_LCD::initialize() {
delay(50);

writeNibble(0x30, 0);
delayMicroSeconds(4500);
//----------------------------------

writeNibble(0x30, 0);
delayMicroSeconds(4500);
//----------------------------------

writeNibble(0x30, 0);
delayMicroSeconds(150);
//----------------------------------

writeNibble(0x20, 0);
delayMicroSeconds(150);
//----------------------------------

sendCommand(functionSet | mode4Bits | _numLines | _numPixels);

//----------------------------------
_displayControl = displayOn | cursorOn | blinkOn;
sendCommand(displayControl | _displayControl);
//----------------------------------

sendCommand(clearDisplay);
//----------------------------------
_entryModeSet = decrement | shiftDecrement;
sendCommand(entryModeSet | _entryModeSet);
//----------------------------------

sendCommand(returnHome);
//----------------------------------
}

/*!
 *   @brief      Acende a luz de fundo do display
 *
 *   Este metodo ativa a luz de fundo. Ã‰ um metodo de ajuste.
 */
void mkl_LCD::setBacklightOn() {
_backLight = backLightOn;
sendI2C(0);
}

/*!
 *   @brief      Desliga a luz de fundo do display
 *
 *   Este metodo desativa a luz de fundo. Ã‰ um metodo de ajuste.
 */
void mkl_LCD::setBacklightOff() {
_backLight = backLightOff;
sendI2C(0);
}



/*!
 *   @brief      Desativa do display
 *
 *   Este metodo desativa o display. Ã‰ um metodo de ajuste.
 */
void mkl_LCD::setDisplayOff() {
_displayControl &= ~displayOn;
sendCommand(displayControl | _displayControl);
}

/*!
 *   @brief      Ativa do display
 *
 *   Este metodo ativa o display. Ã‰ um metodo de ajuste.
 */
void mkl_LCD::setDisplayOn() {
_displayControl |= displayOn;
sendCommand(displayControl | _displayControl);
}

/*!
 *   @brief      Desativa a exibiÃ§Ã£o do cursor do display
 *
 *   Este metodo desativa o cursor. Ã‰ um metodo de ajuste.
 */
void mkl_LCD::setCursorOff() {
_displayControl &= ~cursorOn;
sendCommand(displayControl | _displayControl);
}

/*!
 *   @brief      Ativa a exibiÃ§Ã£o do cursor do display
 *
 *   Este metodo ativa o cursor. Ã‰ um metodo de ajuste.
 */
void mkl_LCD::setCursorOn() {
_displayControl |= cursorOn;
sendCommand(displayControl | _displayControl);
}

/*!
 *   @brief      Desativa a opÃ§Ã£o de piscar do cursor do display
 *
 *   Este metodo desativa a opÃ§Ã£o piscar cursor. Ã‰ um metodo de ajuste.
 */
void mkl_LCD::setBlinkOff() {
_displayControl &= ~blinkOn;
sendCommand(displayControl | _displayControl);
}

/*!
 *   @brief      Ativa a opÃ§Ã£o de piscar do cursor do display
 *
 *   Este metodo ativa a opÃ§Ã£o piscar cursor. Ã‰ um metodo de ajuste.
 */
void mkl_LCD::setBlinkOn() {
_displayControl |= blinkOn;
sendCommand(displayControl | _displayControl);
}

/*!
 *   @brief      Limpa tela
 *
 *   Este metodo limpa toda informaÃ§Ã£o que houver no display.
 */
void mkl_LCD::clear() {
sendCommand(clearDisplay);
}

/*!
 *   @brief      Retorna o cursor para a posiÃ§Ã£o de inicio
 *
 *   Este metodo retorna o cursor para a posicao de inicio, ou home.
 */
void mkl_LCD::home() {
sendCommand(returnHome);
}

/*!
 *   @brief       Define posiÃ§Ã£o do cursor
 *
 *   Este metodo permite definir a linha e a coluna em que o cursor estara
 *   posicionado.
 *
 *   @param[in]    row - valor da linha. Deve estar entre 1 e 4.
 *                 col - valor da coluna.
 */
void mkl_LCD::setCursor(uint8_t row, uint8_t col) {
col = col - 1;
row = row - 1;

int lines = 0;
int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };

if(_numLines == mode2Lines) {
lines = 2;
} else if (_numLines == mode4Lines) {
lines = 4;
}

sendCommand(setDDRAMAddr | ((col) + row_offsets[(row)]));
}

/*!
 *   @brief      Desloca o conteudo do display para a esquerda
 *
 *   Este metodo desloca o conteudo do display (cursor e texto) um espaco para a
 *   esquerda.
 */
void mkl_LCD::scrollDisplayLeft() {
sendCommand(cursorShift | displayMove | moveLeft);
}

/*!
 *   @brief      Desloca o conteudo do display para a direita
 *
 *   Este metodo desloca o conteudo do display (cursor e texto) um espaco para a
 *   direita.
 */
void mkl_LCD::scrollDisplayRight() {
sendCommand(cursorShift | displayMove | moveRight);
}

/*!
 *   @brief      Altera o fluxo do texto para ser da esquerda para a direita
 *
 *   Este metodo define a direcao de escrita no LCD para ser da esquerda para a
 *   direita, como o padrÃ£o.
 */
void mkl_LCD::leftToRight() {
_entryModeSet |= decrement;
sendCommand(entryModeSet | _entryModeSet);
}

/*!
 *   @brief      Altera o fluxo do texto para ser da direita para a esquerda
 *
 *   Este metodo define a direcao de escrita no LCD para ser da direita para a
 *   esquerda.
 */
void mkl_LCD::rightToLeft() {
_entryModeSet &= ~decrement;
sendCommand(entryModeSet | _entryModeSet);
}

/*!
 *   @brief      Ativa rolagem automÃ¡tica do display
 *
 *   Este metodo faz com que cada caractere mostrado no display seja deslocado de
 *   um espaco. De acordo com a direÃ§Ã£o definida para o texto.
 */
void mkl_LCD::autoScroll() {
_entryModeSet |= shiftIncrement;
sendCommand(entryModeSet | _entryModeSet);
}

/*!
 *   @brief      Desativa rolagem automÃ¡tica do display
 */
void mkl_LCD::noAutoScroll() {
_entryModeSet &= ~shiftIncrement;
sendCommand(entryModeSet | _entryModeSet);
}
