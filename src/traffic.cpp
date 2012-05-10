#include "traffic.h"
using namespace khagine;

Traffic::Traffic(int argc, char** argv)
{
	max_sim_time = 3600;
	strcpy(outfile, "test.log");
	for(int i = 0 ; i < argc ; i ++)
	{
		if(i == 1)
			max_sim_time = atof(argv[i]);
		else if(i == 2)
			strcpy(outfile, argv[i]);
	}

	khagine = new Khagine(argc, argv);

	CarType type0;
	type0.length = 3.0f;
	Car::addType(type0);

	init_khagine();
}

Traffic::~Traffic()
{
	delete khagine;
}

void Traffic::init_khagine()
{
	srand(time(0));
	int bound_count = 4;
	Road* road = new Road(outfile, 0.0f, 0.0f, 0.0f, bound_count, 10000.0f, 40.0f);
	for(int i = 0 ; i < bound_count ; i ++)
	{
		Bound* bound = road->get_bound(i);
		char name[10] = {0};
		sprintf(name, "bound%d", i);
		khagine->add_entity(name, bound);
		
		Event* evt = new Event(0.0f, bound, 0);
		khagine->push_event(evt);
	}
}

void Traffic::run()
{
	bool running = true;

	while(running)
	{
		if(khagine->get_time() >= max_sim_time)
			running = false;

		khagine->step(running);
	}
}
