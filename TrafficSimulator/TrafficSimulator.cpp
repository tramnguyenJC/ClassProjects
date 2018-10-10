#include "TrafficSimulator.h"

//***************************************************************
//* @brief Default Constructor, initialize all member variables
TrafficSimulator::TrafficSimulator()
{
	NSlaneLength = 10;
    WElaneLength = 10;

	newVehicleProb = 0.5;
	carProb = 0.4;
	SUVProb = 0.4;
	truckProb = 0.2;

	NSProb = 0.25;
	SNProb = 0.25;
	EWProb = 0.25;
	WEProb = 0.25;

	numIterations = 10;
	printInfo = true;
	single_step = false;

	timeGreen = 6;
	timeYellow = 3;

	//create traffic system
	northWest = new Section();
	northWest->setIntersection();
	//cout << "intersection northWest: " << northWest << endl;
	
	northEast = new Section();
	northEast->setIntersection();
	//cout << "intersection northEast: " << northEast << endl;
	
	southWest = new Section();
	southWest->setIntersection();
	//cout << "intersection southWest: " << southWest << endl;
	
	southEast = new Section();
	southEast->setIntersection();
	//cout << "intersection southEast: " << southEast << endl;

    trafficLightWE = new TrafficLight(timeGreen, timeYellow, "GREEN");
    trafficLightEW = new TrafficLight(timeGreen, timeYellow, "GREEN");
    trafficLightNS = new TrafficLight(timeGreen, timeYellow, "RED");
    trafficLightSN = new TrafficLight(timeGreen, timeYellow, "RED");

	laneWE = new Lane("WE", WElaneLength, southWest, southEast, trafficLightWE);
	laneEW = new Lane("EW", WElaneLength, northEast, northWest, trafficLightEW);
	laneNS = new Lane("NS", NSlaneLength, northWest, southWest, trafficLightNS);
	laneSN = new Lane("SN", NSlaneLength, southEast, northEast, trafficLightSN);

	setIntersections();
	clock = 1;
}

//***************************************************************
//* @brief Copy Constructor
//* @param trafficSimulator: given TrafficSimulator to be copied
TrafficSimulator::TrafficSimulator(TrafficSimulator& trafficSimulator)
{
	northWest = trafficSimulator.northWest;
	northEast = trafficSimulator.northEast;
	southWest = trafficSimulator.southWest;
	southEast = trafficSimulator.southEast;

	laneWE = trafficSimulator.laneWE;
	laneEW = trafficSimulator.laneEW;
	laneNS = trafficSimulator.laneNS;
	laneSN = trafficSimulator.laneSN;

	trafficLightWE = trafficSimulator.trafficLightWE;
	trafficLightEW = trafficSimulator.trafficLightEW;
	trafficLightNS = trafficSimulator.trafficLightNS;
	trafficLightSN = trafficSimulator.trafficLightSN;

    newVehicleProb = trafficSimulator.newVehicleProb;
	carProb = trafficSimulator.carProb;
	SUVProb = trafficSimulator.SUVProb;
	truckProb = trafficSimulator.truckProb;

	NSProb = trafficSimulator.NSProb;
	SNProb = trafficSimulator.SNProb;
	WEProb = trafficSimulator.WEProb;
	EWProb = trafficSimulator.EWProb;
	timeGreen = trafficSimulator.timeGreen;
	timeYellow = trafficSimulator.timeYellow;

	NSlaneLength = trafficSimulator.NSlaneLength;
	WElaneLength = trafficSimulator.WElaneLength;
	numIterations = trafficSimulator.numIterations;
	vehicles = trafficSimulator.vehicles ;
	clock = trafficSimulator.clock;
	printInfo = trafficSimulator.printInfo;
	single_step = trafficSimulator.single_step;
}

//***************************************************************
//* @brief Destructor
TrafficSimulator::~TrafficSimulator()
{
	delete northWest;
	delete northEast;
	delete southWest;
	delete southEast;
	delete laneWE;
	delete laneEW;
	delete laneNS;
	delete laneSN;
	delete trafficLightWE;
	delete trafficLightEW;
	delete trafficLightNS;
	delete trafficLightSN;

	for (int i = 0; i < vehicles.size(); i++){
		delete vehicles[i];
	}
}

