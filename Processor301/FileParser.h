#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

class FileParser{
private:
	string programInput;
    string memoryInput;
    string registerInput;
    string outputMode;
    string debugMode;
    string printMemoryContents;
    string outputFile;
    string writeToFile;

    string m_inputFile;

    bool checkFormat(string str);

public:

	FileParser();
	FileParser(FileParser& fileParser);
	FileParser(string inputFile);

	~FileParser();

	void readFile();


	string getProgramInput(){return programInput;}
	string getMemoryInput(){return memoryInput;}
	string getRegisterInput(){return registerInput;}
	string getOutputMode(){return outputMode;}
	string getDebugMode(){return debugMode;}
	string getPrintMemoryContents(){return printMemoryContents;}
	string getOutputFile(){return outputFile;}
	string getWriteToFile(){return writeToFile;}

	string getInputFile(){return m_inputFile;}
};