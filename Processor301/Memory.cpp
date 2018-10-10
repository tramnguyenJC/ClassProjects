#include "Memory.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;

//***************************************************************
//* Default constructor
//***************************************************************
Memory::Memory(){
    myInputFile = "";
}

//***************************************************************
//* Copy Constructor
//* @param dm Given constructor to be copied
Memory::Memory(Memory& dm){
    myInputFile = dm.myInputFile;
}

//***************************************************************
//* Constructor. Takes in an inputfile, and store the pair of key
//* -values into the Memory object
//* @param _inputFile givenInputFile
Memory::Memory(string _inputFile)
{
    // declare an input-file stream variable for reading
    ifstream inputFile;

    inputFile.open(_inputFile);
    if ( !inputFile.is_open() )
    {
        cerr << "Error: Unable to open file " << _inputFile << endl;
        exit(1);
    }

    while (inputFile.good() )
    {   
        // Read each line
        string input;
        getline(inputFile, input);
        
        // Skip to next line if line is empty or starts with pound sign
        if(input == "")
            continue;
        else if (input[0] == '#')
            continue;

        int indexColon = input.find(":");

        string key = input.substr(0, indexColon);
        string value = input.substr(indexColon + 1);
    
        if(key.substr(0,2) == "0x")
            key = key.substr(2);
        if(value.substr(0,2) == "0x")
            value = value.substr(2);
        myMap.insert(pair<string,string>(key,value));

        if ( inputFile.fail() )
        {
            // If the fail flag is set by >>, something unexpected happened:
            //    e.g., wrong data type in file for reading;
            //    e.g., only thing left to read is end-of-file stringacter 
            // If the former, one could (should) print an error message;
            // if the latter, the .eof() method can be used to identify and
            // break out.
            if (inputFile.eof()){
                // no problem here -- just exit loop and handle results
                break;
            }
            else
            {
                // failed for some other reason (eg. input type mismatch)
                // print a message and exit
                cerr << "Error reading data. " << endl;
                exit(1);
            }
        }
    }
    inputFile.close();
}

//***************************************************************
//* ~Memory
//* Destructor
//***************************************************************
Memory::~Memory(){}

//***************************************************************
//* Read data(string address)
//* This method returns the data stored at the given address in binary
//* @param address: given address to look up
//***************************************************************
string Memory::readData(string address)
{
    if(myMap.find(address) == myMap.end())
        return ""; 
    return converter.hexToBinary(myMap.at(address));
}

//***************************************************************
//* write data(string data, string address)
//* This method writes the given data into the given address
//* @param data: given data to write to memory
//* @param address: given address to look up
//***************************************************************
void Memory::writeData(string data, string address)
{
    myMap[address] = data;
}

//***************************************************************
//* Print out memory to console
void Memory::print(){
    cout << "****************************************************************" << endl;
    cout << "                           " << name << "                       " << endl;
    cout << "****************************************************************" << endl;


    for (std::map<string,string>::iterator it=myMap.begin(); it!=myMap.end(); ++it)
      cout << it->first << ": 0x" << it->second << '\n';
}

//***************************************************************
//* @brief print content to file
//* @param file1 given file name
void Memory::printToFile(string file1)
{
    std::ofstream file;
    file.open (file1, std::ofstream::out | std::ofstream::app);

    file << "****************************************************************" << endl;
    file << "                           " << name << "                       " << endl;
    file << "****************************************************************" << endl;

    for (std::map<string,string>::iterator it=myMap.begin(); it!=myMap.end(); ++it)
      file << it->first << ": 0x" << it->second << '\n';

  file.close();

}