#ifndef TRAFFIC_H
#define TRAFFIC_H

#include <Khagine/Khagine.hpp>
#include "Traffic.hpp"

class Traffic
{
	khagine::Khagine* khagine;
	int max_sim_time;
	char outfile[80];

	// initializing khagine
	void init_khagine();

	public:

	Traffic(int argc, char** argv);
	~Traffic();

	void run();

}; // end class Traffic
	

#endif // TRAFFIC_H
