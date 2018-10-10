#include "ALU.h"
#include <string>
#include <iostream>

using namespace std;

//*********************************************************
//* Default ALU Constructor
ALU::ALU()
{
    ALUControl = "";

    inputOne = "";
    inputTwo = "";

    result = "";

    zeroControl = 0;
}

//*********************************************************
//* ALU Copy constructor
//* @param alu The ALU whose data are to be copied
ALU::ALU(ALU& alu)
{
    ALUControl = alu.ALUControl;

    inputOne = alu.inputOne;
    inputTwo = alu.inputTwo;

    result = alu.result;

    zeroControl = alu.zeroControl;
}

//***************************************************************
//* @brief Destructor
ALU::~ALU()
{}

//*********************************************************
//* getResult()
//* This method returns the result of the arithmetic that
//* the ALU object did.
//* Preconditions: none.
//* Postconditions: string representing the result of the 
//* ALU arithmetic
string ALU::getResult()
{
    if (inputOne == "" )
    {
        //cerr << "inputOne of ALU not set." << endl;
        //exit(1);
    }
    if (inputTwo == "")
    {
        //cerr << "inputOne of ALU not set." << endl;
        //exit(1);
    }

    if (inputOne == "" && inputTwo == "")
	return "";

    int decimalInputOne = converter.binaryToDecimal(inputOne);
    int decimalInputTwo = converter.binaryToDecimal(inputTwo);
    
    int decimalResult = 0;

    //addition ADD
    if(ALUControl == "0010")
        decimalResult = decimalInputOne + decimalInputTwo;

    //subtraction SUB 
    //branch if equal BEQ - set the zero control to 1 if it equals zero
    if(ALUControl == "0110"){
       
        decimalResult = (int)decimalInputOne - (int)decimalInputTwo;
        if (decimalResult == 0)
        {
            zeroControl = 1; 
        } else {
            zeroControl = 0;
        }
    }

    //set on less than SLT
    if(ALUControl == "0111")
    {
        decimalResult = decimalInputOne - decimalInputTwo;
        if (decimalResult < 0)
        {
            decimalResult = 1; //set register to 1 if inputOne is less than inputTwo
        } else {
            decimalResult = 0; //set register to 0 if inputOne is equal to or greater than inputTwo
        }
    }

    result = converter.decToBin(decimalResult,32);
    return result;
}

//***************************************************************
//* @brief print input and output to file
//* @param file1 given file name
void ALU::printToFile(string file1)
{
    std::ofstream file;
    file.open (file1, std::ofstream::out | std::ofstream::app);

    file << name << " inputOne: 0x" << converter.binaryToHex(inputOne) << endl;
    file << name << " inputTwo: 0x" << converter.binaryToHex(inputTwo) << endl;
    file << name << " output: 0x" << converter.binaryToHex(getResult()) << endl;
    file << name << " zeroFlag: 0x" << zeroControl << endl;

    file.close();
}

//***************************************************************
//* @brief print input and output to console
void ALU::print()
{
    cout << name << " inputOne: 0x" << converter.binaryToHex(inputOne) << endl;
    cout << name << " inputTwo: 0x" << converter.binaryToHex(inputTwo) << endl;
    cout << name << " output: 0x" << converter.binaryToHex(getResult()) << endl;
    cout << name << " zeroFlag: 0x" << zeroControl << endl;
}
