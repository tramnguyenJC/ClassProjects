#include "Vehicle.h"
//#include "Lane.h"
#include <iostream>

static int id = 1;

//***************************************************************
//* @brief Default Constructor, initialize all member variables
Vehicle::Vehicle()
{
	size = 0;
	turnProb = 0.0;
}

//***************************************************************
//* @brief Copy Constructor
//* @param vehicle: Given Vehicle to be copied
Vehicle::Vehicle(Vehicle& vehicle)
{
	size = vehicle.size;
	lane = vehicle.lane;
	turnProb = vehicle.turnProb;
}

//***************************************************************
//* @brief Destructor
Vehicle::~Vehicle()
{}

//***************************************************************
//* @brief Constructor
//* @param lane: given Lane pointer that the vehicle is on
//* @param typeOfVehicle: a string specifying the type
//* @param turnProb vehicle's probability of turning
Vehicle::Vehicle(Lane* lane, string typeOfVehicle, double turnProb)
{
	// Assign size of vehicle
	if(typeOfVehicle == "CAR")
		size = 2;
	else if (typeOfVehicle == "SUV")
		size = 3;
	else if(typeOfVehicle == "TRUCK")
		size = 4;
	else
		cerr << "Type of vehicle specified is not supported. Select 'CAR', 'SUV', or 'TRUCK'." << endl;

	myID = id;
	id++;
	this->lane = lane;
	laneTurned = lane->getName();
	section = lane->getLaneStart();
	section->fillSection(myID); 
	this->turnProb = turnProb;
}

//***************************************************************
//* @brief Move car forward, or turn car at intersection appropriately
//*		   Does not allow U-turns.
//* @return true if move successfully
bool Vehicle::move(){
	bool moved = false;

	// Move the head of the car forward, or left or right (if car is at intersection)
	// if the next section is not occupied. If the head of the car (signified by the
	// member variable Section*) has moved, bool moved is set to true, and the rest
	// of the car (that currently occupied other sections) also move one step forward
	if(section->isIntersection()){
		// generate random number for determining whether car turns
		double randTurn = (double)rand() / RAND_MAX;
		// If car has turned, or if number is in probability range of 1 - p
		// then go straight
		if(randTurn > turnProb || turned)
			moved = goStraight();
		else {
			// Has to turn left if car turns on the second intersection
			if(passedIntersectionOne){
				turnedLeft = true;
				moved = turnLeft();
			}
			else {
				// Has to turn right if car turns on the first intersection
				moved = turnRight();
			}
		}
		// Passed the first intersection, set to true;
		passedIntersectionOne = true;
	}
	// if car is not at intersection, just move straight
	else{
		moved = goStraight();
	}

	// if car has moved up one section (straight/left/right), fill up previous 
	// sections depending on size of car and free one section.
	// If car did not move, then all the sections meant to be occupied are still
	// occupied as from the last iteration of move()
	if(moved)
		moveRestOfCar();
	return true;
}


//***************************************************************
//* @brief If car moved, move the rest of the car accordingly,
//* and free up one section that car has moved out of.
bool Vehicle::moveRestOfCar(){
	Section* temp = section;

	// If the head of the car has turned left or right instead of going straight
	if(turned){
		int i = 0;
		// Fill up all previous sections until we reach the vehicle's size or
		// we reach the intersection (turning point)
		while(i < size - 1 && !temp->isIntersection()){
			if (temp == 0) break;
			temp = temp->getPrevious();
			temp->fillSection(myID);
			i++;
		}

		// If the car has moved out of intersection
		// set turned back to false
		if(!temp->isIntersection())
			turned = false;
		// Else we know the we reached the intersection
		else {
			// FlagOneIntersection to ensure that we only moves to the previous
			// intersection in relative to the laneTurned once.
			bool flagOneIntersection = true;
			// While we have not assigned all parts of the car to occupy appropriate sections
			while(i < size - 1){
				if (temp->isIntersection()){
					// If the car turns after the second intersection
					// it will go back to the right previous intersection relative to landTurned
					if(turnedLeft && flagOneIntersection){
						temp = temp->getPreviousIntersection(laneTurned);
						flagOneIntersection = false;
					}
					// Otherwise, get the previous intersection relative to the original lane  
					else
						temp = temp->getPreviousIntersection(lane->getName());
				}
				// For non-intersection sections
				else
					temp = temp->getPrevious();
				//special case for when the vehicle is still entering or exiting the system
				if (temp == 0) break;
				// Occupy the sections and increment counter i
				temp->fillSection(myID);
				i++;
			}
		}
	} else {
		// If the car went straight
		for(int i = 0; i < size - 1; i++){
			// Get the previous section based on the types of section
			if (temp->isIntersection())
				temp = temp->getPreviousIntersection(lane->getName());
			else
				temp = temp->getPrevious();

			//special case for when the vehicle is still entering or exiting the system
			if (temp == 0) break;
			temp->fillSection(myID);
		}
	}
	
	// Retrieve tempPrevious that we are supposed to free after the vehicle moves
	// one step forward/left/right
	Section* tempPrevious = 0;
	if(temp != 0){
		if (temp->isIntersection()){
			// If the car turns left and the current last section that the car occupies
			// point to the second intersection, the previous intersection
			// needs to be relative to laneTurned
			if(turnedLeft && 
				!temp->getNextIntersection(laneTurned)->isIntersection())
				tempPrevious = temp->getPreviousIntersection(laneTurned);
			// Otherwise, the previous intersection is relative to original lane
			else
				tempPrevious = temp->getPreviousIntersection(lane->getName());
		}
		// If the current last section is non-intersection
		else
			tempPrevious = temp->getPrevious();
	}

	// free the section not filled by the vehicle anymore
	if (tempPrevious != 0 )
		tempPrevious->freeSection();
	
	return true;
}

