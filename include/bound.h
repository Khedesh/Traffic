#ifndef BOUND_H
#define BOUND_H

#include <deque>
#include <fstream>

#include <Khagine/Khagine.hpp>
using namespace khagine;

class Car;
class Road;

class Bound : public Entity
{
	friend void OnBoundArrival(Entity* ent);
	friend void OnBoundDeparture(Entity* ent);

	std::deque<Car*> cars;
	bool reversed;

	static int bound_count;
	int index;

	Road* parent_road;

	static float last_event_time;

	public:

	Bound(Road* proad, bool _reversed = false);
	~Bound();

	void push(Car* m_car);
	Car* pop();

	Car* front();
	Car* back();

	bool is_empty();

	int get_car_count();
	Car* get_car(int cindex);

	void update_cars_position(float t);

	void set_last_event_time(float let);

	void print_all_cars();

	int get_index();

	Road* get_parent_road();
};

void OnBoundArrival(Entity* ent);
void OnBoundDeparture(Entity* ent);

#endif // BOUND_H
