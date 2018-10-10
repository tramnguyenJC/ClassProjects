#include "Processor.h"
#include <iostream>


//**************************************************************
//* Default constructor
Processor::Processor()
{}

//**************************************************************
//* Copy constructor
//* @param processor given Processor to be copied
Processor::Processor(Processor& processor)
{}

//**************************************************************
//* Destructor
Processor::~Processor()
{
    delete asmParser;
    delete dataMem;
    delete registerMem;
    delete instructionMemory;
    delete registers;
    delete dataMemory;
}

//**************************************************************
//* Run the processor based on output mode
bool Processor::run(FileParser* fileParser)
{
    this->fileParser = fileParser;

    string outputFile = fileParser->getOutputFile();
    std::ofstream file;
    file.open(outputFile, std::ofstream::out | std::ofstream::trunc);
    file.close();

    //load assembly code into the ASMParser
    asmParser = new ASMParser(fileParser->getProgramInput());

    //construct memory objects with the given memory files
    dataMem = new Memory(fileParser->getMemoryInput());
    registerMem = new Memory(fileParser->getRegisterInput());

    //construct the register file and data memory with their approriate memory
    registers = new RegisterMemory(*registerMem);
    dataMemory = new DataMemory(*dataMem);

    instructionMemory = new InstructionMemory(*asmParser);

    //set names for all components
    pc.setName("PC");
    aluControl.setName("ALUControl");
    signExtender.setName("SignExtender");
    left2Shifter1.setName("Left2Shifter1");
    left2Shifter2.setName("Left2Shifter2");
    multiplexor1.setName("Multiplexor1");
    multiplexor2.setName("Multiplexor2");
    multiplexor3.setName("Multiplexor3");
    multiplexor4.setName("Multiplexor4");
    multiplexor5.setName("Multiplexor5");
    control.setName("Control");
    alu1.setName("ALU1");
    alu2.setName("ALU2");
    alu3.setName("ALU3");
    dataMemory->setName("DataMemory"); //set name of the Memory object
    registers->setName("RegisterFile"); //set name of the Memory object
    instructionMemory->setName("InstructionMemory");

    return run();  
}

//**************************************************************
//* Run the processor in batch mode
//* Execute all instructions sequentially without stopping
bool Processor::run()
{

    if(fileParser->getPrintMemoryContents() == "true")
    {
        if (fileParser->getWriteToFile() == "true")
        {
            string outputFile = fileParser->getOutputFile();
            std::ofstream file;
            file.open (outputFile, std::ofstream::out | std::ofstream::app);
            file << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            file << "                     MEMORY AT THE START                    " << endl;
            file << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            file.close();

        }else{
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "                     MEMORY AT THE START                    " << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        }


        printMemory();
    }
    //***************************************************************************
    //* ALL INSTRUCTIONS
    string currentAddress = pc.getAddress();

    instructionMemory->findInstruction(currentAddress);

    while(instructionMemory->getInstruction() != "end")
    {
        //pauses before each instruction if in single step mode
        if(fileParser->getOutputMode() == "single_step")
        {
            cout << "************************************************************" << endl;
            cout << "Press 'Enter' to continue." << endl;
            cin.get();
            currentAddress = pc.getAddress();
        }

        currentAddress = pc.getAddress();

         //steps to update pc address
        alu1.setInputOne(currentAddress);
        alu1.setInputTwo("0100"); //increment the addresses by 4
        
        instructionMemory->findInstruction(currentAddress);

        string opcode = instructionMemory->getInstruction_31_26();

        control.inputOpcode(opcode);

        if (opcode == "000010") //if instruction is jump instruction continue this way
        {
            runJTYPEpath();
           // break; // jump back to top of loop to get next instruction
        }else if (opcode == "000000") //RTYPE
        {
            runRTYPEpath();
        }else if (opcode == "100011") //LW
        {
            runLWpath();
        }else if (opcode == "101011") //SW
        {
            runSWpath();
        }else if (opcode == "000100") //BEQ
        {   
            runBEQpath();
        }else if (opcode == "001000") //ADDI
        {
            runADDIpath();
        }

        if (instructionMemory->getInstruction() != "end") //don't print the inputs/outputs if we are at end
        {
            printSystem();
        }

       // if(fileParser->getOutputMode() == "single_step")
        {
            //show something to show the process in the terminal
            cout << asmParser->getAssemblyLine(instructionMemory->getInstruction()) << endl; 
            printMemory(); //print memory on every single step if in single_step mode
        }

        //update PC (update happens here with all instructions except JUMP)
        pc.changeAddress(multiplexor4.getOutput());
    }

    if(fileParser->getPrintMemoryContents() == "true")
    {
        if (fileParser->getWriteToFile() == "true")
        {
            string outputFile = fileParser->getOutputFile();
            std::ofstream file;
            file.open (outputFile, std::ofstream::out | std::ofstream::app);
            file << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            file << "                     MEMORY AT THE END                      " << endl;
            file << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            file.close();

        } else {
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "                     MEMORY AT THE END                      " << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        }
        printMemory();
    }

    return true;
}

