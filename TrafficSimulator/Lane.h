#ifndef __LANE_H__
#define __LANE_H__

#include "Section.h"
#include "TrafficLight.h"

#include <string>

using namespace std;

class Lane{
	private:
		int length;
		Section* laneStart;
		string name;
		TrafficLight* trafficLight;
		Section* laneEnd;

		
	public:

		Lane();
		Lane(string name, int length, Section* one, Section* two, TrafficLight* trafficLight);
		Lane(Lane& lane);
		~Lane(); 

		int getLength(){return length;}
		//needs to change because need to modify the section
		void setLength(int laneLength){length = laneLength;}
		Section* getLaneStart(){return laneStart;}
		Section* getLaneEnd(){return laneEnd;}

		string getName(){return name;}

		void printLane();

		void printLaneContents();

		TrafficLight* getTrafficLight(){return trafficLight;}


};

#endif