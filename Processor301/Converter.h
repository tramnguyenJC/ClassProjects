//****************************************************************
//* This class performs conversion between binary, decimal, or
//* hexadecimal representation of a string
#ifndef __CONVERTER_H__
#define __CONVERTER_H__

#include <string>
#include <map>
#include <iostream>
using namespace std;

class Converter{
private:
	map<string, string> myHexMap;
	map<string, string> myHexMap2;
	void initializeHexMap();

public:
	Converter();
	Converter(Converter& im);

	~Converter();

	string binaryToHex(string input);
	string hexToBinary(string input);
	int binaryToDecimal(string binary);
    string decToBin( int i, int length );
	string addPaddingBits(string bitstring, int length, char pad);
};

#endif