//**************************************************************
//* Run the J-type instruction
void Processor::runJTYPEpath()
{
    left2Shifter1.inputInstruction(instructionMemory->getInstruction_25_0(), 28);
    string shiftedInstruction = left2Shifter1.getInstruction();

    //(PC + 4) + instruction
    string concatInstruction = alu1.getOutput().substr(0,4) + shiftedInstruction;
    multiplexor4.setInputTwo(concatInstruction);
    multiplexor4.setControl(control.getJump());

    //change the pc address to the calculated target address
    pc.changeAddress(multiplexor4.getOutput());
}

//**************************************************************
//* Run the R-type instruction
void Processor::runRTYPEpath()
{
    string registerOne = instructionMemory->getInstruction_25_21();
    string registerTwo = instructionMemory->getInstruction_20_16();

    string destinationRegister1 = instructionMemory->getInstruction_20_16();
    string destinationRegister2 = instructionMemory->getInstruction_15_11();

    signExtender.inputInstruction(instructionMemory->getInstruction_15_0());

    string extendedInstruction = signExtender.getInstruction(); //goes to multiplexor2

    string functionCode = instructionMemory->getInstruction_5_0(); //goes to ALU control

    multiplexor1.setInputs(destinationRegister1, destinationRegister2);
    multiplexor1.setControl(control.getRegDst()); //output is used when writing to the register

    string writeRegister = multiplexor1.getOutput();

    registers->setRegisterOne(registerOne);
    registers->setRegisterTwo(registerTwo);
    registers->setWriteRegister(writeRegister);

    multiplexor2.setInputs(registers->getRegisterTwoData(), extendedInstruction);
    multiplexor2.setControl(control.getALUSrc());

    alu3.setInputOne(registers->getRegisterOneData());
    alu3.setInputTwo(multiplexor2.getOutput());

    //set the ALU control variables
    aluControl.setALUOp(control.getALUOp1(), control.getALUOp0());
    aluControl.setFunctionCode(functionCode);

    alu3.setALUControl(aluControl.getALUControl());

    string ALUresult = alu3.getResult();

    string dataFromMemory = "";
    
    //WRITE BACK
    multiplexor3.setInputOne(ALUresult);
    multiplexor3.setInputTwo(dataFromMemory);
    multiplexor3.setControl(control.getMemtoReg());

    registers->writeData(multiplexor3.getOutput());

    //setting things up to fetch appropriate next address
    multiplexor5.setInputOne(alu1.getOutput());

    multiplexor5.setControl(0);

    multiplexor4.setInputOne(multiplexor5.getOutput());
    multiplexor4.setControl(control.getJump());
}

