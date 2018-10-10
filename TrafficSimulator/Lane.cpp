#include "Lane.h"
#include <iostream>

using namespace std;

//***************************************************************
//* @brief Default Constructor, initialize all member variables
Lane::Lane()
{
	length = 0;
	laneStart = 0;
}

//***************************************************************
//* @brief Constructor
//* @param name specified name for lane
//* @param length the length of the lane
//* @param one the Intersection one of the lane
//* @param two the Intersection two of the lane
//* @param trafficLight the TrafficLight the lane owns
Lane::Lane(string name, int length, Section* one, Section* two, TrafficLight* trafficLight)
{
	this->trafficLight = trafficLight;
	this->name = name;
	laneStart = new Section();
	Section* temp = laneStart;
	laneStart->setPrevious(0);

	//create first half of lane
	for (int i = 0; i < length/2 -2  ; i++)
	{
		Section* section = new Section();
		temp->setNext(section);
		section->setPrevious(temp);
		temp = section;
	}

	//set the intersection pieces to the middle of the lane
	temp->setNext(one);
	one->setPrevious(temp);
	//temp = one;
	
	temp = temp->getNext();
	temp = two;

	//create second half of lane
	for (int i = 0; i < length/2 - 1; i++) 
	{
		Section* section = new Section();
		temp->setNext(section);
		section->setPrevious(temp);
		temp = section;
	}
	//end the lane
	temp->setNext(0);
	laneEnd = temp;

	this->length = length;

}

//***************************************************************
//* @brief Copy Constructor
//* @lane given Lane to be copied from
Lane::Lane(Lane& lane)
{
	length = lane.length;
	laneStart = lane.laneStart;
}

//***************************************************************
//* @brief Default Destructor
//* Delete all the non-intersection sections
Lane::~Lane()
{
	Section* temp = laneStart;
	Section* temp2 = temp;

	for (int i = 0; i < length/2 -1 ; i++)
	{
		temp2 = temp->getNext();
		delete temp;
		temp = temp2;
	}

	temp2 = temp->getNextIntersection(name);
	temp2 = temp2->getNextIntersection(name);
	temp = temp2;
	for (int i = 0; i < length/2 -2 ; i++)
	{

		temp2 = temp->getNext();
		delete temp;
		temp = temp2;
	}
	delete temp2; 
}

//***************************************************************
//* @brief Print lane with section addresses for debugging purposes
void Lane::printLane()
{
	Section* temp = laneStart;
	for (int i = 0; i < length/2 -1  ; i++)
	{
		cout << temp << endl;
		temp = temp->getNext();
	}

	cout << temp << endl;
	temp = temp->getNextIntersection(name);
	cout << temp << endl;
	temp = temp->getNextIntersection(name);
	
	// print second half of lane
	for (int i = 0; i < length/2 - 1; i++) 
	{
		cout << temp << endl;
		temp = temp->getNext();
	}
}

//***************************************************************
//* @brief Print the contents of the lane
//* Print out 0 if section is unoccupied, and car's ID otherwise
void Lane::printLaneContents()
{
	Section* temp = laneStart;
	cout << "| ";
	for (int i = 0; i < length/2 -1  ; i++)
	{
		temp->printSection("");
		temp = temp->getNext();	
	}

	temp->printSection("");
	temp = temp->getNextIntersection(name);
	temp->printSection("");
	temp = temp->getNextIntersection(name);

	//create second half of lane
	for (int i = 0; i < length/2 - 1; i++) 
	{
		temp->printSection("");
		temp = temp->getNext();
	}
	cout << endl;
}
