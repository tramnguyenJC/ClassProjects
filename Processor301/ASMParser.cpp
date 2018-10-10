#include "ASMParser.h"
#include <algorithm>
//**********************************************************************
//* @brief: Default constructor
ASMParser::ASMParser(){}

//**********************************************************************
//* @brief: Constructor. COnstruct an ASMParser based on inputs from a file
//* @param fileName: name of the given file input
ASMParser::ASMParser(string filename){
  // Specify a text file containing MIPS assembly instructions. Function
  // checks syntactic correctness of file and creates a list of Instructions.
  Instruction i;
  myFormatCorrect = true;

  myLabelAddress = 0x400000;

  ifstream in;
  in.open(filename.c_str());
  if(in.bad()){
    myFormatCorrect = false;
  }
  else{
    string line; 

    while(getline(in, line)){
      string temp = removeSpaces(line);
       //check if the line is a comment
      if(temp == ""){
	continue;
      }
      if( temp.at(0) == '#')
      {
        continue;
      }
      string opcode("");
      string operand[80];
      int operand_count = 0;
      getTokens(line, opcode, operand, operand_count);

      if(opcode.length() == 0 && operand_count != 0){
        // No opcode but operands
        myFormatCorrect = false;
        break;
      }

      Opcode o = opcodes.getOpcode(opcode);      
      if(o == UNDEFINED){
      // invalid opcode specified
        myFormatCorrect = false;
        break;
      }

      bool success = getOperands(i, o, operand, operand_count);
      if(!success){
        myFormatCorrect = false;
        break;
      }

      string encoding = encode(i);
      i.setEncoding(encoding);

      //map out the encoding to the assembly line that it was encoded from

      myMap.insert(pair<string,string>(encoding,line)); //key is the binary encoding and the line is the value

      myInstructions.push_back(i);
    }
  }

  myIndex = 0;
}


Instruction ASMParser::getNextInstruction()
  // Iterator that returns the next Instruction in the list of Instructions.
{
  if(myIndex < (int)(myInstructions.size())){
    myIndex++;
    return myInstructions[myIndex-1];
  }
  
  Instruction i;
  return i;
}

//**********************************************************************
//* @brief: Decomposes a line of assembly code into strings for the opcode 
//* field and operands, checking for syntax errors and counting the 
//* number of operands.
//* @param line: line of assembly code
//* @param opcode: given opcode
//* @param operand: given operand
//* @param numOperands: given number of operands
void ASMParser::getTokens(string line,
  string &opcode,
  string *operand,
  int &numOperands)
{
    // locate the start of a comment
  string::size_type idx = line.find('#');
  if (idx != string::npos) // found a ';'
    line = line.substr(0,idx);
  int len = line.length();
  opcode = "";
  numOperands = 0;

  if (len == 0) return;
  int p = 0; // position in line

  // line.at(p) is whitespace or p >= len
  while (p < len && isWhitespace(line.at(p)))
    p++;
  // opcode starts
  while (p < len && !isWhitespace(line.at(p))){
    opcode = opcode + line.at(p);
    p++;
  }
  // for(int i = 0; i < 3; i++){
  int i = 0;
  while(p < len){
    while ( p < len && isWhitespace(line.at(p)))
      p++;
    // operand may start
    bool flag = false;
    while (p < len && !isWhitespace(line.at(p)))
    {
      if(line.at(p) != ','){
        operand[i] = operand[i] + line.at(p);
        flag = true;
        p++;
      }
      else{
        p++;
        break;
      }
    }
    if(flag == true){
      numOperands++;
    }
    i++;
  }


  idx = operand[numOperands-1].find('(');
  string::size_type idx2 = operand[numOperands-1].find(')');

  if (idx == string::npos || idx2 == string::npos ||
    ((idx2 - idx) < 2 )){ // no () found
  }
  else{ // split string
    string offset = operand[numOperands-1].substr(0,idx);
    string regStr = operand[numOperands-1].substr(idx+1, idx2-idx-1);
      
    operand[numOperands-1] = offset;
    operand[numOperands] = regStr;
    numOperands++;
  }

  // ignore anything after the whitespace after the operand
  // We could do a further look and generate an error message
  // but we'll save that for later.
  return;
}

bool ASMParser::isNumberString(string s)
  // Returns true if s represents a valid decimal integer
{
  int len = s.length();
  if (len == 0) return false;
  if ((isSign(s.at(0)) && len > 1) || isDigit(s.at(0))){
  // check remaining characters
    for (int i=1; i < len; i++){
      if (!isdigit(s.at(i))) return false;
    }
    return true;
  }
  return false;
}

//****************************************************************
//* Convert a numeric string to an integer.
//* @param s: given string
//* @return a corresponding integer representation of given numeric
//* string
int ASMParser::cvtNumString2Number(string s)
{
  if (!isNumberString(s)){
    cerr << "Non-numberic string passed to cvtNumString2Number"
    << endl;
    return 0;
  }
  int k = 1;
  int val = 0;
  for (int i = s.length()-1; i>0; i--)
  {
    char c = s.at(i);
    val = val + k*((int)(c - '0'));
    k = k*10;
  }
  if (isSign(s.at(0))){
    if (s.at(0) == '-') 
      val = -1*val;
  }
  else
    val = val + k*((int)(s.at(0) - '0'));
  
  return val;
}

