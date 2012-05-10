#include "cross.h"

void Cross::Connect(Road * h)
{
	connected_Roads.push_back(h);
}

Cross::Cross()
{
	length = 10;
	width  = 10;
}

void Cross::Install(int x1, int y1, double speedy, bool light)
{
	length = x1;
	width  = y1;
	speed = speedy;
	haslight = light;	
}

void Cross::Enter(Car * a)
{
	available_Cars.push_back(a);
}

Car* Cross::Exit()
{
	Car* b = available_Cars.front();
	return b;
} 
