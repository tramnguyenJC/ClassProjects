#include "FileParser.h"
#include <algorithm>
//********************************************************
//* Default Constructor
FileParser::FileParser()
{
    m_inputFile = "";
}

//********************************************************
//* Copy Constructor
//* @param fileParser: a given FileParser whose values are copied
FileParser::FileParser(FileParser& fileParser)
{
    m_inputFile = fileParser.m_inputFile;
}

//********************************************************
//* Constructor given an inputFile, set corresponding values
//* @param inputFile the name of the given inputFile
FileParser::FileParser(string inputFile)
{
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
//* the parameters and saves the values for
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

        param.erase(std::remove(param.begin(),param.end(), ' '),param.end());
        value.erase(std::remove(value.begin(),value.end(), ' '),value.end());

        int indexPoundSign = value.find("#");
       // if (indexPoundSign != "npos")
        value = value.substr(0, indexPoundSign);

        cout << "param: " << param << " value: " << value << endl;

        // Check if format is true. Print out error message and exit
        if(!checkFormat(param) || !checkFormat(value)){
            cerr << "Error: Invalid format: " << input << endl;
            exit(1);
        }

        // Extract all remaining white spaces
        //param.erase(std::remove(param.begin(),param.end(), ' '),param.end());
        //value.erase(std::remove(value.begin(),value.end(), ' '),value.end());

        // Assign values read to the variables
        if(param == "NS_lane_length"){
            NS_lane_length = stoi(value);
        } else if (param == "WE_lane_length"){
            WE_lane_length = stoi(value);
        } else if (param == "new_vehicle_prob"){
            new_vehicle_prob = stod(value);
        } else if (param == "car_prob"){
            car_prob = stod(value);
        } else if (param == "SUV_prob"){
            SUV_prob = stod(value);
        } else if (param == "truck_prob"){
            truck_prob = stod(value);
        } else if (param == "southbound_prob"){
            southbound_prob = stod(value);
        } else if (param == "northbound_prob"){
            northbound_prob = stod(value);
        } else if (param == "westbound_prob"){
            westbound_prob = stod(value);
        } else if (param == "eastbound_prob"){
            eastbound_prob = stod(value);
        } else if (param == "time_green"){
            time_green = stoi(value);
        } else if (param == "time_yellow"){
            time_yellow = stoi(value);
        } else if (param == "num_iterations"){
            num_iterations = stoi(value);
        } else if (param == "print_info"){
            print_info = toBoolean(value);
        } else if (param == "single_step"){
            single_step = toBoolean(value);
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

    inputFile.close();
}

bool FileParser::toBoolean(string str){
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    std::istringstream is(str);
    bool b;
    is >> std::boolalpha >> b;
    return b;
}
