/*
CAR:
 * localPosition(struct(x,y,z)) -> Another solution class localPosition
 *carType(length,maxSpeed,meshType,color,withd,int delay) -> Another solution class carType
 **in these solutions:
 currentSpeed
 Road* road
 void brake()
 void addSpeed()
 void draw()
 These are All MADINE FAZELE!
 */
#include "car.h"

vector<CarType> Car::car_types;

void Car::addType(CarType nType)
{
	car_types.push_back(nType);
}

CarType Car::getType()
{
	return car_types[type_index];
}

void Car::setPosition(float x, float y, float z)
{
	pos.x = x; pos.y = y; pos.z = z;
}

Vector3df Car::getPosition()
{
	return pos;
}

void Car::setRotation(float rx, float ry, float rz)
{
	rot.x = rx; rot.y = ry; rot.z = rz;
}

Rotation Car::getRotation()
{
	return rot;
}

double Car::getCurrentSpeed()
{
	return currentSpeed;
}

void Car::setCurrentSpeed(double cSpeed)
{
	currentSpeed = cSpeed;
}

Car::Car(int t_index, Bound* pbound, double iSpeed)
{
	type_index = t_index;
	currentSpeed = iSpeed;
	local_pos = 0.0f;

	min_to_end = 0;
	parent_bound = pbound;

	// adding method
	add_method(OnCarCollide);

	// setting the default value for back and next member
	back = 0;
	next = 0;
}

void Car::brake()
{
	currentSpeed = 0;
}

void Car::addSpeed(double adder)
{
	currentSpeed += adder;
}

void Car::increase_local_pos(float dx)
{
	local_pos += dx;
}

float Car::get_local_pos()
{
	return local_pos;
}

Car::~Car()
{
}

Car* Car::get_back()
{
	return back;
}

Car* Car::get_next()
{
	return next;
}

void Car::set_back(Car* _back)
{
	back = _back;
}

void Car::set_next(Car* _next)
{
	next = _next;
}

float Car::get_min_to_end()
{
	return min_to_end;
}

void Car::set_min_to_end(float mend)
{
	min_to_end = mend;
}

void Car::update_local_pos(float dt)
{
	local_pos += dt * currentSpeed;
}

void OnCarCollide(Entity* ent)
{
	Car* car = (Car*)ent;
	Bound* bound = car->parent_bound;
	float cur_time = bound->get_clock()->get_time();
/*
	Logger::inst()->log(KLT_OUTPUT) << "----------------------------------------------" << std::endl;
	Logger::inst()->log(KLT_OUTPUT) << "Time: " << bound->get_clock()->get_time() << std::endl;
	Logger::inst()->log(KLT_OUTPUT) << "Index: " << bound->get_index() << std::endl;
	Logger::inst()->log(KLT_OUTPUT) << "Event type: Collide" << std::endl;
*/
	// updating cars
	bound->get_parent_road()->update_all_bounds(bound->get_clock()->get_time());
	bound->set_last_event_time(bound->get_clock()->get_time());

	// setting the velocity
	car->setCurrentSpeed(car->get_next()->getCurrentSpeed());

	// setting the min to end
	car->set_min_to_end(car->get_next()->get_min_to_end());

	// go to back cars
	Car* cur_car = car;
	Car* back_car = cur_car->get_back();
	while(back_car != NULL)
	{
		float dx = cur_car->get_local_pos() - back_car->get_local_pos() - (cur_car->getType().length + back_car->getType().length) / 2;
		float dv = cur_car->getCurrentSpeed() - back_car->getCurrentSpeed();

		// if they will collide
		if(dv < 0)
		{
			float dt = -dx / dv;

			if(cur_time + dt < cur_car->get_min_to_end())
			{
				// constructing the collide event
				Event* col_evt = new Event(cur_time + dt, back_car, 0);
				bound->get_event_queue()->push_event(col_evt);

				back_car->set_min_to_end(cur_time + dt);
			}
			else
			{
				back_car->set_min_to_end(cur_car->get_min_to_end());
			}
		}
		else
		{
				back_car->set_min_to_end(cur_car->get_min_to_end());
		}

		cur_car = back_car;
		back_car = cur_car->get_back();
	}

	//bound->get_parent_road()->print_all_cars();
	bound->get_parent_road()->append_to_file();
}
