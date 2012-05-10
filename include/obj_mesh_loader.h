#ifndef OBJ_MESH_LOADER_H
#define OBJ_MESH_LOADER_H

#include <fstream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include "mesh.h"

class ObjMeshLoader
{
	Mesh* mesh;

	char file[80];

	Index str_to_index(const char* str);

	public:

	ObjMeshLoader(const char* _file, Mesh* _mesh);
	~ObjMeshLoader();

	void load();

}; // end class ObjMeshLoader

#endif // OBJ_MESH_LOADER_H