//***************************************************************
//* @brief Constructor
//* @param length: given length of lane specified
TrafficSimulator::TrafficSimulator(FileParser* fileParser)
{

	NSlaneLength = fileParser->getNSlaneLength();
    WElaneLength = fileParser->getWElaneLength();

	newVehicleProb = fileParser->getNewVehicleProb();
	carProb = fileParser->getCarProb();
	SUVProb = fileParser->getSUVProb();
	truckProb = fileParser->getTruckProb();

	NSProb = fileParser->getNSProb();
	SNProb = fileParser->getSNProb();
	EWProb = fileParser->getEWProb();
	WEProb = fileParser->getWEProb();

	timeGreen = fileParser->getTimeGreen();
	timeYellow = fileParser->getTimeYellow();

	numIterations = fileParser->getNumIterations();
	printInfo = fileParser->getPrintInfo();
	single_step = fileParser->getSingleStep();


	// Create traffic system
	northWest = new Section();
	northWest->setIntersection();
	
	northEast = new Section();
	northEast->setIntersection();
	
	southWest = new Section();
	southWest->setIntersection();
	
	southEast = new Section();
	southEast->setIntersection();
	
	// Create traffic lights
	trafficLightWE = new TrafficLight(timeGreen, timeYellow, "GREEN");
    trafficLightEW = new TrafficLight(timeGreen, timeYellow, "GREEN");
    trafficLightNS = new TrafficLight(timeGreen, timeYellow, "RED");
    trafficLightSN = new TrafficLight(timeGreen, timeYellow, "RED");

    // Create lanes
	laneWE = new Lane("WE",WElaneLength, southWest, southEast, trafficLightWE);
	laneEW = new Lane("EW",WElaneLength, northEast, northWest, trafficLightEW);
	laneNS = new Lane("NS",NSlaneLength, northWest, southWest, trafficLightNS);
	laneSN = new Lane("SN",NSlaneLength, southEast, northEast, trafficLightSN);

	// Connect intersection with lanes
	setIntersections();

	clock = 1;

	// Set error flags if probabilities do not add up
	if((carProb + SUVProb + truckProb) != 1)
	{
		cerr << "The probabilities of a new vehicle being a certain type must sum to 1 exactly." << endl;
		exit(1);
	}

	if((NSProb + SNProb + EWProb + WEProb) != 1)
	{
		cerr << "The probabilities of a vehicle being on a certain lane must sum to 1 exactly." << endl;
		exit(1);
	}

	if ((newVehicleProb > 1) || (newVehicleProb < 0))
	{
		cerr << "The probability of a new vehicle appearing must be between 0 and 1." << endl;
		exit(1);
	}

	if(newVehicleProb == 0)
		cerr << "WARNING: the probability of a new vehicle appearing is set to 0, so vehicles will not enter the system." << endl;
}

//***************************************************************
//* @brief Run the simulation
bool TrafficSimulator::run()
{
	for (int i = 0; i < numIterations; i++)
	{
		if (single_step)
			cin.get();

		cout << "CLOCK: " << clock << endl;
		
		// Move all vehicles
		for (int i = 0; i < vehicles.size(); i++)
		{
			vehicles[i]->move();
		}

		// Spawn new vehicle with probability newVehicleProb
		double randSpawn = (double) rand() / RAND_MAX;
		if(randSpawn <= newVehicleProb)
			spawnVehicle();
		else {	
			if (printInfo)
			cout << "no new vehicles spawned" << endl;
		}

		updateTrafficLights();
		clock++; //update the clock
		printSystem();
	}
	return true;
}

//***************************************************************
//* @brief Sets all the directions for the intersections so they
//* are linked correctly
void TrafficSimulator::setIntersections()
{
	northWest->setSouth(southWest);
	northWest->setWest(northWest->getNext());
	northWest->setEast(northEast);
	northWest->setNorth(northWest->getPrevious());
	// northWest cannot go north or east

	southWest->setEast(southEast);
	southWest->setSouth(southWest->getNext());
	southWest->setNorth(northWest);
	southWest->setWest(southWest->getPrevious());
	// southWest cannot go north or west

	northEast->setWest(northWest);
	northEast->setNorth(northEast->getNext());
	northEast->setSouth(southEast);
	northEast->setEast(northEast->getPrevious());
	// northEast cannot go south or east

	southEast->setNorth(northEast);
	southEast->setEast(southEast->getNext());
	southEast->setWest(southWest);
	southEast->setSouth(southEast->getPrevious());
	// southEast cannot go west or south
}

