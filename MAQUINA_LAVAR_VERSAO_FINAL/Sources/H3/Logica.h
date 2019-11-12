/**
 * Project Untitled
 */


#ifndef _LOGICA_H
#define _LOGICA_H

#include "Comparador.h"
#include "Led2.h"

class Logica : public Comparador {
public: 
    
/**
 * @param empty
 * @param full
 */
	Logica(char *dtRI);
    
	bool isEmpty(char *nivel);
    
	bool isFull(char *nivel);
    
	bool isEOC(char *nivel);

	void writeMax(char *valor);

protected: 
    char max[2];
    char min[2] = {'0','0'};
};

#endif //_LOGICA_H
