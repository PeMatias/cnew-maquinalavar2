/**
 * Project Untitled
 */


#include "LCD.h"
#include "mkl_LCD.h"

/**
 * LCD implementation
 */


/**
 * @param mode2Lines
 * @param mode16Cols
 * @param mode5x8Dots
 * @param i2c_PTE1
 * @param i2c_PTE0
 * @param deviceAddress
 */
LCD::LCD()
{
	 //painel = mkl_LCD(mode2Lines, mode16Cols, mode5x8Dots, i2c_PTE1, i2c_PTE0, 0x27);
}

/**
 * @param data
 * @return void
 */
void LCD::print(string data) {
    return;
}
