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
	void decCounter(bool carryIn, bool clk);
    
	char readCounter();
    
	bool isCarryOut();

	bool isEnable();

	void setEnable(bool valor);

    bool enable;

protected:
    char data;
    int module;
};

#endif //_DOWNCOUNTER_H
