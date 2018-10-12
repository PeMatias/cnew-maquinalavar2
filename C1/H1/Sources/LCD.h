/**
 * Project Untitled
 */


#ifndef _LCD_H
#define _LCD_H
#include "mkl_LCD.h"


class LCD {
public: 
    
	LCD();
    
/**
 * @param data
 */
	void print(string data);
private: 

	mkl_LCD painel= mkl_LCD(mode2Lines, mode16Cols, mode5x8Dots, i2c_PTE1, i2c_PTE0, 0x27);
};

#endif //_LCD_H
