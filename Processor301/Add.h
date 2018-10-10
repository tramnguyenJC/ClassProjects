//***************************************************************
//* This class adds two input and return result
#include <string>
#include <fstream>
#include <iostream>

using namespace std;
#include "Converter.h"

class Add{

private:
	string inputOne;
	string inputTwo;
	Converter converter;
	string name;

public:
	void setName(string name){this->name = name;}
	string getName(){return name;}
	void setInputOne(string input){inputOne = input;}
	void setInputTwo(string input){inputTwo = input;}
	string getOutput();
	void printToFile(string file1);
	void print();
};