#include "Left2Shifter.h"

using namespace std;

//***************************************************************
//* @brief Default Constructor
Left2Shifter::Left2Shifter(){
	instruction = "";
}

//***************************************************************
//* @brief Copy Constructor
//* @param left2Shiter Left2Shifter object to be copied
Left2Shifter::Left2Shifter(Left2Shifter& left2Shifter){
	shiftedInstruction = left2Shifter.shiftedInstruction;
}

//***************************************************************
//* @brief Destructor
Left2Shifter::~Left2Shifter(){}

//*******************************************************
//* inputInstruction(string instruction)
//* This method sets the instruction in the Left2Shifter
//* object to the given instruction that has been 
//* shifted two bits to the left
//* Preconditions: string instruction to be stored
//* as a 2 bit shifter left instruction 
//*******************************************************
void Left2Shifter::inputInstruction(string instruction, int length)
{
	//append two 0 bits to the end 
	string temp = instruction;
	temp += "00";

	while(temp.length() > length)
	{
		temp = temp.substr(1, temp.length()-1);
	}


	shiftedInstruction = temp;
}

//*******************************************************
//* getInstruction()
//* This method return the shifted 2 bit left instruction in 
//* the Left2Shifter object
//* Preconditions: none
//* Postconditions: the left shifted (2 bits) instruction
//*******************************************************
string Left2Shifter::getInstruction()
{
	//returns myInstruction which was shifted left upon inputting
	return shiftedInstruction;
}

//***************************************************************
//* @brief print content to file
//* @param file1 given file name
void Left2Shifter::printToFile(string file1)
{
	std::ofstream file;
  	file.open (file1, std::ofstream::out | std::ofstream::app);

	file << name << " input: 0x" << converter.binaryToHex(instruction) << endl;
	file << name << " output: 0x" << converter.binaryToHex(shiftedInstruction) << endl; 

	file.close();
}

//***************************************************************
//* @brief print content to console
void Left2Shifter::print()
{
	cout << name << " input: 0x" << converter.binaryToHex(instruction) << endl;
	cout << name << " output: 0x" << converter.binaryToHex(shiftedInstruction) << endl; 
}

