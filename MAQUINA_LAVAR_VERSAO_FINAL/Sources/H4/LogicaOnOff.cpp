/**
 * Project Untitled
 */


#include "LogicaOnOff.h"

/**
 * LogicaOnOff implementation
 */

LogicaOnOff::LogicaOnOff(){

	currentState = ST_OFF;
	refreshOutputSM();

}

void LogicaOnOff::botaoOnEvent() {

	if ( currentState == ST_OFF )
		currentState = ST_RESET;
	else if ( currentState == ST_ON )
		currentState = ST_WAIT;

	refreshOutputSM();

}

void LogicaOnOff::botaoOffEvent() {

	if ( currentState == ST_RESET ) {
		currentState = ST_ON;
	} else if ( currentState == ST_WAIT ){
		currentState = ST_OFF;
	}

	refreshOutputSM();

}

void LogicaOnOff::refreshOutputSM(){

	switch(currentState){
		case ST_OFF:
			output.reset = true;
			output.ledStandbyOff = true;
			output.beep = BEEP_OFF;
			break;
		case ST_RESET:
			output.reset = true;
			output.ledStandbyOff = false;
			output.beep = BEEP_SHORT;
			break;
		case ST_ON:
			output.reset = false;
			output.ledStandbyOff = false;
			output.beep = BEEP_OFF;
			break;
		case ST_WAIT:
			output.reset = true;
			output.ledStandbyOff = false;
			output.beep = BEEP_LONG;
			break;
		}

}

States LogicaOnOff::getCurrentState(){
	return currentState;
}

SM_Output LogicaOnOff::getOutputSM(){
	return output;
}
