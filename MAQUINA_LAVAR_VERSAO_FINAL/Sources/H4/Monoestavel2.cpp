/**
 * Project Untitled
 */


#include "Monoestavel2.h"

/**
 * Monoestavel2 implementation
 */

/*Monoestavel2::Monoestavel2(SM_Output output_){

	output = output_;

}*/


/*void Monoestavel2::toLedBuzzer(SM_Output output) {

}*/

SM_Output Monoestavel2::toLedBuzzer(SM_Output output) {

	Led led(gpio_PTB0);
	Led buzzer(gpio_PTB1);

	buzzer.setOff();

	if ( output.ledStandbyOff )
		led.setOn();
	else
		led.setOff();

	// Beep
	if ( output.beep == BEEP_LONG ){
		buzzer.setOn();
		longDelay();
		buzzer.setOff();
	} else if ( output.beep == BEEP_SHORT ){
		buzzer.setOn();
		veryShortDelay();
		buzzer.setOff();
	} else {
		buzzer.setOff();
	}

}
