//***************************************************************
//* This class stores the mapping of data to memory address
#include <string>
#include "Converter.h"
#include "Memory.h"
using namespace std;

class DataMemory{
private:
	Memory myMemory; // memory
	Converter converter;
	string name;
	string address;
	string writeData1;
	string readData1;

public:
	DataMemory();
	DataMemory(DataMemory& im);
	DataMemory(Memory& memory); //initialize with the Memory

	~DataMemory();

	void setName(string name);
	string getName(){return name;}

	string readData(string address);
	void writeData(string data, string address);
	void print();
	void printSystem();
	void printToFile(string file1);
	void printSystemToFile(string file1);
};