#include "FileParser.h"
#include <algorithm>
//********************************************************
//* Default Constructor
FileParser::FileParser()
{
    programInput = "";
    memoryInput = "";
    registerInput = "";
    outputMode = "";
    debugMode = "";
    printMemoryContents = "";
    outputFile = "";
    writeToFile = "";

    m_inputFile = "";
}

//********************************************************
//* Copy Constructor
//* @param fileParser: a given FileParser whose values are copied
FileParser::FileParser(FileParser& fileParser)
{
    programInput = fileParser.programInput;
    memoryInput = fileParser.memoryInput;
    registerInput = fileParser.registerInput;
    outputMode = fileParser.outputMode;
    debugMode = fileParser.debugMode;
    printMemoryContents = fileParser.printMemoryContents;
    outputFile = fileParser.outputFile;
    writeToFile = fileParser.writeToFile;

    m_inputFile = fileParser.m_inputFile;
}

//********************************************************
//* Constructor given an inputFile, set corresponding values
//* @param inputFile the name of the given inputFile
FileParser::FileParser(string inputFile)
{
    programInput = "";
    memoryInput = "";
    registerInput = "";
    outputMode = "";
    debugMode = "";
    printMemoryContents = "";
    outputFile = "";
    writeToFile = "";

    this->m_inputFile = inputFile;

    readFile();
}

//********************************************************
//* Destructor
FileParser::~FileParser()
{}

//********************************************************
//* checkFormat(string str)
//* This method checks the format of a given string to see
//* that it matches the correct format of the configuration
//* file
//* @param str: given string
//* return true if format is right, false if there is 
//* space between characters of an address
//********************************************************
bool FileParser::checkFormat(string str)
{
    bool flag = true;
    for(int i = 0; i < str.length() -1; i++){
        if(str[i] == ' ' && flag)
            continue;
        flag = false;
        if(str[i] == ' ' && str[i+1] != ' ')
            return false;
    }
    return true;
}

//***********************************************************
//* readFile()
//* This method reads in a configuration file that specifies all of
//* the parameters for the Processor and saves the values for
//* each parameter to the FileParser. It will exit if it 
//* cannot read from the file or if the format of the file 
//* is wrong. It will ignore any line preceded by "#" and any 
//* whitespace.
//***********************************************************
void FileParser::readFile()
{
    // declare an input-file stream variable for reading
    ifstream inputFile;
    
    // open file and check that it was successfully opened
    inputFile.open( m_inputFile);
    if ( !inputFile.is_open() )
    {
        cerr << "Error: Unable to open file " << m_inputFile << endl;
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
        
        // Extract the param and value (though they might still contain spaces)
        int indexEqualSign = input.find("=");
        string param = input.substr(0, indexEqualSign);
        string value = input.substr(indexEqualSign + 1);

        // Check if format is true. Print out error message and exit
        if(!checkFormat(param) || !checkFormat(value)){
            cerr << "Error: Invalid format: " << input << endl;
            exit(1);
        }

        // Extract all remaining white spaces
        param.erase(std::remove(param.begin(),param.end(), ' '),param.end());
        value.erase(std::remove(value.begin(),value.end(), ' '),value.end());

        // Assign values read to the variables
        if(param == "program_input"){
            programInput = value;
        } else if (param == "memory_contents_input"){
            memoryInput = value;
        } else if (param == "register_file_input"){
            registerInput = value;
        } else if (param == "output_mode"){
            outputMode = value;
        } else if (param == "debug_mode"){
            debugMode = value;
        } else if (param == "print_memory_contents"){
            printMemoryContents = value;
        } else if (param == "output_file"){
            outputFile = value;
        } else if (param == "write_to_file"){
            writeToFile = value;
        }
        

        if ( inputFile.fail() )
        {
            // If the fail flag is set by >>, something unexpected happened:
            //    e.g., wrong data type in file for reading;
            //    e.g., only thing left to read is end-of-file character 
            // If the former, one could (should) print an error message;
            // if the latter, the .eof() method can be used to identify and
            // break out.
            if (inputFile.eof())
            {
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

    if(programInput == "" )
    {
        cerr << "No program input given!" << endl;
        exit(1);
    }

    if(memoryInput == "" )
    {
        cerr << "No memory input given!" << endl;
        exit(1);
    }

    if(registerInput == "" )
    {
        cerr << "No register input given!" << endl;
        exit(1);
    }

    if(outputMode == "" )
    {
        cerr << "No output mode given!" << endl;
        exit(1);

        if (outputMode != "single_step" && outputMode != "batch" )
        {
            cerr << "Output mode must be either single_step or batch!"<< endl;
            exit(1);
        }
    }

    if(debugMode == "")
    {
        cerr << "No debug mode given!" << endl;
        exit(1);

        if(debugMode != "true" && debugMode != "false")
        {
            cerr << "Debug mode must be either true or false!" << endl;
        }
    }

    if(writeToFile == "")
    {
        cerr << "No write to file given!" << endl;
        exit(1);

        if(debugMode != "true" && debugMode != "false")
        {
            cerr << "Write to file must be either true or false!" << endl;
            exit(1);
        }

    }

    if(writeToFile == "true"){
        if(outputFile == ""){
            cerr << "No output file given!" << endl;
            exit(1);
        }
    }

    if(printMemoryContents == "")
    {
        cerr << "No print memory contents given!" << endl;
        exit(1);
        if(printMemoryContents != "true" && printMemoryContents != "false")
            cerr << "Print memory contents must be either true or false!" << endl;
    }

    inputFile.close();

    if (debugMode == "true")
        cout << programInput << " " << memoryInput << " " << registerInput << " " << outputMode << " " << debugMode << " " << printMemoryContents << " " << outputFile << " " << writeToFile << endl;
    
}
