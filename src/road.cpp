#include "road.h"
#include "car.h"
using namespace std;

Road::Road(const char* _file, double x, double y, double z, int bcount, float _length, int _max_speed, float _angle) : pos(x, y, z)
{
	max_speed = _max_speed;
	angle = _angle;
	length = _length;

	for(int i = 0 ; i < bcount ; i ++)
	{
		Bound* tmp_bound = new Bound(this, false);
		bounds.push_back(tmp_bound);
	}

	strcpy(file, _file);
	
	fptr = fopen(file, "wa");
}

Road::~Road()
{
	unsigned count = bounds.size();
	for(unsigned i = 0 ; i < count ; i ++)
	{
		delete bounds[i];
	}
	bounds.clear();
}

void Road::push_car(Car* m_car, int index)
{
	bounds[index]->push(m_car);
}

Car* Road::pop_car(int index)
{
	return bounds[index]->pop();
}

bool Road::is_empty(int index)
{
	return bounds[index]->is_empty();
}

int Road::get_bound_count()
{
	return bounds.size();
}

Bound* Road::get_bound(int index)
{
	return bounds[index];
}

float Road::get_length()
{
	return length;
}

void Road::update_all_bounds(float time)
{
	for(unsigned i = 0 ; i < bounds.size() ; i ++)
	{
		bounds[i]->update_cars_position(time);
	}
}

void Road::print_all_cars()
{
	for(unsigned i = 0 ; i < bounds.size() ; i ++)
	{
		Logger::inst()->log(KLT_OUTPUT) << "*****" << endl;
		Logger::inst()->log(KLT_OUTPUT) << "Bound: " << i << endl;
		bounds[i]->print_all_cars();
	}
}

void Road::append_to_file()
{
	/*std::ofstream fout(file, ios::out | ios::app);

	fout << "------------------------------------------" << endl;
	fout << "frame " << bounds[0]->get_clock()->get_time() << endl;

	for(unsigned i = 0 ; i < bounds.size() ; i ++)
	{
		fout << "road " << i << endl;
		Bound* b = bounds[i];
		for(int j = 0 ; j < b->get_car_count() ; j ++)
		{
			fout << "car " << b->get_car(j)->get_local_pos() << " " << b->get_car(j)->getCurrentSpeed() << endl;
		}
		fout << "endroad" << endl;
	}

	fout << "end" << endl;*/

	fprintf(fptr, "------------------------------------------\n");
	fprintf(fptr, "frame %f\n", bounds[0]->get_clock()->get_time());

	for(unsigned i = 0 ; i < bounds.size() ; i ++)
	{
		fprintf(fptr, "road %d\n", i);
		Bound* b = bounds[i];
		for(int j = 0 ; j < b->get_car_count() ; j ++)
		{
			fprintf(fptr, "car %f %f\n", b->get_car(j)->get_local_pos(), b->get_car(j)->getCurrentSpeed());
		}
		fprintf(fptr, "endroad\n");
	}

	fprintf(fptr, "end\n");
}
