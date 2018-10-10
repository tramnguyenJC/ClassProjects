#include "RegisterMemory.h"
#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

//**************************************************************
//* Default constructor
RegisterMemory::RegisterMemory()
{}

//**************************************************************
//* Copy Constructor
//* @ri RegisterMemory to be copied
RegisterMemory::RegisterMemory(RegisterMemory& ri)
{
	myMemory = ri.myMemory;
}

//**************************************************************
//* Constructor: construct RegisterMemory based on given Memory
RegisterMemory::RegisterMemory(Memory& memory)
{
	myMemory = memory;

}

//**************************************************************
//* Destructor
RegisterMemory::~RegisterMemory(){}

//**************************************************************
//* Retrieve data from a specified registerNum
//* @string registerNum given register
//* @return data stored in that register
string RegisterMemory::getData(string registerNum)
{
	int registerNumDecimal = converter.binaryToDecimal(registerNum);
	string registerNumStr = std::to_string(registerNumDecimal);
	return myMemory.readData(registerNumStr);
}

//**************************************************************
//* Set data stored in the first register
//* @string register1 the given register
void RegisterMemory::setRegisterOne(string register1)
{
	registerOne = register1;

	int registerNumDecimal = converter.binaryToDecimal(registerOne);
	string registerNumStr = std::to_string(registerNumDecimal);
	registerOneData = myMemory.readData(registerNumStr);
}

//**************************************************************
//* Set data stored in the second register
//* @string register2 the given register
void RegisterMemory::setRegisterTwo(string register2)
{
	registerTwo = register2;

	int registerNumDecimal = converter.binaryToDecimal(registerTwo);
	string registerNumStr = std::to_string(registerNumDecimal);
	registerTwoData = myMemory.readData(registerNumStr);
}

//**************************************************************
//* Write data to the write register
//* @param data given data to be written
void RegisterMemory::writeData(string data)
{
	if(writeRegister == "")
	{
		cerr << "No write register specified" << endl;
	}

	int registerNumDecimal = converter.binaryToDecimal(writeRegister); //writeRegister already set earlier
	string registerNumStr = std::to_string(registerNumDecimal);
	string hexDataStr	  = converter.binaryToHex(data);
	myMemory.writeData(hexDataStr, registerNumStr);
}

//**************************************************************
//* Print out the mappings of registers and their contents
void RegisterMemory::printMemory(){
 	
 	myMemory.print();   
}

//***************************************************************
//* @brief print System to console
void RegisterMemory::printSystem()
{
	cout << name << " registerOne: 0x" << converter.binaryToHex(registerOne) << endl;
	cout << name << " registerTwo: 0x" << converter.binaryToHex(registerTwo) << endl;
	cout << name << " writeRegister: 0x" << converter.binaryToHex(writeRegister) << endl;

	cout << name << " registerOneData: 0x" << converter.binaryToHex(registerOneData) << endl;
	cout << name << " registerTwoData: 0x" << converter.binaryToHex(registerTwoData) << endl;

}

//***************************************************************
//* @brief print System content to file
//* @param file1 given file name
void RegisterMemory::printSystemToFile(string file1)
{
	std::ofstream file;
  	file.open (file1, std::ofstream::out | std::ofstream::app);

	file << name << " registerOne: 0x" << converter.binaryToHex(registerOne) << endl;
	file << name << " registerTwo: 0x" << converter.binaryToHex(registerTwo) << endl;
	file << name << " writeRegister: 0x" << converter.binaryToHex(writeRegister) << endl;

	file << name << " registerOneData: 0x" << converter.binaryToHex(registerOneData) << endl;
	file << name << " registerTwoData: 0x" << converter.binaryToHex(registerTwoData) << endl;

	file.close(); 
}

//***************************************************************
//* @brief print  Memory content to file
//* @param file1 given file name
void RegisterMemory::printMemoryToFile(string file1)
{
	myMemory.printToFile(file1);
}

//***************************************************************
//* @brief set Name of Memory
//* @param name given name
void RegisterMemory::setName(string name)
{
	this->name = name;
	myMemory.setName(name);
}
