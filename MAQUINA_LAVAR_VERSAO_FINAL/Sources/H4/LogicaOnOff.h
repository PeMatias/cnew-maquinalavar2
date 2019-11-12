/**
 * Project Untitled
 */

#ifndef _LOGICAONOFF_H
#define _LOGICAONOFF_H

// Definition of the possible Beep states
typedef enum {
	BEEP_OFF,
	BEEP_SHORT,
	BEEP_LONG
} Beep;

// Definition of the onoff logic state machine
typedef enum {
	ST_OFF,
	ST_RESET,
	ST_ON,
	ST_WAIT
} States;

// Definition of the output of each state
typedef struct {
	bool reset;
	Beep beep;
	bool ledStandbyOff;
} SM_Output;

class LogicaOnOff {

protected:

	States currentState;
	void refreshOutputSM();
	SM_Output output;


public:

	LogicaOnOff();
	void botaoOnEvent();
	void botaoOffEvent();
	States getCurrentState();
	SM_Output getOutputSM();

};

#endif //_LOGICAONOFF_H
