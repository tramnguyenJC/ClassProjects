//****************************************************************
//* This class performs arithmetic addition or subtraction operations 
//* on given inputs and return appropriate results.
#include <string>
#include <fstream>
#include "Converter.h"
#include <iostream>
using namespace std;



class ALU{
private:
	string ALUControl; //coming from ALUcontrol

	string inputOne;
	string inputTwo;
	Converter converter;
	string result;
	string name;

	int zeroControl;

public:
	ALU();
	ALU(ALU& alu);
	~ALU();

	void setInputOne(string value){inputOne = value;}
	void setInputTwo(string value){inputTwo = value;}

	void setName(string name){this->name = name;}
	string getName(){return name;}

	void setALUControl(string value){ALUControl = value;}

	int getZero(){return zeroControl;}
	string getResult(); 

	void printToFile(string file1);
	void print();
};