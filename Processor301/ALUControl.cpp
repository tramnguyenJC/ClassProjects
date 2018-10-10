#include "ALUControl.h"
#include <string>

//*************************************************
//* ALUControl()
//* Constructor for ALUControl
//*************************************************
ALUControl::ALUControl()
{
	ALUOp1 = 0;
	ALUOp0 = 0;

	functionCode = "";
	aluControl = "";
}

//*************************************************
//* ALUControl()
//* Copy Constructor for ALUControl
//*************************************************
ALUControl::ALUControl(ALUControl& aluControl)
{
	ALUOp1=aluControl.ALUOp1;
	ALUOp0=aluControl.ALUOp0;

	functionCode = aluControl.functionCode;

	this->aluControl = aluControl.aluControl;
}

//*************************************************
//* ~ALUControl()
//* Destructor for ALUControl
//*************************************************
ALUControl::~ALUControl(){}

//*************************************************
//* setALUOp(int op1, int op0)
//* This method sets the ALUOp1 and ALUOp0 to 
//* the specified op1 and op0
//* Preconditions: int op1 - the leftmost digit of 
//* the ALUOp 
//* int op0 - the rightmost digit of the ALUOp
//* Postconditions: none
//*************************************************
void ALUControl::setALUOp(int op1, int op0)
{
	if (op1 != 0 && op1 != 1)
	{
		cerr << "ALUOp1 must be set to either 1 or 0. " << op1 << " is not a valid input." << endl;
	}

	if (op0 != 0 && op0 != 1)
	{
		cerr << "ALUOp0 must be set to either 1 or 0. " << op0 << " is not a valid input." << endl;
	}

	ALUOp0 = op0;
	ALUOp1 = op1;
}

//*************************************************
//* setFunctionCode(string functionCode)
//* This method sets the functionCode to the 
//* specified function code
//* Preconditions: string functionCode - binary
//* string representing the function code
//*************************************************
void ALUControl::setFunctionCode(string functionCode)
{
	this->functionCode = functionCode;
}

//*************************************************
//* getALUContro(int op1, int op0, string functionCode)
//* This method generates the four digit ALU control
//* using the specified op1, op0, and functionCode(in binary)
//* Preconditions: int op1 - the leftmost digit of 
//* the ALUOp 
//* int op0 - the rightmost digit of the ALUOp
//* string functionCode - binary string representing 
//* the function code
//* Postconditions: string representing the four 
//* digit ALU control code
//*************************************************
string ALUControl::getALUControl(int op1, int op0, string functionCode)
{
	setALUOp(op1,op0);
	setFunctionCode(functionCode);

	return getALUControl();
}

//*************************************************
//* getALUContro()
//* This method generates the four digit ALU control
//* using the op1, op0, and functionCode(in binary) 
//* currently in the ALUControl
//* Preconditions:
//* Postconditions: string representing the four 
//* digit ALU control code
//*************************************************
string ALUControl::getALUControl()
{	
	//LW or SW - add
	if (ALUOp1 == 0 && ALUOp0 == 0)
	{
		aluControl = "0010";
	}

	//BEQ - subtract
	if (ALUOp1 == 0 && ALUOp0 == 1)
	{
		aluControl = "0110";
	}

	//R -type
	if (ALUOp1 == 1 && ALUOp0 == 0)
	{
		if (functionCode == "100000"){aluControl = "0010";} //ADD
		if (functionCode == "100010"){aluControl = "0110";} //SUB
		if (functionCode == "101010"){aluControl = "0111";} //SLT
	}

	return aluControl;
}

//********************************************************
//* @brief print the function code and ALU Control in hexadecimal to the terminal
void ALUControl::print()
{	
	cout << name << " ALUOp1 input: 0x" << ALUOp1 << endl;
	cout << name << " ALUOp0 input: 0x" << ALUOp0 << endl;
	cout << name << " function code input: 0x" << converter.binaryToHex(functionCode) << endl;
	cout << name << " ALUControl: 0x" << converter.binaryToHex(aluControl) << endl;
}

//***************************************************************
//* @brief print input and output to file
//* @param file1 given file name
void ALUControl::printToFile(string file1)
{
	std::ofstream file;
  	file.open (file1, std::ofstream::out | std::ofstream::app);

	file << name << " ALUOp1 input: 0x" << ALUOp1 << endl;
	file << name << " ALUOp0 input: 0x" << ALUOp0 << endl;
	file << name << " function code input: 0x" << converter.binaryToHex(functionCode) << endl;
	file << name << " ALUControl: 0x" << converter.binaryToHex(aluControl) << endl;

	file.close();
}

