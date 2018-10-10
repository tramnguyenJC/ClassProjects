#include "Section.h"
#include <iostream>

//***************************************************************
//* @brief Default Constructor, initialize all member variables
Section::Section()
{
	intersection = false;
	full = false;
	next = 0;
	previous = 0;
	vehicleID = 0;
}

//***************************************************************
//* @brief Copy Constructor
//* @param section: the Section to be copied
Section::Section(Section& section)
{
	intersection = section.intersection;
	full = section.full;
	next = section.next;
}

//***************************************************************
//* @brief Destructor
Section::~Section()
{}

//***************************************************************
//* @brief Get the previous intersection block based on lane
//* @param laneName the name of the lane
//* @return the section previous to current section on this lane
Section*
Section::getPreviousIntersection(string laneName){
	if (laneName == "NS")
		return nextNorth;
	if (laneName == "SN")
		return nextSouth;
	if (laneName == "EW")
		return nextEast;
	if (laneName == "WE")
		return nextWest;
	return 0;
}

//***************************************************************
//* @brief Get the next intersection block based on lane
//* @param laneName the name of the lane
//* @return the section following the current section on this lane
Section*
Section::getNextIntersection(string laneName){
	if (laneName == "NS")
		return nextSouth;
	if (laneName == "SN")
		return nextNorth;
	if (laneName == "EW")
		return nextWest;
	if (laneName == "WE")
		return nextEast;
	return 0;
}

//***************************************************************
//* @brief Fill section with vehicle
//* @param vehicleID the id of the vehicle that occupies the section
void Section::fillSection(int vehicleID)
{
	full = true;
	this->vehicleID = vehicleID;
}

//***************************************************************
//* @brief Free section
//* Set vehicleID to 0 (unoccupied)
void Section::freeSection()
{
	full = false;
	vehicleID = 0;
}

//***************************************************************
//* @brief Print information about section
void Section::printSection(string lane){
	if(!full)
		if(lane == "WE" || lane == "EW")
			cout << "0 " ;
		else if(lane == "NS" || lane == "SN") 
			cout << "0"<< "|" ;
		else
			cout << "0"<< "|" ;

	else
		if(lane == "WE" || lane == "EW")
			cout << vehicleID << " " ;
		else if(lane == "NS" || lane == "SN")
			cout << vehicleID << "|" ;
		else
			cout << vehicleID << "|" ;

}