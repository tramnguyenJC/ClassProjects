#ifndef __SECTION_H__
#define __SECTION_H__

#include <string>

using namespace std;

class Section{
	private:

		bool intersection;
		bool full;
		Section* next;
		Section* previous;
		int vehicleID = 0;

		Section* nextNorth;
		Section* nextSouth;
		Section* nextWest;
		Section* nextEast;

	public:
		Section();
		Section(Section& section);
		~Section();

		void fillSection(int id);
		void freeSection();

		// Setters and getter for next or previous sections
		void setNext(Section* nextSection){ next = nextSection;}
		void setPrevious(Section* previousSection){previous = previousSection;}
		Section* getNext(){return next;} // may need to use pointers?
		Section* getPrevious(){return previous;}

		Section* getNorth(){return nextNorth;}
		Section* getSouth(){return nextSouth;}
		Section* getWest(){return nextWest;}
		Section* getEast(){return nextEast;}
		Section* getPreviousIntersection(string laneName);
		Section* getNextIntersection(string laneName);

		void setNorth(Section* north){nextNorth = north;}
		void setSouth(Section* south){nextSouth = south;}
		void setWest(Section* west){nextWest = west;}
		void setEast(Section* east){nextEast = east;}

		// Setters and getters for whether Section is Intersection
		void setIntersection(){intersection = true;}
		bool isIntersection(){return intersection;}
		bool isFull(){return full;}

		void printSection(string lane);
		int getVehicleID(){return vehicleID;}
};

#endif