#include "mesh.h"
using namespace std;

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

Normal Mesh::calc_normal(Vertex v1, Vertex v2, Vertex v3)
{
	Normal ret;

	Vector3df vc1, vc2;
	
	vc1.x = v1.x - v2.x;
	vc1.y = v1.y - v2.y;
	vc1.z = v1.z - v2.z;

	vc2.x = v2.x - v3.x;
	vc2.y = v2.y - v3.y;
	vc2.z = v2.z - v3.z;

	// cross product

	ret.x = vc1.y * vc2.z - vc1.z * vc2.y;
	ret.y = -vc1.x * vc2.z + vc1.z * vc2.x;
	ret.z = vc1.x * vc2.y - vc1.y * vc2.x;

	return ret;

}

void Mesh::draw()
{
	glPushMatrix();

	glBegin(GL_TRIANGLES);

	Index crnt_index;
	Normal crnt_normal;

	for(unsigned int i = 0 ; i < faces.size() ; i ++)
	{
		crnt_normal = calc_normal(vertices[faces[i].indices[0].vid],
				vertices[faces[i].indices[1].vid], 
				vertices[faces[i].indices[2].vid]);
		// first
		crnt_index = faces[i].indices[0];
		glNormal3f(crnt_normal.x, crnt_normal.y, crnt_normal.z);
		// does it have texture??
		if(texcoords.size() != 0)
		{
			glTexCoord2f(texcoords[crnt_index.tid].x, texcoords[crnt_index.tid].y);
		}
		glVertex3f(vertices[crnt_index.vid].x, vertices[crnt_index.vid].y, vertices[crnt_index.vid].z);

		// second
		crnt_index = faces[i].indices[1];
		glNormal3f(crnt_normal.x, crnt_normal.y, crnt_normal.z);
		// does it have texture??
		if(texcoords.size() != 0)
		{
			glTexCoord2f(texcoords[crnt_index.tid].x, texcoords[crnt_index.tid].y);
		}
		glVertex3f(vertices[crnt_index.vid].x, vertices[crnt_index.vid].y, vertices[crnt_index.vid].z);

		// third
		crnt_index = faces[i].indices[2];
		glNormal3f(crnt_normal.x, crnt_normal.y, crnt_normal.z);
		// does it have texture??
		if(texcoords.size() != 0)
		{
			glTexCoord2f(texcoords[crnt_index.tid].x, texcoords[crnt_index.tid].y);
		}
		glVertex3f(vertices[crnt_index.vid].x, vertices[crnt_index.vid].y, vertices[crnt_index.vid].z);
	}

	glEnd();

	glPopMatrix();
}
