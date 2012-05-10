#ifndef EXIT_H
#define EXIT_H

#include <Khagine.h>
#include <vector>
using namespace std;
using namespace khagine;

#include "road.h"
#include "car.h"

class Exit
{
	private:
		Road* road;
		double delay;
		double maxSpeed;
		//double currentSpeed;
		vector<Car*>cars;
	public:
		int getMaxSpeed();
		//int getCurrentSpeed();
		int getDelay();
};

#endif
