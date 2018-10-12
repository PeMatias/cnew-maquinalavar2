/**
 * Project Untitled
 */


#ifndef _DECODERBCDASCII_H
#define _DECODERBCDASCII_H

class DecoderBCDAscii {
public: 
    
	DecoderBCDAscii();
/**
 * @param value
 */
	void writeData(char value);
    
	char readData();

private: 

    char data;
};

#endif //_DECODERBCDASCII_H
