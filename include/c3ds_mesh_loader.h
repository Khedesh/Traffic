#ifndef C3DS_MESH_LOADER_H
#define C3DS_MESH_LOADER_H

#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mesh.h"

class C3DSMeshLoader
{
	char file[80];

	Mesh* mesh;

	public:

	C3DSMeshLoader(const char* _file, Mesh* _mesh);
	~C3DSMeshLoader();

	int load();

}; // end class C3DSMeshLoader

#endif // C3DS_MESH_LOADER_H