//***************************************************************
//* @brief Print out lanes and their content
void TrafficSimulator::printSystem()
{
	printNorth();
	printEW();
	printWE();
	printSouth();

	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
}

//***************************************************************
//* @brief Print the lanes in north direction
void TrafficSimulator::printNorth()
{
	int numSpaces = (laneWE->getLength()-2)/2;
	string spaces = "";
	string extraSpaces = spacer(0," ");
	for (int i = 0; i < numSpaces; i++)
	{
		spaces = "  " + extraSpaces + spaces; //get the correct spacing for printing to the left of the lane
	}
 	
 	spaces = spaces + "        ";//accomodating for the East label
 	//print out lane labels
 	cout << " " << spaces << "North" << endl;
 	cout << " " << spaces << extraSpaces << "|" << endl;
 	cout << " " << spaces << extraSpaces << "V" << endl;

 	

	Section* tempNS = laneNS->getLaneStart(); //first half of NS
	Section* tempSN = laneSN->getLaneEnd(); //second half of SN
	for (int i = 0; i < laneNS->getLength()/2 -1  ; i++)
	{
		cout << spaces << "|";
		cout << spacer(tempNS->getVehicleID(),"0");
		tempNS->printSection("NS");
		cout << spacer(tempSN->getVehicleID(),"0");
		tempSN->printSection("SN");
		tempNS = tempNS->getNext();//get next section of NS
		tempSN = tempSN->getPrevious();//get previous section of SN(going backwards)
		cout << endl;
	}
}

//***************************************************************
//* @brief Print lane WE
void TrafficSimulator::printWE()
{
	Section* tempWE = laneWE->getLaneStart(); 
	
	string roadLine = " ";
	string roadSegment = spacer(0,"-");
	for (int i = 0; i < laneWE->getLength(); i++)
	{
		roadLine = roadLine + roadSegment + "- ";
	}

	cout << "        " << roadLine << endl;
	cout << "West --> ";
	//first half of WE
	for (int i = 0; i < laneWE->getLength()/2 -1  ; i++)
	{
		cout << spacer(tempWE->getVehicleID(),"0");
		tempWE->printSection("WE");
		tempWE = tempWE->getNext();//get next section of WE
	}

	//print intersections that belong to WE lane
	cout << spacer(tempWE->getVehicleID(),"0");
	tempWE->printSection("NS");
	tempWE = tempWE->getEast();
	cout << spacer(tempWE->getVehicleID(),"0");
	tempWE->printSection("NS");
	tempWE = tempWE->getEast();

	//second half of WE
	for (int i = 0; i < laneWE->getLength()/2 -1  ; i++)
	{
		cout << spacer(tempWE->getVehicleID(),"0");
		tempWE->printSection("WE");
		tempWE = tempWE->getNext();//get next section of WE
	}

	cout << endl; //next line
	cout << "        " << roadLine << endl;
}

//***************************************************************
//* @brief Print lane EW
void TrafficSimulator::printEW()
{
	string roadLine = " ";
	string roadSegment = spacer(0, "-");
	for (int i = 0; i < laneWE->getLength(); i++)
	{
		roadLine = roadLine + roadSegment + "- " ;
	}

	cout << "        " << roadLine << endl;
	
	Section* tempEW = laneEW->getLaneEnd(); 
	cout << "         ";
 	//first half of WE
	for (int i = 0; i < laneEW->getLength()/2 -1  ; i++)
	{
		cout << spacer(tempEW->getVehicleID(),"0");
		tempEW->printSection("EW");
		tempEW = tempEW->getPrevious();//going backward on EW
	}
	//cout << "here" << endl;

	//print intersections that belong to EW lane
	cout << spacer(tempEW->getVehicleID(),"0");
	tempEW->printSection("NS");
	tempEW = tempEW->getEast();
	cout << spacer(tempEW->getVehicleID(),"0");
	tempEW->printSection("NS");
	tempEW = tempEW->getEast();

	//second half of WE
	for (int i = 0; i < laneEW->getLength()/2 -1  ; i++)
	{
		cout << spacer(tempEW->getVehicleID(),"0");
		tempEW->printSection("EW");
		tempEW = tempEW->getPrevious();//going backward on EW
	}

	cout << "<-- East";

	cout << endl; //next line
}

