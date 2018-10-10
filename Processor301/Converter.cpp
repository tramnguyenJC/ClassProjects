#include "Converter.h"
#include <cstdlib>

using namespace std;

//***************************************************************
//* Constructor, construct the hex map
//***************************************************************
Converter::Converter(){
    initializeHexMap();
}

Converter::Converter(Converter& dm){
    initializeHexMap();
}

//***************************************************************
//* ~Converter
//* Destructor
//***************************************************************
Converter::~Converter(){}

//***************************************************************
//*@ brief: Initialize hexMap for future conversion between 
//* hexadecimal and binary
void Converter::initializeHexMap(){
    myHexMap.insert(pair<string,string>("0","0000"));
    myHexMap.insert(pair<string,string>("1","0001"));
    myHexMap.insert(pair<string,string>("2","0010"));
    myHexMap.insert(pair<string,string>("3","0011"));
    myHexMap.insert(pair<string,string>("4","0100"));
    myHexMap.insert(pair<string,string>("5","0101"));
    myHexMap.insert(pair<string,string>("6","0110"));
    myHexMap.insert(pair<string,string>("7","0111"));
    myHexMap.insert(pair<string,string>("8","1000"));
    myHexMap.insert(pair<string,string>("9","1001"));
    myHexMap.insert(pair<string,string>("a","1010"));
    myHexMap.insert(pair<string,string>("A","1010"));
    myHexMap.insert(pair<string,string>("b","1011"));
    myHexMap.insert(pair<string,string>("B","1011"));
    myHexMap.insert(pair<string,string>("c","1100"));
    myHexMap.insert(pair<string,string>("C","1100"));
    myHexMap.insert(pair<string,string>("d","1101"));
    myHexMap.insert(pair<string,string>("D","1101"));
    myHexMap.insert(pair<string,string>("e","1110"));
    myHexMap.insert(pair<string,string>("E","1110"));
    myHexMap.insert(pair<string,string>("f","1111"));
    myHexMap.insert(pair<string,string>("F","1111"));

    myHexMap2.insert(pair<string,string>("0000","0")); 
    myHexMap2.insert(pair<string,string>("0001","1"));
    myHexMap2.insert(pair<string,string>("0010","2"));
    myHexMap2.insert(pair<string,string>("0011","3"));
    myHexMap2.insert(pair<string,string>("0100","4"));
    myHexMap2.insert(pair<string,string>("0101","5"));
    myHexMap2.insert(pair<string,string>("0110","6"));
    myHexMap2.insert(pair<string,string>("0111","7"));
    myHexMap2.insert(pair<string,string>("1000","8"));
    myHexMap2.insert(pair<string,string>("1001","9"));
    myHexMap2.insert(pair<string,string>("1010","a"));
    myHexMap2.insert(pair<string,string>("1010","A"));
    myHexMap2.insert(pair<string,string>("1011","b"));
    myHexMap2.insert(pair<string,string>("1011","B"));
    myHexMap2.insert(pair<string,string>("1100","c"));
    myHexMap2.insert(pair<string,string>("1100","C"));
    myHexMap2.insert(pair<string,string>("1101","d"));
    myHexMap2.insert(pair<string,string>("1101","D"));
    myHexMap2.insert(pair<string,string>("1110","e"));
    myHexMap2.insert(pair<string,string>("1110","E"));
    myHexMap2.insert(pair<string,string>("1111","f"));
    myHexMap2.insert(pair<string,string>("1111","F"));
}

//***************************************************************
//* @brief: convert binary to decimal form
//* @param binary: given string in binary form
//* @return string in decimal form
//***************************************************************
int
Converter::binaryToDecimal(string binary) 
{
    int k = 1;
    int val = 0;
    for (int i = binary.length()-1; i>0; i--){
       char c = binary.at(i);
       val = val + k*((int)(c - '0'));
       k = k*2;
    }
    if (binary.at(0) == '-') 
        val = -1*val;     
    else
       val = val + k*((int)(binary.at(0) - '0'));

    return val;
}

//***************************************************************
//* Convert a hexadecimal represent of a string to a binary one
//* @param input given string in hexadecimal form
//* @return string in binary form
//***************************************************************
string Converter::hexToBinary(string input)
{
    string binaryString;
    for(int i = 0; i < input.length(); i++)
    {
        //translating char to string to look up in the string,string map
        string tmp = "";
        tmp += input[i];
        binaryString += myHexMap.at(tmp); 
    }
    return binaryString;
}

