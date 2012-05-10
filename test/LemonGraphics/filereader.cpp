#include "filereader.h"

FileReader::FileReader(const char* _file)
{
	strcpy(file, _file);
}

FileReader::~FileReader()
{
}

void FileReader::read()
{
	ifstream fin(file, ios::in);

	Chunk ch;

	while(fin.good())
	{
		string line;

		fin >> line;

		if(line == "front")
		{
			fin >> ch.frame_time;
		}
		else if(line == "car")
		{
			Chunk::Pair p;

			fin >> p.pos >> p.vel;

			ch.pairs.push_back(p);
		}
		else if(line == "end")
		{
			chunks.push_back(ch);
			ch.pairs.clear();
		}
	}
}

Chunk FileReader::get_chunk(int index)
{
	return chunks[index];
}

int FileReader::get_size()
{
	return chunks.size();
}
