#include "Instruction.h"

//***************************************************************
//* Default constructor
Instruction::Instruction(){
  myOpcode = UNDEFINED;
  myRS = myRT = myRD = NumRegisters;
}

//***************************************************************
//* Constructor, specify all the fields to initialize the Instruction
//* @param op: given Opcode
//* @param rs: given rSrc register
//* @param rt: given rt register
//* @param rd: given rDes register
//* @param imm: given immediate fields
Instruction::Instruction(Opcode op, Register rs, Register rt, Register rd, int imm)
{
  setValues(op, rs, rt, rd, imm);
}

//***************************************************************
//* Specify all the fields of the Instruction
//* @param op: given Opcode
//* @param rs: given rSrc register
//* @param rt: given rt register
//* @param rd: given rDes register
//* @param imm: given immediate fields
void Instruction::setValues(Opcode op, Register rs, Register rt, Register rd, int imm)
{

  myOpcode = op;
  if(op < 0 || op >= UNDEFINED)
    myOpcode = UNDEFINED;

  myRS = rs;
  if(rs < 0 || rs >= NumRegisters)
    myRS = NumRegisters;

  myRT = rt;
  if(rt < 0 || rt >= NumRegisters)
    myRT = NumRegisters;

  myRD = rd;
  if(rd < 0 || rd >= NumRegisters)
    myRD = NumRegisters;

  myImmediate = imm;
}

//***************************************************************
//* Get a string representation of the instruction
//* @return the string representation of the instruction
string Instruction::getString()
{
  stringstream s ;
  s << "OP: \t" << myOpcode << "\t" << "RD: " << myRD << "\t" << 
    "RS: " << myRS << "\t" << "RT: " << "\t" << myRT << "\t" <<
    "Imm: " << myImmediate;
  
  return s.str(); 
}

