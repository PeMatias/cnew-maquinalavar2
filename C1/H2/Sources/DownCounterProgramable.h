/**
 * Project Untitled
 */


#ifndef _DOWNCOUNTERPROGRAMABLE_H
#define _DOWNCOUNTERPROGRAMABLE_H

#include "DownCounter.h"


class DownCounterProgramable: public DownCounter {
public: 
    
/**
 * @param int valor
 */
	DownCounterProgramable(int valor);
    
/**
 * @param writeTE
 */
	void writeData(bool writeTE, char valor);


};

#endif //_DOWNCOUNTERPROGRAMABLE_H