//**************************************************************
//* Run the LW-type instruction
void Processor::runLWpath()
{

    string valueToWrite = instructionMemory->getInstruction_25_21();  
    string regFile = instructionMemory->getInstruction_20_16(); // register file to be written to

    multiplexor1.setInputOne(instructionMemory->getInstruction_20_16());
    multiplexor1.setInputTwo(instructionMemory->getInstruction_15_11());
    multiplexor1.setControl(control.getRegDst());

    registers->setWriteRegister(multiplexor1.getOutput());

    registers->setRegisterOne(valueToWrite);
    registers->setRegisterTwo(multiplexor1.getOutput());

    signExtender.inputInstruction(instructionMemory->getInstruction_15_0()); 

    string offset = signExtender.getInstruction(); // gets sign extended 32-bit offset value 
    
    multiplexor2.setInputOne(registers->getRegisterTwoData());
    multiplexor2.setInputTwo(offset);
    multiplexor2.setControl(control.getALUSrc());


    alu3.setInputOne(registers->getRegisterOneData());
    alu3.setInputTwo(multiplexor2.getOutput());

    aluControl.setALUOp(control.getALUOp1(), control.getALUOp0());
    aluControl.setFunctionCode(instructionMemory->getInstruction_5_0());

    alu3.setALUControl(aluControl.getALUControl());

    string memAddress = alu3.getResult(); // computed memory address from ALU 

    string dataFromMemory = dataMemory->readData(memAddress);

    multiplexor3.setInputOne(alu3.getResult());
    multiplexor3.setInputTwo(dataFromMemory);
    multiplexor3.setControl(control.getMemtoReg());


    registers->writeData(multiplexor3.getOutput()); //writes to the write register already specified

    //updating the pc

    multiplexor5.setInputOne(alu1.getOutput());
    
    multiplexor5.setControl(0);

    multiplexor4.setInputOne(multiplexor5.getOutput());
    multiplexor4.setControl(control.getJump());
}

//**************************************************************
//* Run the SW-type instruction
void Processor::runSWpath()
{

    string registerOne = instructionMemory->getInstruction_25_21();
    string registerTwo = instructionMemory->getInstruction_20_16();

    string destinationRegister1 = instructionMemory->getInstruction_20_16();
    string destinationRegister2 = instructionMemory->getInstruction_15_11();

    signExtender.inputInstruction(instructionMemory->getInstruction_15_0());

    string extendedInstruction = signExtender.getInstruction(); //goes to multiplexor2

    string functionCode = instructionMemory->getInstruction_5_0(); //goes to ALU control

    multiplexor1.setInputs(destinationRegister1, destinationRegister2);
    multiplexor1.setControl(control.getRegDst()); //output is used when writing to the register

    string writeRegister = multiplexor1.getOutput();

    registers->setRegisterOne(registerOne);
    registers->setRegisterTwo(registerTwo);
    registers->setWriteRegister(writeRegister);

    multiplexor2.setInputs(registers->getRegisterTwoData(), extendedInstruction);
    multiplexor2.setControl(control.getALUSrc());

    alu3.setInputOne(registers->getRegisterOneData());
    alu3.setInputTwo(multiplexor2.getOutput());

    //set the ALU control variables
    aluControl.setALUOp(control.getALUOp1(), control.getALUOp0());
    aluControl.setFunctionCode(functionCode);

    alu3.setALUControl(aluControl.getALUControl());

    string ALUresult = alu3.getResult(); //memory address to write to

    string dataToWrite = registers->getRegisterTwoData();

    dataMemory->writeData(dataToWrite, ALUresult);

    //updating the pc 

    multiplexor5.setInputOne(alu1.getOutput());
    
    multiplexor5.setControl(0);

    multiplexor4.setInputOne(multiplexor5.getOutput());
    multiplexor4.setControl(control.getJump());
}

//**************************************************************
//* Run the BEQ-type instruction
void Processor::runBEQpath()
{
    string registerOne = instructionMemory->getInstruction_25_21();
    string registerTwo = instructionMemory->getInstruction_20_16();

    registers->setRegisterOne(registerOne);
    registers->setRegisterTwo(registerTwo);
    alu3.setInputOne(registers->getRegisterOneData());
    alu3.setInputTwo(registers->getRegisterTwoData());
    string functionCode = instructionMemory->getInstruction_5_0(); // goes to ALU control
    
    // set the ALU control variables
    aluControl.setALUOp(control.getALUOp1(), control.getALUOp0());
    aluControl.setFunctionCode(functionCode);

    alu3.setALUControl(aluControl.getALUControl());

    string ALUresult = alu3.getResult();

    signExtender.inputInstruction(instructionMemory->getInstruction_15_0());
    string extendedInstruction = signExtender.getInstruction();

    left2Shifter2.inputInstruction(extendedInstruction, 32);

    alu2.setInputOne(alu1.getOutput());
    alu2.setInputTwo(left2Shifter2.getInstruction());
    
    int AND = 0;
    if (control.getBranch() == 1 && alu3.getZero() == 1)
        AND = 1;
    
    multiplexor5.setInputOne(alu1.getOutput());
    multiplexor5.setInputTwo(alu2.getOutput());
    multiplexor5.setControl( AND );

    multiplexor4.setInputOne(multiplexor5.getOutput());
    multiplexor4.setControl(control.getJump()); //should be 0
}

