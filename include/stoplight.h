#ifndef STOPLIGHT_H
#define STOPLIGHT_H

#include <Khagine.h>
#include "road.h"

using namespace khagine;
using namespace std;

class StopLight
{
	private:
		Road* road;
		static int color;
		double maxSpeed;
		double currentSpeed;
		bool passLine;
	public:
		int getColor(int = 0);
		double getmaxSpeed();
		double getCurrentSpeed();
		bool getPassline();
};

#endif
