# cnew-maquinalavar2

Implementação de um protótipo de máquina de lavar controlada remotamente por bluetooth, microprocessada com ARM Cortex-M0+, usando C++.

**Status**: Em desenvolvimento

# Arquitetura do Sistema

O projeto está sendo desenvolvido em duas sprints:
 
  * C1 - Módulo Periféricos
  * C2 - Módulo Controle
 
 ![Alt Text](https://github.com/PeMatias/cnew-maquinalavar2/blob/master/DiagramaBlocos.PNG)
 ![Alt Text](https://github.com/PeMatias/cnew-maquinalavar2/blob/master/legendaDiagramaBlocos.PNG)

# Características

O sistema oferecerá ao usuário final dois tipos de lavagens programadas na RAM: LD (Dia-a-Dia) e LE (Especial), na qual se diferem no tempo e na ordem de execução das etapas.

![Alt Text](https://github.com/PeMatias/cnew-maquinalavar2/blob/master/teclasCelular.PNG)

## C1 - Blocos Funcionais

Os blocos funcionais são aqueles que compõem a classe digital do sistema no nível mais alto do Módulo de Periféricos.

Lista de blocos funcionais que já foram implementados ou que estão sendo implementados na caminhada C1 :

- [X] Controlador LCD
- [X] Decodificador BCD-ASCII
- [X] Decodificador BCD-STRING
- [X] Contador Decresencente
- [X] Contador Up/Down
- [X] Divisor de Frequência
- [X] Lógica NL - Comparador
- [X] Debounce
- [X] Lógica On/Off
- [X] Monoestável
## C1 - Interfaces de Hardware

São clientes de instanciação dos Controladores de Hardware.

Lista de interfaces de hardware que já foram implementados ou que ainda estão sendo trabalhados:

- [x] Botão
- [x] Led
- [x] Chave
- [X] LCD
- [X] Buzzer
- [X] Oscilador
## C1 - Controladores de Hardware

São utilizados pelos blocos funcionais para acessar os Periféricos.

Lista de controladores de hardware que já foram implementados ou que ainda estão sendo trabalhados:

- [x] mkl_GPIOPort
- [x] mkl_TPMDelay
- [x] mkl_PITPeriodicInterrupt
- [X] mkl_LCDI2C

## C2 - Blocos Funcionais
Os blocos funcionais são aqueles que compõem a classe digital do sistema no nível mais alto do Módulo de Controle.

Lista de blocos funcionais que já foram implementados ou que estão sendo implementados na caminhada C2 :

## C2 - Interfaces de Hardware

São clientes de instanciação dos Controladores de Hardware.

Lista de dispositivos externos de hardware que foram implementados na Caminhada 2:

## C2 - Controladores de Hardware

São utilizados pelos blocos funcionais para controlar os Periféricos de C2.

Lista de controladores de hardware que foram utilizados do framework:

- [ ] mkl_TPMPWM
- [ ] mkl_UARTPort
- [ ] mkl_UARTInterrupt
