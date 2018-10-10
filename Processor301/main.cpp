#include "Processor.h"

using namespace std;

int main(int argc, char* argv[]){
	
    
    if ( argc < 2 )
    {
        // print a reasonable usage message
        cerr << "Usage: " << argv[0] << " [input file]" << endl;
        exit(0);
    }

    //construct the FileParser to read in the configuration file
    FileParser* fileParser = new FileParser(argv[1]); 
    Processor processor;
    processor.run(fileParser);

    delete fileParser;
	return(0);
}