//**************************************************************
//* Run the ADDI-type instruction
void Processor::runADDIpath()
{
    string registerOne = instructionMemory->getInstruction_25_21();
    string registerTwo = instructionMemory->getInstruction_20_16(); // write register
 
    string destinationRegister1 = instructionMemory->getInstruction_20_16();
    string destinationRegister2 = instructionMemory->getInstruction_15_11();
 
    signExtender.inputInstruction(instructionMemory->getInstruction_15_0());
    string extendedInstruction = signExtender.getInstruction(); // immediate goes to multiplexor2

    multiplexor1.setInputs(destinationRegister1, destinationRegister2);
    multiplexor1.setControl(control.getRegDst()); //output is used when writing to the register

    string writeRegister = multiplexor1.getOutput();

    registers->setRegisterOne(registerOne);
    registers->setRegisterTwo(registerTwo);
    registers->setWriteRegister(writeRegister);

    multiplexor2.setInputs(registers->getRegisterTwoData(), extendedInstruction);
    multiplexor2.setControl(control.getALUSrc());

    alu3.setInputOne(registers->getRegisterOneData());
    alu3.setInputTwo(multiplexor2.getOutput());

    alu3.setALUControl("0010");
    string ALUresult = alu3.getResult();

    string dataFromMemory = "";

    //WRITE BACK
    multiplexor3.setInputOne(ALUresult);
    multiplexor3.setInputTwo(dataFromMemory);
    multiplexor3.setControl(control.getMemtoReg());

    registers->writeData(multiplexor3.getOutput());

    //setting things up to fetch appropriate next address
    multiplexor5.setInputOne(alu1.getOutput());
    
    multiplexor5.setControl(0);

    multiplexor4.setInputOne(multiplexor5.getOutput());
    multiplexor4.setControl(control.getJump());
}

//***************************************************************
//* @brief print Memory content
void Processor::printMemory()
{
    if(fileParser->getWriteToFile() == "true")
    {
        //printing to the specified file
        string outputFile = fileParser->getOutputFile();
        registers->printMemoryToFile(outputFile);
        instructionMemory->printToFile(outputFile);
        dataMemory->printToFile(outputFile);
    }else{
        //printing to the terminal
        registers->printMemory();
        instructionMemory->print();
        dataMemory->print();
    }

}

//***************************************************************
//* @brief print System content
void Processor::printSystem()
{
    if(fileParser->getWriteToFile() == "true")
    {
        //printing to the specified file
        string outputFile = fileParser->getOutputFile();

        std::ofstream file;
        file.open (outputFile, std::ofstream::out | std::ofstream::app);
        file << "==================================================================================================================" << endl;
        
        file << asmParser->getAssemblyLine(instructionMemory->getInstruction()) << endl; //print out the current assembly instruction
        file << "------------------------------------------------------------------------------------------------------------------" << endl;

        file.close();

        pc.printToFile(outputFile);
        alu1.printToFile(outputFile);
        multiplexor1.printToFile(outputFile);
        control.printToFile(outputFile);
        registers->printSystemToFile(outputFile);
        signExtender.printToFile(outputFile);
        multiplexor2.printToFile(outputFile);
        aluControl.printToFile(outputFile);
        alu3.printToFile(outputFile);
        dataMemory->printSystemToFile(outputFile);
        left2Shifter1.printToFile(outputFile);
        left2Shifter2.printToFile(outputFile);
        alu2.printToFile(outputFile);
        multiplexor5.printToFile(outputFile);
        multiplexor4.printToFile(outputFile);
        multiplexor3.printToFile(outputFile);

    }else {
        //printing to the terminal

        cout << "==================================================================================================================" << endl;
        
        cout << asmParser->getAssemblyLine(instructionMemory->getInstruction()) << endl; //print out the current assembly instruction
        
        cout << "------------------------------------------------------------------------------------------------------------------" << endl;

        pc.print();
        alu1.print();
        multiplexor1.print();
        control.print();
        registers->printSystem();
        signExtender.print();
        multiplexor2.print();
        aluControl.print();
        alu3.print();
        dataMemory->printSystem();
        left2Shifter1.print();
        left2Shifter2.print();
        alu2.print();
        multiplexor5.print();
        multiplexor4.print();
        multiplexor3.print();
    }
}
