#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>

using namespace std;

class FileParser{
private:
	int NS_lane_length;
    int WE_lane_length;
    double new_vehicle_prob;
    double car_prob;
    double SUV_prob;
    double truck_prob;
    double southbound_prob;
    double northbound_prob;
    double westbound_prob;
    double eastbound_prob;
    int time_yellow;
    int time_green;
    int num_iterations;

    bool print_info;
    bool single_step;


    string m_inputFile;

    bool checkFormat(string str);
    bool toBoolean(string str);

public:

	FileParser();
	FileParser(FileParser& fileParser);
	FileParser(string inputFile);

	~FileParser();

	void readFile();

	string getInputFile(){return m_inputFile;}

	int getNSlaneLength(){return NS_lane_length;}
	int getWElaneLength(){return WE_lane_length;}
	double getNewVehicleProb(){return new_vehicle_prob;}
	double getCarProb(){return car_prob;}
	double getSUVProb(){return SUV_prob;}
	double getTruckProb(){return truck_prob;}
	double getSNProb(){return southbound_prob;}
	double getNSProb(){return northbound_prob;}
	double getEWProb(){return westbound_prob;}
	double getWEProb(){return eastbound_prob;}
	int getTimeGreen(){return time_green;}
	int getTimeYellow(){return time_yellow;}

	int getNumIterations(){return num_iterations;}
	bool getPrintInfo(){return print_info;}
	bool getSingleStep(){return single_step;}

};