//***************************************************************
//* @brief Print the lanes in south direction
void TrafficSimulator::printSouth()
{
	int numSpaces = (laneWE->getLength()-2)/2;
	string spaces = "";
	string extraSpaces = spacer(0," ");
	for (int i = 0; i < numSpaces; i++)
	{
		//get the correct spacing for printing to the left of the lane
		spaces = "  " + extraSpaces + spaces;
	}

	Section* tempNS = southWest->getSouth();
	Section* tempSN = southEast->getSouth();

	spaces = spaces + "        ";//accomodating for the East label

	for (int i = 0; i < laneNS->getLength()/2 - 1; i++) 
	{
		cout << spaces << "|";
		cout << spacer(tempNS->getVehicleID(),"0");
		tempNS->printSection("NS");
		cout << spacer(tempSN->getVehicleID(),"0");
		tempSN->printSection("SN");
		tempNS = tempNS->getNext();
		tempSN = tempSN->getPrevious();
		cout << endl;
	}

	cout << " " << spaces << extraSpaces << extraSpaces << "^" << endl;
 	cout << " " << spaces << extraSpaces << extraSpaces << "|" << endl;
	cout << " " << spaces << extraSpaces << "South" << endl;
	//end of all printing
}

//***************************************************************
//* @brief Spawn vehicles randomly
bool TrafficSimulator::spawnVehicle()
{
	srand (8675309 + clock); //initialize with random seed - new every clock tick
	rand();

	Lane* laneType = 0;

	// generate random number between 1-4 for determining what lane
	double randLane = (double)rand () / RAND_MAX;
	//assigning ranges
	double NSrange = NSProb;
	double SNrange = NSProb + SNProb;
	double WErange = NSProb + SNProb + WEProb;
	double EWrange = NSProb + SNProb + WEProb + EWProb; //should be 1

	//cout << "NSrange: " << NSrange << " SNrange: " << SNrange <<  " WErange: " << WErange << " EWrange: " << EWrange << endl;

	if(randLane <= NSrange)
		laneType = laneNS;
	else if (randLane <= SNrange)
		laneType = laneSN;
	else if (randLane <= WErange)
		laneType = laneWE;
	else if (randLane <= EWrange)
		laneType = laneEW;

	// if there is a vehicle occupying the start of the lane, do not spawn vehicle
	if(laneType->getLaneStart()->isFull() == true)
		return false;

	// generate random number between 1-3 for determining what kind of car
	double randVehicle = (double)rand() / RAND_MAX;

	string vehicleType = "";
	double carRange = carProb;
	double SUVRange = SUVProb + carProb; // assigning certain range to SUV
	double truckRange = truckProb + SUVProb + carProb; // assigning certain range to truck - should be 1

	if(randVehicle <= carRange)
		vehicleType = "CAR";
	else if (randVehicle <= SUVRange)
		vehicleType = "SUV";
	else if (randVehicle <= truckRange)
		vehicleType = "TRUCK";

	double turnProb = (double)rand() / RAND_MAX; //generate random turning probablity

	Vehicle* vehicle = new Vehicle(laneType, vehicleType, turnProb);
	vehicles.push_back(vehicle);

	if (printInfo)
		cout << "added vehicle " << vehicle->getID() << " of type " << vehicleType 
			 << " to the " << laneType->getName() << " lane" << endl;

	return true;
}

//***************************************************************
//* @brief Update Traffic lights
void TrafficSimulator::updateTrafficLights()
{
	//NOTE: currentStateCounter being updated in the changeState() method

	trafficLightEW->changeState();
	trafficLightWE->changeState();
	trafficLightSN->changeState();
	trafficLightNS->changeState();

	if (printInfo){
		cout << "NS lane - " << trafficLightNS->getState() << endl;
		cout << "SN lane - " << trafficLightSN->getState() << endl;
		cout << "WE lane - " << trafficLightWE->getState() << endl;
		cout << "EW lane - " << trafficLightEW->getState() << endl;
	}
}

//***************************************************************
//* @brief spaces the item correctly for the number of iterations
string TrafficSimulator::spacer(int vehicleID, string item)
{
	string space = "";

	string max = to_string(numIterations);
	string vehicle = to_string(vehicleID);

	int numZeroes = max.length() - vehicle.length();

	for (int i = 0; i < numZeroes; i++)
		space = item + space;

	return space; 
}
