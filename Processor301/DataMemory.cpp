#include "DataMemory.h"
#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

//***************************************************************
//* Default constructor
//***************************************************************
DataMemory::DataMemory()
{}

//***************************************************************
//* Copy Constructor
//* @dm given DataMemory to be copied
DataMemory::DataMemory(DataMemory& dm){
    myMemory = dm.myMemory;
}

//***************************************************************
//* Construct DataMemory based on given Memory
//* @param memory: given Memory
DataMemory::DataMemory(Memory& memory)
{
    myMemory = memory;
}

//***************************************************************
//* ~DataMemory
//* Destructor
//***************************************************************
DataMemory::~DataMemory(){}

//***************************************************************
//* Assumption: address is in binary
//* This method returns the data stored at the given address in 
//* the memory
//* @param address given address to look up
//* @param returns the data stored at that address in memory
//***************************************************************
string DataMemory::readData(string address)
{
	this->address = address;
	string hexAddress = converter.binaryToHex(address);
	readData1 = myMemory.readData(hexAddress);
    return readData1;
}

//***************************************************************
//* assumption: data and address are in binary
//* This method writes the given data into the given address
//* @param data: given data to be written to memory
//* @param address: given address in memory to write to
//***************************************************************
void DataMemory::writeData(string data, string address)
{
	writeData1 = data;
	string hexData = converter.binaryToHex(data);
    string hexAddress = converter.binaryToHex(address);
    myMemory.writeData(hexData, hexAddress);
}

//***************************************************************
//* @brief: print out the content of the data memory to console
void DataMemory::print(){
 	myMemory.print();   
}

void DataMemory::printSystem()
{
	cout << name << " input address: 0x" << converter.binaryToHex(address) << endl;
	cout << name << " writeData: 0x" << converter.binaryToHex(writeData1) << endl;

	cout << name << " readData: 0x" << converter.binaryToHex(readData1) << endl;
}

//***************************************************************
//* @brief print content to file
//* @param file1 given file name
void DataMemory::printToFile(string file1)
{
	myMemory.printToFile(file1);
}

void DataMemory::printSystemToFile(string file1)
{
	std::ofstream file;
  	file.open (file1, std::ofstream::out | std::ofstream::app);

	file << name << " input address: 0x" << converter.binaryToHex(address) << endl;
	file << name << " writeData: 0x" << converter.binaryToHex(writeData1) << endl;

	file << name << " readData: 0x" << converter.binaryToHex(readData1) << endl;

	file.close();
}

//***************************************************************
//* @brief set Name of DataMemory
//* @param name given name
void DataMemory::setName(string name)
{
	this->name = name;
	myMemory.setName(name);
}
