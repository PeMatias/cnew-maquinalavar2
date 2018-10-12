/*!
 * Interface da classe LED.
 */

#include "mkl_GPIOPort.h"

/*!
 *  @class    led
 *
 *  @brief    Classe de implementação de um LED.
 *
 *  @details  Esta classe é usada para representar um LED da placa KL25Z128.
 *
 */
class Led {

	protected:
		/*! Objeto da porta de saída do LED. */
		mkl_GPIOPort port;	
	public:
		/*!
		 * Construtor padrão da classe (apaga o LED).
		 */
		Led(gpio_Pin);
		/*!
		 * Métodos para mudar o estado do LED.
		 */
		void setOn();
		void setOff();

}; //! Fim da Classe
