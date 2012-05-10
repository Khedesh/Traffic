#ifndef ASGHAR_H
#define ASGHAR_H

#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include "core.h"
#include "road.h"
using namespace std;

struct CarType
{
	int delay;
	float length;
	float max_speed;
	Vector3df color;

}; // end struct CarType

class Car : public Entity
{
	friend void OnCarCollide(Entity* ent);

	Vector3df pos;
	Rotation rot;

	float local_pos;

	double currentSpeed;
	Road * road; //It will handle

	int type_index;

	static vector<CarType> car_types;

	Car* back;
	Car* next;

	float min_to_end; // minimum event time from this to end.

	Bound* parent_bound;

	public:

	Car(int t_index, Bound* pbound, double iSpeed);
	~Car();

	static void addType(CarType nType);
	CarType getType();

	void setPosition(float x, float y, float z);
	Vector3df getPosition();
	void setRotation(float rx, float ry, float rz);
	Rotation getRotation();

	double getCurrentSpeed();
	void setCurrentSpeed(double cSpeed);
	void brake();
	void addSpeed(double adder);

	Car* get_back();
	Car* get_next();

	void set_back(Car* _back);
	void set_next(Car* _next);

	void increase_local_pos(float dx);
	float get_local_pos();

	float get_min_to_end();
	void set_min_to_end(float mend);

	void update_local_pos(float dt);
};

void OnCarCollide(Entity* ent);

#endif
