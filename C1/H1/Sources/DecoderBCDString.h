/**
 * Project Untitled
 */


#ifndef _DECODERBCDSTRING_H
#define _DECODERBCDSTRING_H
#include <cstdint>
#include <string>
using namespace std;

class DecoderBCDString {
public: 
    
	DecoderBCDString();
    
	void writeData(char value);
    
	string readData();

private: 
    string data;
};

#endif //_DECODERBCDSTRING_H
