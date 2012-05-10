#include "bound.h"
#include "car.h"

int Bound::bound_count = 0;
float Bound::last_event_time = 0.0f;

Bound::Bound(Road* proad, bool _reversed)
{
	last_event_time = 0;

	parent_road = proad;

	reversed = _reversed;

	add_method(OnBoundArrival);
	add_method(OnBoundDeparture);

	index = bound_count ++;
}

Bound::~Bound()
{
}

void Bound::push(Car* m_car)
{
	cars.push_back(m_car);
}

Car* Bound::pop()
{
	Car* ret = cars.front();
	cars.pop_front();
	return ret;
}

Car* Bound::front()
{
	if(reversed)
		return cars.back();
	else
		return cars.front();
}

Car* Bound::back()
{
	if(reversed)
		return cars.front();
	else
		return cars.back();
}

bool Bound::is_empty()
{
	return cars.empty();
}

int Bound::get_car_count()
{
	return cars.size();
}

Car* Bound::get_car(int cindex)
{
	return cars[cindex];
}

void Bound::update_cars_position(float t)
{
	for(unsigned j = 0 ; j < cars.size() ; j ++)
	{
		cars[j]->update_local_pos(t - last_event_time);
	}
}

void Bound::set_last_event_time(float let)
{
	last_event_time = let;
}

void Bound::print_all_cars()
{
	for(unsigned i = 0 ; i < cars.size() ; i ++)
	{
		Logger::inst()->log(KLT_OUTPUT) << "Car " << i << ": pos=" << cars[i]->get_local_pos() << " vel=" << cars[i]->getCurrentSpeed() << endl;
	}
}

int Bound::get_index()
{
	return index;
}

Road* Bound::get_parent_road()
{
	return parent_road;
}

void OnBoundArrival(Entity* ent)
{
	Bound* bound = (Bound*)ent;

/*	Logger::inst()->log(KLT_OUTPUT) << "----------------------------------------------" << std::endl;
	Logger::inst()->log(KLT_OUTPUT) << "Time: " << bound->get_clock()->get_time() << std::endl;
	Logger::inst()->log(KLT_OUTPUT) << "Index: " << bound->index << std::endl;
	Logger::inst()->log(KLT_OUTPUT) << "Event type: Arrival" << std::endl;
*/
	// another arrival event
	static ExponentialDistribution exp(0.1f);
	float iat = exp.generate(); // inter arrival time
	//Logger::inst()->log(KLT_OUTPUT) << "Next car arrival time: " << bound->get_clock()->get_time() + iat << std::endl;
	Event* arr_evt = new Event(bound->get_clock()->get_time() + iat, bound, 0);
	bound->get_event_queue()->push_event(arr_evt);

	// filling data of car;
	static NormalDistribution nd(16.0f, 5.0f);
	Car* cur_car = new Car(0, bound, nd.generate());
	//Logger::inst()->log(KLT_OUTPUT) << "Current car velocity: " << cur_car->getCurrentSpeed() << std::endl;
	if(bound->get_car_count() > 0)
	{
		cur_car->set_next(bound->back());
		bound->back()->set_back(cur_car);
	}

	// updating local positions
	//cout << "Last event time: " << bound->last_event_time << std::endl;
	bound->parent_road->update_all_bounds(bound->get_clock()->get_time());
	bound->last_event_time = bound->get_clock()->get_time();

	bound->push(cur_car); 

	// test for another event types
	if(bound->get_car_count() == 1)
	{
		bound->last_event_time = bound->get_clock()->get_time();
		cur_car->set_min_to_end(bound->get_clock()->get_time() + bound->parent_road->get_length() / cur_car->getCurrentSpeed());
		Event* dep_evt = new Event(bound->get_clock()->get_time() + bound->parent_road->get_length() / cur_car->getCurrentSpeed(), bound, 1);
		bound->get_event_queue()->push_event(dep_evt);
	}
	else
	{
		// if they will collide
		if(cur_car->get_next()->getCurrentSpeed() < cur_car->getCurrentSpeed())																					  
		{
			float dv = cur_car->getCurrentSpeed() - cur_car->get_next()->getCurrentSpeed();
			float dx = cur_car->get_next()->get_local_pos() - cur_car->get_local_pos() - (cur_car->getType().length + cur_car->get_next()->getType().length) / 2;

			// setting min to end
			if(bound->get_clock()->get_time() + dx / dv < cur_car->get_next()->get_min_to_end())
			{	cur_car->set_min_to_end(bound->get_clock()->get_time() + dx / dv);
				//Logger::inst()->log(KLT_OUTPUT) << "It collide to the next at: " << bound->get_clock()->get_time() + dx / dv << endl;
				Event* col_evt = new Event(bound->get_clock()->get_time() + dx / dv, cur_car, 0);
				bound->get_event_queue()->push_event(col_evt);
			}
			else
				cur_car->set_min_to_end(cur_car->get_next()->get_min_to_end());

		}
		else
			cur_car->set_min_to_end(cur_car->get_next()->get_min_to_end());
	}

	//bound->parent_road->print_all_cars();
	bound->parent_road->append_to_file();
}

void OnBoundDeparture(Entity* ent)
{
	Bound* bound = (Bound*)ent;
	float cur_time = bound->get_clock()->get_time();

/*	Logger::inst()->log(KLT_OUTPUT) << "----------------------------------------------" << std::endl;
	Logger::inst()->log(KLT_OUTPUT) << "Time: " << bound->get_clock()->get_time() << std::endl;
	Logger::inst()->log(KLT_OUTPUT) << "Event type: Departure" << std::endl;
*/
	delete bound->pop();
	if(bound->get_car_count() > 0)
		bound->front()->set_next(0);

	if(bound->is_empty() == false)
	{
		float de = (bound->parent_road->get_length() - bound->front()->get_local_pos()) / bound->front()->getCurrentSpeed(); // time to end
		bound->front()->set_min_to_end(bound->get_clock()->get_time() + de);
		Event* dep_evt = new Event(bound->get_clock()->get_time() + de, bound, 1);
		//Logger::inst()->log(KLT_OUTPUT) << "Next departure event time: " << bound->get_clock()->get_time() + de << std::endl;
		bound->get_event_queue()->push_event(dep_evt);
	}

	// updating another collide events
	Car* cur_car = bound->front();
	Car* back_car = cur_car->get_back();
	while(back_car != NULL)
	{
		float dx = cur_car->get_local_pos() - back_car->get_local_pos() - (cur_car->getType().length + back_car->getType().length) / 2;
		float dv = cur_car->getCurrentSpeed() - back_car->getCurrentSpeed();

		if(dv < 0)
		{
			float dt = -dx / dv;

			if(cur_time + dt < cur_car->get_min_to_end())
			{
				back_car->set_min_to_end(cur_time + dt);
				Event* col_evt = new Event(cur_time + dt, back_car, 0);
				bound->get_event_queue()->push_event(col_evt);
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

		// updating the variables
		cur_car = back_car;
		back_car = cur_car->get_back();
	}

	//bound->parent_road->print_all_cars();
	bound->parent_road->append_to_file();

	//cout << "Last event time: " << bound->last_event_time << std::endl;
	bound->parent_road->update_all_bounds(bound->get_clock()->get_time());
	bound->last_event_time = bound->get_clock()->get_time();
}
