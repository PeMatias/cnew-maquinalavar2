/*
 * DecoderCmdAddr.cpp
 *
 *  Created on: 20/11/2018
 *      Author: pevic
 */

#include "DecoderCmdAddr.h"

DecoderCmdAddr::DecoderCmdAddr() {
	// TODO Auto-generated constructor stub
	data = 0x0;
}

void DecoderCmdAddr::writeData(uint8_t cmd)
{
    //Power OnOff
    if(cmd == 0x10) data = 0x11;
    // End of Program
    else if(cmd == 0x60) data = 0x12;
    // Programa LE
    else if(cmd == 0x70) data = 0x00;
    //Programa LD
    else if(cmd == 0x50) data = 0x0F;
    // Beep
    else data = 0xFF;

}

uint8_t DecoderCmdAddr::readData()
{
	return data;
}
