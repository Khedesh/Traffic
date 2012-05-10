#ifndef OBJ_H
#define OBJ_H

#include <vector>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>

struct Vertex
{
	float x;
	float y;
	float z;
};
typedef Vertex Normal;

struct TexCoord
{
	float u;
	float v;
};

struct Index
{
	int vid;
	int tid;
	int nid;
};

struct Face
{
	Index indices[3];
};

struct Mesh
{
	std::vector<Vertex> vertices;
	std::vector<TexCoord> texcoords;
	std::vector<Normal> normals;
	std::vector<Face> faces;

	char name[80];

	void load(const char* file);

	void draw();
};

#endif // OBJ_H
