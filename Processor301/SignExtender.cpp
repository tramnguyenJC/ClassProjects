
#include "SignExtender.h"

using namespace std;

//*******************************************************
//* Default constructor
SignExtender::SignExtender(){
	extendedInstruction = "";
}

//*******************************************************
//* Copy constructor
//* @param signExtender the given SignExtender to be copied
SignExtender::SignExtender(SignExtender& signExtender){
	extendedInstruction = signExtender.extendedInstruction;
}

//*******************************************************
//* Destructor
SignExtender::~SignExtender(){
}

//*******************************************************
//* inputInstruction(string instruction)
//* This method sets the instruction in the SignExtender
//* object to the appropriately sign extended version
//* of the given instruction.
//* Preconditions: string instruction to be stored
//* as a sign extended instruction in the SignExtender
//*******************************************************
void SignExtender::inputInstruction(string instruction){
	char firstChar = instruction[0];
	this->instruction = instruction;
	//extend the first char appropriately
	if (firstChar == '1')
	{
		extendedInstruction = "1111111111111111";
		extendedInstruction += instruction;
		
	} else {
		extendedInstruction = "0000000000000000";
		extendedInstruction += instruction;
	}
}

//*******************************************************
//* getInstruction()
//* This method return the sign extended instruction in 
//* the SignExtender object.
//* Preconditions: none
//* Postconditions: the sign extended instruction
//*******************************************************
string SignExtender::getInstruction(){
	//return myInstruction, which has already been extended upon setting
	return extendedInstruction;
}

//***************************************************************
//* @brief print content to file
//* @param file1 given file name
void SignExtender::printToFile(string file1)
{
	std::ofstream file;
  	file.open (file1, std::ofstream::out | std::ofstream::app);

	file << name << " input: 0x" << converter.binaryToHex(instruction) << endl;
	file << name << " output: 0x" << converter.binaryToHex(extendedInstruction) << endl;

	file.close();
}

//***************************************************************
//* @brief print content to console
void SignExtender::print()
{
	
	cout << name << " input: 0x" << converter.binaryToHex(instruction) << endl;
	cout << name << " output: 0x" << converter.binaryToHex(extendedInstruction) << endl;
}






