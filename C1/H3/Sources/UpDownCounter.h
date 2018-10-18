/**
 * Project Untitled
 */


#ifndef _UPDOWNCOUNTER_H
#define _UPDOWNCOUNTER_H

#include "DownCounter.h"

class UpDownCounter : public DownCounter {
public:

/**
 * @param int valor
 */
	UpDownCounter(int valor);

	void incCounter(bool carryIn, bool clk);
	bool isCarryOut();

};

#endif //_UPDOWNCOUNTER_H
