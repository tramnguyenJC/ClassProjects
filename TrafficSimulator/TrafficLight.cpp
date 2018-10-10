#include "TrafficLight.h"

//***************************************************************
//* @brief Default Constructor

TrafficLight::TrafficLight()
{}

//***************************************************************
//* @brief Copy Constructor
//* @param trafficLight the TrafficLight to be copied from
TrafficLight::TrafficLight(TrafficLight& trafficLight)
{
	state = trafficLight.state; 
	currentStateCounter = trafficLight.currentStateCounter;
	timeRed = trafficLight.timeRed;
	timeYellow = trafficLight.timeYellow;
	timeGreen = trafficLight.timeGreen;
}

//***************************************************************
//* @brief Default destructor
TrafficLight::~TrafficLight()
{}

//***************************************************************
//* @brief Constructor
//* @param timeGreen: given time length for Green stage
//* @param timeYellow: given time length for Yellow stage
//* 	   timeRed would be timeGreen + timeYellow
//* @param state: the state the traffic light is starting out with
TrafficLight::TrafficLight(int timeGreen, int timeYellow, string state)
{
	this->timeYellow = timeYellow;
	this->timeGreen = timeGreen;
	timeRed = timeGreen + timeYellow; //assuming no car enters the intersection if it cannot completely clear it by end of yellow light

	currentStateCounter = 0;

	this->state = state;
}

//***************************************************************
//* @brief Change the state if the time is reached
void TrafficLight::changeState()
{
	currentStateCounter++;
	//assuming that the currentStateCounter is being updated outside - HS changed to updating in this method
	if(state == "GREEN" && currentStateCounter >= timeGreen)
	{
		state = "YELLOW";
		currentStateCounter = 0;
	} else if (state == "YELLOW" && currentStateCounter >= timeYellow)
	{
		state = "RED";
		currentStateCounter = 0;
	} else if (state == "RED" && currentStateCounter >= timeRed)
	{
		state = "GREEN";
		currentStateCounter = 0;
	}
}