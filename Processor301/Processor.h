//**************************************************************
//* This class is a masterpiece...
//* This class joins different components to execute MIPS instructions
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "FileParser.h"
#include "PC.h"
#include "InstructionMemory.h"
#include "SignExtender.h"
#include "Left2Shifter.h"
#include "Multiplexor.h"
#include "Control.h"
#include "ALU.h"
#include "RegisterMemory.h"
#include "ALUControl.h"
#include "DataMemory.h"
#include "Memory.h"
#include "Add.h"
#include <string>

class Processor{
	private:

		FileParser* fileParser;
		PC pc;
		ALUControl aluControl;
		ASMParser* asmParser;
		Memory* dataMem;
		Memory* registerMem;
		InstructionMemory* instructionMemory;
		RegisterMemory* registers;
		DataMemory* dataMemory;
		SignExtender signExtender;
		Left2Shifter left2Shifter1;
		Left2Shifter left2Shifter2;
		Multiplexor multiplexor1;
		Multiplexor multiplexor2;
		Multiplexor multiplexor3;
		Multiplexor multiplexor4;
		Multiplexor multiplexor5;
		Control control;
		Add alu1;
		Add alu2;
		ALU alu3;
		Converter converter;

		void printMemory();
		void printSystem(); // inputs and outputs

		void runJTYPEpath();
		void runRTYPEpath();
		void runLWpath();
		void runSWpath();
		void runBEQpath();
		void runADDIpath();

		void fetch();
		void decode();
		void execute();
		void memory();
		void writeBack();

		bool run();





	public:
		Processor();
		Processor(Processor& processor);
		~Processor();

		bool run(FileParser* fileParser);

		

};