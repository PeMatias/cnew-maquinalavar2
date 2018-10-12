/**
 * Project Untitled
 */


#include "Botao.h"


/**
 * Botao implementation
 */


/**
 * @param pin
 */
Botao::Botao(gpio_Pin pin) {
	  this->port.setPortMode(gpio_input);
	  this->port.setPullResistor(gpio_pullUpResistor);//Sempre retorna o valor zero

}

/**
 * @return bool
 */
bool Botao::isOn()
{
    return false;
}

/**
 * @return bool
 */
bool Botao::isOff() {
    return false;
}
