#ifndef __TRAFFICLIGHT_H__
#define __TRAFFICLIGHT_H__

#include <string>

using namespace std;

class TrafficLight{
	
	private:
		string state; 				//< State of the traffic light "RED", "GREEN" or "YELLOW"
		int currentStateCounter;	
		int timeRed;
		int timeYellow;
		int timeGreen;

	public:

		TrafficLight();
		TrafficLight(TrafficLight& trafficLight);
		~TrafficLight();
		TrafficLight(int timeGreen, int timeYellow, string state);

		void changeState();
		string getState(){return state;}

		void setTimeRed(int timeRed){this->timeRed = timeRed;}
		void setTimeYellow(int timeYellow){this->timeYellow = timeYellow;}
		void setTimeGreen(int timeGreen){this->timeGreen = timeGreen;}

		int getTimeRed(){return timeRed;}
		int getTimeYellow(){return timeYellow;}
		int getTimeGreen(){return timeGreen;}

		int getCurrentStateCounter(){return currentStateCounter;}
};

#endif