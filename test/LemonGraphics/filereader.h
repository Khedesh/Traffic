#ifndef FILEREADER_H
#define FILEREADER_H

#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

struct Chunk
{
	float frame_time;

	struct Pair
	{
		float vel;
		float pos;
	};

	vector<Pair> pairs;
};

class FileReader
{
	char file[80];

	vector<Chunk> chunks;

	public:

	FileReader(const char* _file);
	~FileReader();

	void read();

	Chunk get_chunk(int index);

	int get_size();
};

#endif // FILEREADER_H
