//***************************************************************
//* This class provides an encapsulated version of Memory for the
//* use of InstructionMemory and DataMemory. It parses in inputs 
//* and store address and data into a map.
#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <string>
#include <map>
#include <iostream>
#include <fstream>
using namespace std;

#include "Converter.h"

class Memory{
private:
	std::map<std::string,std::string> myMap;
	string myInputFile;
	Converter converter;
	string name;

public:
	Memory();
	Memory(Memory& im);
	Memory(string _inputFile); //initialize with the inputFile containing the memory

	~Memory();

	void print();
	void printToFile(string file1);

	string readData(string address);
	void writeData(string data, string address);

	void setName(string name){this->name = name;}
	string getName(){return name;}
};
#endif