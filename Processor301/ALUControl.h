//****************************************************************
//* This class sens control signals to the ALU based on function code
#include <string>
#include <iostream>
#include <fstream>

#include "Converter.h"
using namespace std;

class ALUControl{
	private:
		int ALUOp1;
		int ALUOp0;
		string name;

		std::string functionCode;
		std::string aluControl;
		Converter converter;

	public:
		ALUControl();
		ALUControl(ALUControl& aluControl);

		~ALUControl();

		void setALUOp(int op1, int op2);
		void setFunctionCode(std::string functionCode);

		void setName(string name){this->name = name;}
		string getName(){return name;}

		std::string getALUControl(int op1, int op0, std::string functionCode);
		std::string getALUControl();

		int getALUOp1(){return ALUOp1;}
		int getALUOp0(){return ALUOp0;}

		void print();
		void printToFile(string file1);

		std::string getFunctionCode(){return functionCode;}
};