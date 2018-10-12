/**
 * Project Untitled
 */


#ifndef _DOWNCOUNTER_H
#define _DOWNCOUNTER_H



class DownCounter {
public: 
    
/**
 * @param valor
 */
	DownCounter(int valor);
    
	void clearCounter();
    
/**
 * @param carryIn
 * @param clk
 * @param enable
 */
	void decCounter(bool carryIn, bool clk, bool enable);
    
	char readCounter();
    
	bool isCarryOut();
private: 
    char data;
    int module;
};

#endif //_DOWNCOUNTER_H
