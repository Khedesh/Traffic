#include "obj_mesh_loader.h"
using namespace std;

ObjMeshLoader::ObjMeshLoader(const char* _file, Mesh* _mesh)
{
	strcpy(file, _file);

	mesh = _mesh;
}

ObjMeshLoader::~ObjMeshLoader()
{
}

Index ObjMeshLoader::str_to_index(const char* str)
{
	Index ret;

	int i1 = -1;
	int i2 = -1;

	// getting the '/' indices
	for(unsigned int i = 0 ; i < strlen(str) ; i ++)
	{
		if(str[i] == '/')
		{
			if(i1 == -1)
			{
				i1 = i;
			}
			else
			{
				i2 = i;
			}
		}
	}

	// getting the {v,t,n} indices
	// vertex
	char tmp[10] = {0};
	strncpy(tmp, str, i1);
	ret.vid = atoi(tmp);
	//fprintf(stdout, "v: %s\n", tmp);
	memset(tmp, '\0', strlen(tmp));

	// texcoord
	strncpy(tmp, str + i1 + 1, i2 - i1 - 1);
	ret.tid = atoi(tmp);
	//fprintf(stdout, "t: %s\n", tmp);
	memset(tmp, '\0', strlen(tmp));

	// normal
	strcpy(tmp, str + i2 + 1);
	//ret.y = atoi(tmp);
	//fprintf(stdout, "n: %s\n", tmp);
	memset(tmp, '\0', strlen(tmp));

	return ret;

}

void ObjMeshLoader::load()
{
	ifstream fin(file, ios::in);

	char line[320];
	while(fin.good())
	{
		fin.getline(line, 320);

		char first[80];
		char second[80];
		char third[80];
		char fourth[80];

		float minx = 0.0f;
		float maxx = 0.0f;
		float miny = 0.0f;
		float maxy = 0.0f;
		float minz = 0.0f;
		float maxz = 0.0f;

		sscanf(line, "%s%s%s%s", first, second, third, fourth);

		if(first[0] == '#')
		{
			// this is a comment
			// do nothing
		}
		else if(strcmp(first, "v") == 0)
		{
			Vertex tmp;
			tmp.x = atof(second);
			tmp.y = atof(third);
			tmp.z = atof(fourth);
			mesh->vertices.push_back(tmp);

			// getting bounding box
			if(tmp.x < minx)
				minx = tmp.x;
			if(tmp.x > maxx)
				maxx = tmp.x;

			if(tmp.y < miny)
				miny = tmp.y;
			if(tmp.y > maxy)
				maxy = tmp.y;

			if(tmp.z < minz)
				minz = tmp.z;
			if(tmp.z > maxz)
				maxz = tmp.z;

			// setting bounding box
			mesh->bbox.l = maxx - minx;
			mesh->bbox.w = maxy - miny;
			mesh->bbox.h = maxz - minz;

		}
		else if(strcmp(first, "vt") == 0)
		{
			TexCoord tmp;
			tmp.x = atof(second);
			tmp.y = atof(third);
			mesh->texcoords.push_back(tmp);
		}
		else if(strcmp(first, "vn") == 0)
		{
			Normal tmp;
			tmp.x = atof(second);
			tmp.y = atof(third);
			tmp.z = atof(fourth);
		}
		else if(strcmp(first, "f") == 0)
		{
			Face tmp;
			tmp.indices[0] = str_to_index(second);
			tmp.indices[1] = str_to_index(third);
			tmp.indices[2] = str_to_index(fourth);
			mesh->faces.push_back(tmp);
		}
		else if(strcmp(first, "mtllib") == 0)
		{
			// forgot
		}
		else if(strcmp(first, "usemtl") == 0)
		{
			// forgot
		}
		else if(strcmp(first, "o") == 0)
		{
			//strcpy(name, second);
		}
		else if(strcmp(first, "g") == 0)
		{
			// forgot
		}
	}
}