//***************************************************************
//* @brief Move the head section of car one section forward
//* @return true if vehicle moved forward (free section ahead),
//* 		false otherwise
bool Vehicle::goStraight(){
	//if the current section is an intersection
	if (section->isIntersection()){
		// If the car has turned on second intersection to another intersection,
		// the next section would be relative to the laneTurned 
		// (in an L-shape)
		if(turned)
			section = section->getNextIntersection(laneTurned);
		else
			section = section->getNextIntersection(lane->getName());
		if(!section->isFull()){ // if the next section is free
			section->fillSection(myID);
			return true;
		}
		return false;
	} else {
		// If car is leaving the system
		if (section->getNext() == 0){
			// If current section is the only part of the car left in simulation
			if(size == 1)
				section->freeSection();
			size--;
			return true;
		}
		// If car is currently right before intersection
		if(section->getNext()->isIntersection()){
			string state = lane->getTrafficLight()->getState(); 
			// If traffic light is red, return false and car doesnt' move
			if(state == "RED")
				return false;
			else if(state == "YELLOW"){
				// If the time left in yellow is enough for car to go past intersection
				if(lane->getTrafficLight()->getCurrentStateCounter() >= size + 2
					&& !section->getNext()->isFull()){
					section = section->getNext();
					section->fillSection(myID);
					return true;
				} return false;
			}
		}
		// If next section is free, occupy it
		if (!section->getNext()->isFull()) {
			section = section->getNext();
			section->fillSection(myID);
			return true;
		}
	}
	return false;
}

//***************************************************************
//* @brief Car turns left at intersection
//* 	   Set the appropriate next section based on current lane
bool Vehicle::turnLeft()
{
	// Set the next section appropriately based on current lane
	Section* next = section;
	if(lane->getName()== "WE"){
		next = section->getNorth();
		laneTurned = "SN";

	}
	if(lane->getName()== "EW"){
		next = section->getSouth();
		laneTurned = "NS";
	}
	if(lane->getName()== "NS"){
		next = section->getEast();
		laneTurned = "WE";
	}
	if(lane->getName()== "SN"){
		next = section->getWest();
		laneTurned = "EW";
	}
	// if the next section is occupied, vehicle stays still
	if(next->isFull())
		return false;

	cout << "vehicle " << myID << " turning left from  " << lane->getName() << " onto " << laneTurned << endl;
	// otherwise, occupy the next section, and set turned to true
	section = next;
	section->fillSection(myID);
	turned = true;	
	return true;
}

//***************************************************************
//* @brief car turns right at intersection
//*		   Set the appropriate next section based on current lane
bool Vehicle::turnRight()
{
	// Set the next section appropriately based on current lane
	Section* next = section;
	if(lane->getName()== "WE"){
		next = section->getSouth();
		laneTurned = "NS";
	}
	if(lane->getName()== "EW"){
		next = section->getNorth();
		laneTurned = "SN";
	}
	if(lane->getName()== "NS"){
		next = section->getWest();
		laneTurned = "EW";
	}
	if(lane->getName()== "SN"){
		next = section->getEast();
		laneTurned = "WE";
	}

	// if the next section is occupied, vehicle stays still
	if(next->isFull())
		return false;

	cout << "vehicle " << myID << " turning right from  " << lane->getName() << " onto " << laneTurned << endl;

	// otherwise, occupy the next section, and set turned to true
	section = next;
	section->fillSection(myID);
	turned = true;	
	return true;
}