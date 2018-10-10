#ifndef __VEHICLE_H__
#define __VEHICLE_H__

#include "Section.h"
#include "Lane.h"
#include <string>

using namespace std;

class Vehicle {
	private:
		////////////////////////////////////////////////////////////////////////////////////////
		// Private instance variables
		int size;					///< size of car
		Lane* lane;					///< lane car is on
		double turnProb;			///< probability that car turns at intersection
		bool turned = false;		///< true if car has turned at intersection
		bool passedIntersectionOne = false; ///< true if car has gone passed first intersection
		bool turnedLeft = false;	///< true if car turned left
		Section* section;			///< Pointer to the section that head of car occupies
		int myID;					///< ID of the car
		string laneTurned;			///< name of the lane if the car turns into a different lane

		bool goStraight();			///< go straight on the lane
		bool turnRight();			///< turn right at intersection
		bool turnLeft();			///< turn left at intersectio
		bool moveRestOfCar();		///< move the body of the car after the head has moved
		
	public:
		Vehicle();
		Vehicle(Vehicle& vehicle);
		~Vehicle();
		Vehicle(Lane* lane, string typeOfVehicle, double turnProb);

		bool move();

		void setSize(int size){this->size = size;}
		void setLane(Lane* lane){this->lane = lane;}
		void setTurnProb(double turnProb){this->turnProb = turnProb;}
	
		int getSize(){return size;}
		Lane* getLane(){return lane;}
		double getTurnProb(){return turnProb;}

		int getID(){return myID;}
};

#endif