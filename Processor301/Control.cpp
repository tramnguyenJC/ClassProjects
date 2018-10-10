#include "Control.h"
#include <string>

//****************************************************************
//* Control()
//* Constructor
//****************************************************************
Control::Control()
{
	//default is nop
	RegDst = 0;
	Jump = 0; //X
	ALUSrc = 0;
	MemtoReg = 0;
	RegWrite = 0;
	MemRead = 0;
	MemWrite = 0;
	Branch = 0;
	ALUOp1 = 0;
	ALUOp0 = 0;

	opcode = "";

}

//****************************************************************
//* Control(Control& control)
//* Copy constructor 
//****************************************************************
Control::Control(Control& control)
{
	RegDst = control.RegDst;
	Jump = control.Jump; //X
	ALUSrc = control.ALUSrc;
	MemtoReg = control.MemtoReg;
	RegWrite = control.RegWrite;
	MemRead = control.MemRead;
	MemWrite = control.MemWrite;
	Branch = control.Branch;
	ALUOp1 = control.ALUOp1;
	ALUOp0 = control.ALUOp0;

	opcode = control.opcode;
}

//****************************************************************
//* ~Control()
//* Destructor
//****************************************************************
Control::~Control()
{}

//****************************************************************
//* setRFormat()
//* This method sets control lines for a R format instruction
//* (arithmetic instructions).
//****************************************************************
void Control::setRformat()
{
	RegDst = 1;
	Jump = 0; //X
	ALUSrc = 0;
	MemtoReg = 0;
	RegWrite = 1;
	MemRead = 0;
	MemWrite = 0;
	Branch = 0;
	ALUOp1 = 1;
	ALUOp0 = 0;
}

//****************************************************************
//* setLW()
//* This method sets control lines for a LW (load word) instruction.
//****************************************************************
void Control::setLW()
{
	RegDst = 0;
	Jump = 0; //X
	ALUSrc = 1;
	MemtoReg = 1;
	RegWrite = 1;
	MemRead = 1;
	MemWrite = 0;
	Branch = 0;
	ALUOp1 = 0;
	ALUOp0 = 0;
}

//****************************************************************
//* setSW()
//* This method sets control lines for a SW (store word) instruction.
//****************************************************************
void Control::setSW()
{
	RegDst = 0; //X
	Jump = 0;//X
	ALUSrc = 1;
	MemtoReg = 1;//X
	RegWrite = 0;
	MemRead = 0;
	MemWrite = 1;
	Branch = 0;
	ALUOp1 = 0;
	ALUOp0 = 0;
}

//****************************************************************
//* setBEQ()
//* This method sets control lines for a BEQ (branch if equal)
//*  instruction.
//****************************************************************
void Control::setBEQ()
{
	RegDst = 0; //X
	Jump = 0; //X
	ALUSrc = 0;
	MemtoReg = 1; //X
	RegWrite = 0;
	MemRead = 0;
	MemWrite = 0;
	Branch = 1;
	ALUOp1 = 0;
	ALUOp0 = 1;
}

//****************************************************************
//* setJ()
//* This method sets control lines for a J (jump) instruction.
//****************************************************************
void Control::setJ()
{
	RegDst = 0; //X
	Jump = 1; //X
	ALUSrc = 0;
	MemtoReg = 0; //X
	RegWrite = 0;
	MemRead = 0;
	MemWrite = 0;
	Branch = 0;
	ALUOp1 = 0;
	ALUOp0 = 0;
}

//****************************************************************
//* setADDI()
//* This method sets control lines for a ADDI (add immediate) instruction.
//****************************************************************
void Control::setADDI()
{
	RegDst = 0; 
	Jump = 0; 
	ALUSrc = 1;
	MemtoReg = 0; 
	RegWrite = 1;
	MemRead = 0;
	MemWrite = 0;
	Branch = 0;
	ALUOp1 = 1;
	ALUOp0 = 0;
}

//****************************************************************
//* inputOpcode(string value)
//* This method sets the opcode of the Control and sets the 
//* appropriate control values for all control lines depending
//* on the type of instruction delineated by the opcode.
//* Preconditions: string value - binary represention of the 
//* opcode to input
//* Postconditions: none
//****************************************************************
void Control::inputOpcode(string value)
{
	opcode = value;

	if (opcode == "000000")
	{
		setRformat();
	}

	if (opcode == "100011")
	{
		setLW();
	}

	if (opcode == "101011")
	{
		setSW();
	}

	if (opcode == "000100")
	{
		setBEQ();
	}

	if (opcode == "000010") // opcode = 2 - from book
	{
		setJ();
	}

	if(opcode == "001000")
	{
		setADDI();
	}
}


//****************************************************************
//* @brief: Print all the control lines data to console
void Control::print(){
	cout << name << " RegDst: " << "0x" << RegDst << endl; 	 //goes to MUX1
	cout << name << " Jump: " << "0x" << Jump << endl;   		 //goes to MUX4
	cout << name << " Branch: " << "0x" << Branch << endl;     //goes to AND and MUX5
	cout << name << " MemRead: " << "0x" << MemRead << endl;   //goes to data memory
	cout << name << " MemToReg: " << "0x" << MemtoReg << endl; //goes to MUX3
	cout << name << " ALUOp1: " << "0x" << ALUOp1 << endl;     //goes to ALU control
	cout << name << " ALUOp0: " << "0x" << ALUOp0 << endl;     //goes to ALU control
	cout << name << " MemWrite: " << "0x" << MemWrite << endl; //goes to data memory
	cout << name << " ALUSrc: " << "0x" << ALUSrc << endl;     //goes to MUX2
	cout << name << " RegWrite: " << "0x" << RegWrite << endl; //goes to Register
}

//***************************************************************
//* @brief print input and output to file
//* @param file1 given file name
void Control::printToFile(string file1)
{
	std::ofstream file;
  	file.open (file1, std::ofstream::out | std::ofstream::app);

	file << name << " RegDst: " << "0x" << RegDst << endl; 	 //goes to MUX1
	file << name << " Jump: " << "0x" << Jump << endl;   		 //goes to MUX4
	file << name << " Branch: " << "0x" << Branch << endl;     //goes to AND and MUX5
	file << name << " MemRead: " << "0x" << MemRead << endl;   //goes to data memory
	file << name << " MemToReg: " << "0x" << MemtoReg << endl; //goes to MUX3
	file << name << " ALUOp1: " << "0x" << ALUOp1 << endl;     //goes to ALU control
	file << name << " ALUOp0: " << "0x" << ALUOp0 << endl;     //goes to ALU control
	file << name << " MemWrite: " << "0x" << MemWrite << endl; //goes to data memory
	file << name << " ALUSrc: " << "0x" << ALUSrc << endl;     //goes to MUX2
	file << name << " RegWrite: " << "0x" << RegWrite << endl; //goes to Register

	file.close();
}