//****************************************************************
//* @brief Given an Opcode, a string representing the operands, and
//* the number of operands, breaks operands apart and stores fields 
//* into Instruction.
//* @param i given Instruction
//* @param o given Opcode
//* @param operand given Operand
//* @param operand_count number of operands
//* @return true if stored fields successfully, false otherwise
bool ASMParser::getOperands(Instruction &i, Opcode o, 
  string *operand, int operand_count)
{
  if(operand_count != opcodes.numOperands(o))
    return false;

  int rs, rt, rd, imm;
  imm = 0;
  rs = rt = rd = NumRegisters;

  int rs_p = opcodes.RSposition(o);
  int rt_p = opcodes.RTposition(o);
  int rd_p = opcodes.RDposition(o);
  int imm_p = opcodes.IMMposition(o);

  if(rs_p != -1){
    rs = registers.getNum(operand[rs_p]);
    if(rs == NumRegisters)
      return false;
  }

  if(rt_p != -1){
    rt = registers.getNum(operand[rt_p]);
    if(rt == NumRegisters)
      return false;
  }
  
  if(rd_p != -1){
    rd = registers.getNum(operand[rd_p]);
    if(rd == NumRegisters)
      return false;
  }

  if(imm_p != -1){
    if(isNumberString(operand[imm_p])){  // does it have a numeric immediate field?
      imm = cvtNumString2Number(operand[imm_p]);
      if(((abs(imm) & 0xFFFF0000)<<1))  // too big a number to fit
        return false;
    }
    else{ 
      if(opcodes.isIMMLabel(o)){  // Can the operand be a label?
        // Assign the immediate field an address
        string address = operand[imm_p].substr(2); // Take out the 0x
        imm = converter.binaryToDecimal(converter.hexToBinary(address));
      }
      else  // There is an error
        return false;
    }
  }
  i.setValues(o, rs, rt, rd, imm);
  return true;
}

//****************************************************************
//* @brief Given an instruction, returns the 32bits MIPS binary
//* encoding of the instruction.
//* @param i given Instruction
//* @return binary encoding of the instruction
string ASMParser::encode(Instruction i)
{
  Opcode op = i.getOpcode();

  // encode instruction based on its type
  if ( opcodes.getInstType( op ) == RTYPE )
    return encodeRTYPE(i);
  else if ( opcodes.getInstType( op ) == ITYPE )
    return encodeITYPE(i);
  else if ( opcodes.getInstType( op ) == JTYPE )
    return encodeJTYPE(i);
  return "";
}


//****************************************************************
//* @brief Given a R-type instruction, returns the binary encoding
//* of the instruction.
//* @param i given Instruction
//* @return binary encoding of R-type instruction
string ASMParser::encodeRTYPE( Instruction i )
{
  // get binary encoding of opcode and funct fields
  string op = opcodes.getOpcodeField( i.getOpcode() );
  string funct = opcodes.getFunctField( i.getOpcode() );

  // get binary encodings of each register field
  string rs = converter.decToBin( i.getRS(), 5 );
  string rd = converter.decToBin( i.getRD(), 5 );
  string rt = converter.decToBin( i.getRT(), 5 );

  string shamt = "";

  if(funct == "" ) //addi so immediate needs to be 16 bits long
    shamt = converter.decToBin( i.getImmediate(), 16 );
  else //not addi so shamt is 5 bits
    shamt = converter.decToBin( i.getImmediate(), 5 );
    // return final encoding by concatenating fields
  return op + rs + rt + rd + shamt + funct;
}

//****************************************************************
//* @brief Given an I-type instruction, returns the binary encoding
//* of the instruction.
//* @param i given Instruction
//* @return binary encoding of I-type instruction
string ASMParser::encodeITYPE( Instruction i )
{
  // get binary encoding of opcode
  string op = opcodes.getOpcodeField( i.getOpcode() );

  // get rs & rt, convert to binary, and extend to 5 bits
  string rs = converter.decToBin( i.getRS(), 5 );
  string rt = converter.decToBin( i.getRT(), 5 );

  // get immediate value, convert to binary, and extend to 16 bits
  string imm = converter.decToBin( i.getImmediate(), 16 );

  // final encoding is concatenation of opcode, rs, rt, immediate value in that order
  return op + rs + rt + imm;
}

//****************************************************************
//* @brief Given a J-type instruction, returns the binary encoding
//* of the instruction.
//* @param i given Instruction
//* @return binary encoding of J-type instruction
string ASMParser::encodeJTYPE( Instruction i )
{
  // get the binary string of the op field
  string op = opcodes.getOpcodeField( i.getOpcode() );

  // get the address that the instruction is jumping to
  int target_int = i.getImmediate();


  // get binary encoding of target address and extend to 26 bits
  // shift address two bits right to ensure it encodes the right address
  string target = converter.decToBin( target_int / 4, 26 );

  // final encoding is op field concatenated with binary encoding of target address
  return op + target;
}

string ASMParser::getAssemblyLine(string encoding)
{
  if(myMap.find(encoding) == myMap.end())
        return ""; 

  return myMap.at(encoding);
}

string ASMParser::removeSpaces(string input)
{
  input.erase(std::remove(input.begin(),input.end(),' '),input.end());
  return input;
}
