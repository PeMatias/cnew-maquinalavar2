/**
 * Project Untitled
 */


#ifndef _COMPARADOR_H
#define _COMPARADOR_H

//#include "Logica.h"


class Comparador  {
public: 
    
	Comparador();
    
	bool isEqual();
    
	bool isGreat();
    
	bool isLess();

	void writeData1(char *valor);

	void writeData2(char *valor);

protected:
    char data1[2];
    char data2[2];
};

#endif //_COMPARADOR_H
