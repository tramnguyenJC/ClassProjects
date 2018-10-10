#include "InstructionMemory.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

//***************************************************************
//* Default Constructor
InstructionMemory::InstructionMemory(){
	myInstruction = "";
}

//***************************************************************
//* Copy Constructor
//* @param im: given InstructionMemory to be copied
InstructionMemory::InstructionMemory(InstructionMemory& im)
{
	myInstruction = im.myInstruction;
    myParser = im.myParser;
}

//***************************************************************
//* InstructionMemory(ASMParser& parser)
//* This constructor accepts an ASMParser that parses input data
//* into the InstructionMemory object
//***************************************************************
InstructionMemory::InstructionMemory(ASMParser& parser){
    if(!parser.isFormatCorrect()){
        //@TODO: Check new format requirements of input file program1.asm
        cerr << "Format of input file is incorrect " << endl;
        exit(1);
    }
    //#for starting address 0x400000
    string address = "00000000010000000000000000000000";
    Instruction i;
    //Iterate through instructions, printing each encoding.
    i = parser.getNextInstruction();
    while(i.getOpcode() != UNDEFINED){
        myMap.insert(pair<string,string>(address,i.getEncoding()));
        int decAddress = converter.binaryToDecimal(address);
        decAddress += 4;
        address = converter.decToBin(decAddress, 32);
        i = parser.getNextInstruction();
    }
    //insert end to signal the end of the code
    myMap.insert(pair<string,string>(address,"end"));
}

//***************************************************************
//* @brief Print out contents of the instruction memory
//***************************************************************
void InstructionMemory::print(){ 
    cout << "****************************************************************" << endl;
    cout << "                           " << name << "                       " << endl;
    cout << "****************************************************************" << endl;

    for(auto it = myMap.cbegin(); it != myMap.cend(); ++it)
    {
        cout << "[" << converter.binaryToHex((*it).first) << ": 0x" << converter.binaryToHex((*it).second) << "]" << endl;
    }
}

//***************************************************************
//* @brief print content to file
//* @param file1 given file name
void InstructionMemory::printToFile(string file1)
{
    std::ofstream file(file1, std::ios_base::out | std::ios_base::app);

    file << "****************************************************************" << endl;
    file << "                         " << name << "                         " << endl;
    file << "****************************************************************" << endl;

    for(auto it = myMap.cbegin(); it != myMap.cend(); ++it)
    {
        file << "[" << converter.binaryToHex((*it).first) << ": 0x" << converter.binaryToHex((*it).second) << "]" << endl;
    }
    
    file.close();
}

//***************************************************************
//* ~InstructionMemory
//* Destructor
//***************************************************************
InstructionMemory::~InstructionMemory(){}

//***************************************************************
//* findInstruction(string address) (assumption: In binary)
//* This method finds the instruction at the given address and 
//* saves the instruction in the InstructionMemory object
//* @param address: given string address
//***************************************************************
void InstructionMemory::findInstruction(string address)
{  
    try{
    myInstruction = myMap.at(address);
    } catch (std::out_of_range& oor)
    {
        cerr << "ERROR!" << endl;
        cerr << "The address specified does not exist." << endl;
        cerr << "Address specified: 0x" << converter.binaryToHex(address) << endl;
      //  cerr << "Assembly line with error: " << myParser->getAssemblyLine(address) << endl;
        exit(1);
    }

}

//***************************************************************
//* getInstruction_25_0()
//* This method returns the 25-0 bits of the binary representation
//* of the instruction currently in the InstructionMemory
//***************************************************************   
string InstructionMemory::getInstruction_25_0(){
    string subString = myInstruction.substr(6, 26);
    return subString;
}

//***************************************************************
//* getInstruction_31_26()
//* This method returns the 31-26 bits of the binary representation
//* of the instruction currently in the InstructionMemory
//***************************************************************	
string InstructionMemory::getInstruction_31_26()
{
	string subString = myInstruction.substr(0, 6);
    return subString;
}

//***************************************************************
//* getInstruction_25_21()
//* This method returns the 25-21 bits of the binary representation
//* of the instruction currently in the InstructionMemory
//***************************************************************	
string InstructionMemory::getInstruction_25_21()
{
    string subString = myInstruction.substr(6, 5);
	return subString;
}

//***************************************************************
//* getInstruction_20_16()
//* This method returns the 20-16 bits of the binary representation
//* of the instruction currently in the InstructionMemory
//***************************************************************	
string InstructionMemory::getInstruction_20_16()
{
    string subString = myInstruction.substr(11, 5);
	return subString;
}

//***************************************************************
//* getInstruction_15_11()
//* This method returns the 15-11 bits of the binary representation
//* of the instruction currently in the InstructionMemory
//***************************************************************	
string InstructionMemory::getInstruction_15_11()
{
    string subString = myInstruction.substr(16, 5);
	return subString;
}

//***************************************************************
//* getInstruction_15_0()
//* This method returns the 15-0 bits of the binary representation
//* of the instruction currently in the InstructionMemory
//***************************************************************	
string InstructionMemory::getInstruction_15_0()
{
    string subString = myInstruction.substr(16, 16);
	return subString;
}

//***************************************************************
//* getInstruction_5_0()
//* This method returns the 5-0 bits of the binary representation
//* of the instruction currently in the InstructionMemory
//***************************************************************	
string InstructionMemory::getInstruction_5_0()
{
    string subString = myInstruction.substr(26, 6);
	return subString;
}