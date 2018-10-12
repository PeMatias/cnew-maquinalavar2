/*!
 * Interface da classe Botao.
 */

#include "mkl_GPIOPort.h"

/*!
 *  @class    botao
 *
 *  @brief    Classe de implementação de um Botao.
 *
 *  @details  Esta classe � usada para representar um Botao da placa KL25Z128.
 *
 */
class Botao {

	protected:
		/*! Objeto da porta de saída do Botao. */
		mkl_GPIOPort port;	
	public:
		/*!
		 * Construtor padrão da classe (configurações do botão)
		 */
		Botao(gpio_Pin);
		/*!
		 * Método para realizar a leitura do estado do botão: true ou false.
		 */
		bool read();

}; //! Fim da Classe
