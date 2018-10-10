//****************************************************************
//* This class sets control signals based on the instruction
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Control{
	private:
		int RegDst; //goes to MUX1
		int Jump;   //goes to MUX4
		int Branch; //goes to AND and MUX5
		int MemRead;//goes to data memory
		int MemtoReg;//goes to MUX3
		int ALUOp1;  //goes to ALU control
		int ALUOp0;  //goes to ALU control
		int MemWrite;//goes to data memory
		int ALUSrc;  //goes to MUX2
		int RegWrite;//goes to Register

		string opcode;
		string name;

		void setRformat();
		void setLW();
		void setSW();
		void setBEQ();
		void setJ();
		void setADDI();

	public:
		Control();
		Control(Control& control);
		~Control();

		void print();
		void printToFile(string file1);

		void inputOpcode(string value);
		string getOpcode(){return opcode;}

		void setName(string name){this->name = name;}
		string getName(){return name;}

		int getRegDst(){return RegDst;}
		int getJump(){return Jump;}
		int getBranch(){return Branch;}
		int getMemRead(){return MemRead;}
		int getMemtoReg(){return MemtoReg;}
		int getALUOp1(){return ALUOp1;}
		int getALUOp0(){return ALUOp0;}
		int getMemWrite(){return MemWrite;}
		int getALUSrc(){return ALUSrc;}
		int getRegWrite(){return RegWrite;}
};