//***************************************************************
//* @brief: Convert a given string from binary to its hexadecimal 
//* representation
//* @param instruction: given binary representation of instruction
//* @return hexadecimal representation of instruction
string Converter::binaryToHex(string instruction)
{
    string hexStr = "";
    if(instruction == "") return "";  //@TODO: does this case ever happen?
    string binaryStr = instruction;
    
    if (binaryStr.length() == 32)
    {

    string subStr1 = binaryStr.substr(0,4);
    string subStr2 = binaryStr.substr(4,4);
    string subStr3 = binaryStr.substr(8,4);
    string subStr4 = binaryStr.substr(12,4);
    string subStr5 = binaryStr.substr(16,4);
    string subStr6 = binaryStr.substr(20,4);
    string subStr7 = binaryStr.substr(24,4);
    string subStr8 = binaryStr.substr(28,4);

    string hexSubStr1 = myHexMap2.at(subStr1);
    string hexSubStr2 = myHexMap2.at(subStr2);
    string hexSubStr3 = myHexMap2.at(subStr3);
    string hexSubStr4 = myHexMap2.at(subStr4);
    string hexSubStr5 = myHexMap2.at(subStr5);
    string hexSubStr6 = myHexMap2.at(subStr6);
    string hexSubStr7 = myHexMap2.at(subStr7);
    string hexSubStr8 = myHexMap2.at(subStr8);

    hexStr += hexSubStr1;
    hexStr += hexSubStr2;
    hexStr += hexSubStr3;
    hexStr += hexSubStr4;
    hexStr += hexSubStr5;
    hexStr += hexSubStr6;
    hexStr += hexSubStr7;
    hexStr += hexSubStr8;
}

    if(binaryStr.length() == 4)
    {
        string subStr1 = binaryStr.substr(0,4);
        string hexSubStr1 = myHexMap2.at(subStr1);
        hexStr += hexSubStr1;

    }

    if(binaryStr.length() == 5)
    {
        binaryStr = "000" + binaryStr;
        string subStr1 = binaryStr.substr(0,4);
        string subStr2 = binaryStr.substr(4,4);
        string hexSubStr1 = myHexMap2.at(subStr1);
        string hexSubStr2 = myHexMap2.at(subStr2);
        hexStr += hexSubStr1;
         hexStr += hexSubStr2;
    }

    return hexStr;
}

//****************************************************************
//* Given an integer and the number of bits used to represent it, 
//* returns a string of the binary encoding of the integer.
//* @param i: given integer
//* @param length: number of bits used to represent i
//* @return a string of binary encoding of the integer
string Converter::decToBin( int i, int length )
{
  string bitstring = "";
  bool negative = false;

  // use unsigned int in case the input is negative
  unsigned int val = i;

  // if int is negative, cast it to unsigned to get the proper binary
  if ( i < 0 ){
    negative = true;
    val = (unsigned int) i;
  }
  while ( val > 0){
    // get bit and add 48 to convert to ASCII char
    char ascii_bit = ( val % 2 ) + 48;
    // add bit to the beginning of the string
    bitstring.insert( 0, 1, ascii_bit );
    // move to the next bit
    val = val / 2;
  }
  // if the original int was negative, pad with 1s
  if ( negative )
      return addPaddingBits( bitstring, length, '1' );
  return addPaddingBits( bitstring, length, '0' );
}

//*******************************************************************
//* addPaddingbits(string bitstring, int length, char pad)
//* This method pads a string representing a binary number with the 
//* indicated char pad to the length specified. It pads to the front
//* of the string.
//* Preconditions: string bitstring - a binary string
//* int length - the length to be padded to
//* char pad - the char to pad the bitstring with
//* Postconditions: string representing the padded binary number
//*******************************************************************
string Converter::addPaddingBits( string bitstring, int length, char pad )
{
  // the number of leading bits that need to be added
  int pad_len = length - bitstring.length();

  if ( pad_len > 0 ) {
    // copies the first bit pad_len times at the front of the string
    bitstring.insert( 0, pad_len, pad );
  }

  //if the length of the bitstring is too long, it takes off some of the padding
  if(pad_len < 0 ){
    pad_len = -1 * pad_len;
    bitstring = bitstring.substr(pad_len, length);
  }
  return bitstring;
}