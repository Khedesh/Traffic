#include "Traffic.hpp"
using namespace khagine;

int main(int argc, char* argv[])
{
	Traffic* traffic = new Traffic(argc, argv);

	traffic->run();

	delete traffic;

	return 0;
}
