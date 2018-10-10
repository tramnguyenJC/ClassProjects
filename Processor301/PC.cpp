#include "PC.h"

//**************************************************************
//* PC()
//* Constructor sets the address to the beginning memory address
//**************************************************************
PC::PC(){
	//0x00400000 in binary
	myAddress = "00000000010000000000000000000000";
}

//**************************************************************
//* PC(PC& pc)
//* Copy constructor sets the address of the current PC to the
//* address of the given PC
//* Preconditions: the PC to be copied
//**************************************************************
PC::PC(PC& pc){
	myAddress = pc.myAddress;
}
//**************************************************************
//* ~PC()
//* Deconstructor deletes all dynamically allocated data
//**************************************************************
PC::~PC(){}

//**************************************************************
//* getAddress()
//* Returns the address that is currently in the PC
//* Preconditions: none
//* Postconditions: returns the address currently in PC
//**************************************************************
string PC::getAddress(){ 
	return myAddress;
}
//**************************************************************
//* changeAddress(string address)
//* Changes the address in the PC to the given address
//* Precondtions: string address to change the PC's address to
//**************************************************************
void PC::changeAddress(string address){ 
	myAddress = address;
}

//***************************************************************
//* @brief print content to file
//* @param file1 given file name
void PC::printToFile(string file1)
{
	std::ofstream file;
  	file.open (file1, std::ofstream::out | std::ofstream::app);

	file << name << " current address: 0x" << converter.binaryToHex(myAddress) << endl; 

	file.close();
}

//***************************************************************
//* @brief print content to console
void PC::print()
{
	cout << name << " current address: 0x" << converter.binaryToHex(myAddress) << endl; 
}




