/**
 * Project Untitled
 */


#ifndef _LOGICAONOFF_H
#define _LOGICAONOFF_H

typedef enum {
	ligado,
	reset,
	desligado,
	espera
} StateMachine;

class LogicaOnOff {
public: 
    StateMachine stateMachine;
    
    LogicaOnOff();
    
void botaoOnEvent();
    
void botaoOffEvent();
    
void reset();
    
void beep();
};

#endif //_LOGICAONOFF_H
