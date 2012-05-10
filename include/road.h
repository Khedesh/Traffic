#ifndef ROAD_H
#define ROAD_H

#include <vector>
#include <cstring>

#include <Khagine/Khagine.hpp>
using namespace khagine;

#include "core.h"
#include "bound.h"

class Road : public Entity
{
	Vector3df pos;
	float angle;
	std::vector<Bound*> bounds;
	
	float max_speed;

	float length;
	
	char file[80];

	FILE* fptr;

	public:
	
	Road(const char* file, double x, double y, double z, int bcount, float _length, int _max_speed, float _angle = 0);
	~Road();
	
	void push_car(Car* m_car, int index);
	Car* pop_car(int index);
	bool is_empty(int index);

	Bound* get_bound(int index);
	int get_bound_count();
	
	float get_length();

	void update_all_bounds(float time);

	void print_all_cars();
	void append_to_file();
};

#endif // ROAD_H
