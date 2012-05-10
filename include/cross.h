#ifndef BEHZAD_H
#define BEHZAD_H

#include <iostream>
#include <vector>
#include "road.h"
#include "car.h"
#include <Khagine/Khagine.hpp>

using namespace std;
using namespace khagine;

class Cross : public Entity
{
	private:
	double speed;
	int length;
	int width;
	bool haslight;
	vector<Road*> connected_Roads;
	vector<Car*> available_Cars;
	public:
	void Install(int x1,int y1,double speed1,bool light);
	Cross();
	void Enter(Car * a);
	Car * Exit();
	void Connect(Road * h);
};

#endif
