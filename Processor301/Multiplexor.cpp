#include "Multiplexor.h"
#include <iostream>

using namespace std;

//******************************************************
//* Multiplexor()
//* Constructor for Multiplexor
//******************************************************
Multiplexor::Multiplexor(){
	myInput1 = "";
	myInput2 = "";
	myControl = false; ///do we need this??
}

//******************************************************
//* Multiplexor()
//* Copy Constructor for Multiplexor
//******************************************************
Multiplexor::Multiplexor(Multiplexor& multiplexor){
	myInput1 = multiplexor.myInput1;
	myInput2 = multiplexor.myInput2;
	myControl = multiplexor.myControl;
}

//******************************************************
//* ~Multiplexor()
//* Destructor for Multiplexor
//******************************************************
Multiplexor::~Multiplexor(){

}

//******************************************************
//* setControl(bool controlInput)
//* This method sets the multiplexor object's control
//* to the passed in argument
//* Preconditions: bool controlInput- boolean value 
//* to set control input
//* Postconditions: none
//******************************************************
void Multiplexor::setControl(bool controlInput){
	myControl = controlInput;
}

//******************************************************
//* getControl()
//* This method returns the control value
//* Precondtions:
//* Postconditions: bool representing the control value
//******************************************************
bool Multiplexor::getControl(){
	return myControl;
}

//******************************************************
//* setInputOne(string input)
//* This method sets the first input to the given string
//* input
//* Preconditons: string input - input to set in 
//* multiplexor
//* Postcondition: none
//******************************************************
void Multiplexor::setInputOne(string input){
	myInput1 = input;
}

//******************************************************
//* setInputTwo(string input)
//* This method sets the second input to the given string
//* input
//* Preconditons: string input - input to set in 
//* multiplexor
//* Postcondition: none
//******************************************************
void Multiplexor::setInputTwo(string input){
	myInput2 = input;
}

//******************************************************
//* getOutput()
//* This method uses the current control and inputs to 
//* generate the appropriate output. If the control is 
//* 0, the first input is the output. If the control is
//* 1, the second input is the output. The method returns
//* the string output
//* Preconditions:
//* Postconditions: string representing the appropriate
//* output of the multiplexor
//******************************************************
string Multiplexor::getOutput(){
	
	if(myControl == false)
	{
		return myInput1; //return input 1 if myControl is false (0)
	}else{
		return myInput2; //return input 2 if myControl is  (1) 
	}
}

//******************************************************
//* setInputs(string input1, string input2)
//* This method sets both inputs in the multiplexor. 
//* input1 is the first input and input2 is the second.
//* Preconditions: string input1 - the information for the
//* first input
//* string input2 -  the information for the second input
//* Postconditions:
//******************************************************
void Multiplexor::setInputs(string input1, string input2)
{
	myInput1 = input1;
	myInput2 = input2;
}

//***************************************************************
//* @brief print content to file
//* @param file1 given file name
void Multiplexor::printToFile(string file1)
{
	std::ofstream file;
  	file.open (file1, std::ofstream::out | std::ofstream::app);

	file << name << " inputOne: 0x" << converter.binaryToHex(myInput1) << endl;
	file << name << " inputTwo: 0x" << converter.binaryToHex(myInput2) << endl;
	file << name << " control: 0x" << myControl << endl;
	file << name << " output: 0x" << converter.binaryToHex(getOutput()) << endl;

	file.close();
}

//***************************************************************
//* @brief print content to console
void Multiplexor::print()
{

	cout << name << " inputOne: 0x" << converter.binaryToHex(myInput1) << endl;
	cout << name << " inputTwo: 0x" << converter.binaryToHex(myInput2) << endl;
	cout << name << " control: 0x" << myControl << endl;
	cout << name << " output: 0x" << converter.binaryToHex(getOutput()) << endl;
}