#ifndef __TRAFFICSIMULATOR_H__
#define __TRAFFICSIMULATOR_H__

#include "Lane.h"

#include "Vehicle.h"
#include "Section.h"
#include "TrafficLight.h"
#include "FileParser.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;


class TrafficSimulator{
	private:
		Section* northWest;				//< Intersection between lane NS and EW
		Section* northEast; 			//< Intersection between lane SN and EW
		Section* southWest;				//< Intersection between lane NS and WE
		Section* southEast;				//< Intersection between lane SN and WE

		Lane* laneWE; 					//< Lane from west to east
		Lane* laneEW;					//< Lane from east to west
		Lane* laneNS; 					//< Lane from north to south
		Lane* laneSN;					//< Lane from south to north
		
		TrafficLight* trafficLightWE;	///< traffic light the WE Lane owns
		TrafficLight* trafficLightEW;	///< traffic light the EW Lane owns
		TrafficLight* trafficLightNS;	///< traffic light the NS Lane owns
		TrafficLight* trafficLightSN;	///< traffic light the SN Lane owns

		double newVehicleProb;			///< probability new car is generated

		double carProb;					///< probability car generated is a car
		double SUVProb;					///< probability car generated is a SUV
		double truckProb;				///< probability car generated is a truck

		double NSProb;					///< probability car is generated at NS Lane 
		double SNProb;					///< probability car is generated at SN Lane 
		double WEProb;					///< probability car is generated at We Lane 
		double EWProb;					///< probability car is generated at EW Lane 
		int timeGreen;					///< the time traffic light is green
		int timeYellow;					///< the time traffic light is yellow

		int NSlaneLength;				///< the length of NSlane
		int WElaneLength;				///< the length of WELane
		int numIterations;				///< Number of iterations simulation supposed to run in

		vector<Vehicle*> vehicles;		///< Vectors of vehicles

		int clock;						///< Clock to keep track of simulation time steps

		bool printInfo;					///< True if we print out info for debugging

		bool single_step;				///< True if we print out simulation step-by-step

		void setIntersections();		

		void printNorth();
		void printWE();
		void printEW();
		void printSouth();

		bool spawnVehicle();
		void updateTrafficLights();

		string spacer(int vehicleID, string item);

	public:
		TrafficSimulator();
		TrafficSimulator(TrafficSimulator& trafficSimulator);
		~TrafficSimulator();

		TrafficSimulator(FileParser* fileParser); // later use a file to parse impt info

		bool run();
		void printSystem();


};
#endif