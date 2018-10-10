//**************************************************************
//* This class is the program counter that points to the instruction
//* to be executed
#include <string>
#include <iostream>
#include <fstream>
#include "Converter.h"

using namespace std;
class PC{
private:
	string myAddress; //large enough to store address?
	string name;
	Converter converter;
public:
	PC(); //default constructor
	PC(PC& pc); //copy constructor

	~PC(); //destructor

	string getAddress(); //accessor method
	void changeAddress(string address); //will update the address that the PC is pointing to

	void setName(string name){this->name = name;}
	string getName(){return name;}

	void printToFile(string file1);
	void print();
};