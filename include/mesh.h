#ifndef MESH_H
#define MESH_H

#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>
#include "core.h"

typedef Vector3df Vertex;
typedef Vector3df Normal;
typedef Vector2df TexCoord;

struct Index
{
	int vid;
	int tid;

	Index()
	{
		vid = 0;
		tid = 0;
	}
};

struct Face
{
	Index indices[3];
};

class Mesh
{
	friend class ObjMeshLoader;
	friend class C3DSMeshLoader;

	char name[80];

	BBox3df bbox;

	std::vector<Vertex> vertices;
	std::vector<TexCoord> texcoords;
	std::vector<Face> faces;

	Normal calc_normal(Vertex v1, Vertex v2, Vertex v3);

	public:

	Mesh();
	~Mesh();

	void draw();

}; // end class Mesh

#endif // MESH_H
