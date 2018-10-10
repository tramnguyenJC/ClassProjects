#include "Lane.h"
#include "Section.h"
#include "TrafficSimulator.h"

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
	if ( argc < 2 ){
        // print a reasonable usage message
        cerr << "Usage: " << argv[0] << " [input file]" << endl;
        exit(0);
    }

    // load input file into FileParser and read it
	FileParser* fileParser = new FileParser(argv[1]); 
	// create TrafficSimulator according to the parameters establishe in input file
	TrafficSimulator* traffic = new TrafficSimulator(fileParser);
	traffic->run();
	return (0);
}


