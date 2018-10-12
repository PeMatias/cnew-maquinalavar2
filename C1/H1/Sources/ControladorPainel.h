/**
 * Project Untitled
 */


#ifndef _CONTROLADORPAINEL_H
#define _CONTROLADORPAINEL_H
#include <cstdint>
#include <string>
using namespace std;


class ControladorPainel {
public: 
    
	ControladorPainel();
    
	bool isEnable();
    
	string readData();
    
/**
 * @param TEuni
 * @param TEdez
 * @param NLuni
 * @param NLdez
 * @param tipo
 * @param estado
 * @param etapa
 */
void writeData1(char TEuni, char TEdez, char NLuni, char NLdez, string tipo, string estado, string etapa);
private: 
    string data;
};

#endif //_CONTROLADORPAINEL_H
