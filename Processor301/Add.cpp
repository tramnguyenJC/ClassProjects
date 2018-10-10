#include "Add.h"
#include <iostream>

using namespace std;

//***************************************************************
//* @brief Add two given inputs
//* @param input1 given first integer input
//* @param input2 given second integer input
string Add::getOutput()
{
	if (inputOne == "" ){
        //cerr << "inputOne of ALU not set." << endl;
    }

    if (inputTwo == ""){
        //cerr << "inputTwo of ALU not set." << endl;
    }

    if (inputOne == "" && inputTwo == "")
    {
        return "";
    }

    int decimalInputOne = converter.binaryToDecimal(inputOne);
    int decimalInputTwo = converter.binaryToDecimal(inputTwo);
    
    int decimalResult = decimalInputOne + decimalInputTwo;

    string result = converter.decToBin(decimalResult,32);

    return result;
}

//***************************************************************
//* @brief print input and output to file
//* @param file1 given file name
void Add::printToFile(string file1)
{
    std::ofstream file;
    file.open (file1, std::ofstream::out | std::ofstream::app);

    file << name << " inputOne: 0x" << converter.binaryToHex(inputOne) << endl;
    file << name << " inputTwo: 0x" << converter.binaryToHex(inputTwo) << endl;
    file << name << " output: 0x" << converter.binaryToHex(getOutput()) << endl;

    file.close();
}

//***************************************************************
//* @brief print input and output to console
void Add::print()
{
    cout << name << " inputOne: 0x" << converter.binaryToHex(inputOne) << endl;
    cout << name << " inputTwo: 0x" << converter.binaryToHex(inputTwo) << endl;
    cout << name << " output: 0x" << converter.binaryToHex(getOutput()) << endl;
} 
