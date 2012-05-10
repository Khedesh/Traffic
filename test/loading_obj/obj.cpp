#include "obj.h"
using namespace std;

Index str_to_index(const char* str)
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
	ret.nid = atoi(tmp);
	//fprintf(stdout, "n: %s\n", tmp);
	memset(tmp, '\0', strlen(tmp));

	return ret;
}

void Mesh::load(const char* file)
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
			vertices.push_back(tmp);
		}
		else if(strcmp(first, "vt") == 0)
		{
			TexCoord tmp;
			tmp.u = atof(second);
			tmp.v = atof(third);
			texcoords.push_back(tmp);
		}
		else if(strcmp(first, "vn") == 0)
		{
			Normal tmp;
			tmp.x = atof(second);
			tmp.y = atof(third);
			tmp.z = atof(fourth);
			normals.push_back(tmp);
		}
		else if(strcmp(first, "f") == 0)
		{
			Face tmp;
			tmp.indices[0] = str_to_index(second);
			tmp.indices[1] = str_to_index(third);
			tmp.indices[2] = str_to_index(fourth);
			faces.push_back(tmp);
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
			strcpy(name, second);
		}
		else if(strcmp(first, "g") == 0)
		{
			// forgot
		}
	}

}

void Mesh::draw()
{
	glBegin(GL_TRIANGLES);

	Index crnt_index;

	for(unsigned int i = 0 ; i < faces.size() ; i ++)
	{
		// first
		crnt_index = faces[i].indices[0];
		glNormal3f(normals[crnt_index.nid].x, normals[crnt_index.nid].y, normals[crnt_index.nid].z);
		glVertex3f(vertices[crnt_index.vid].x, vertices[crnt_index.vid].y, vertices[crnt_index.vid].z);
		glTexCoord2f(texcoords[crnt_index.tid].u, texcoords[crnt_index.tid].v);

		// second
		crnt_index = faces[i].indices[1];
		glNormal3f(normals[crnt_index.nid].x, normals[crnt_index.nid].y, normals[crnt_index.nid].z);
		glVertex3f(vertices[crnt_index.vid].x, vertices[crnt_index.vid].y, vertices[crnt_index.vid].z);
		glTexCoord2f(texcoords[crnt_index.tid].u, texcoords[crnt_index.tid].v);

		// third
		crnt_index = faces[i].indices[2];
		glNormal3f(normals[crnt_index.nid].x, normals[crnt_index.nid].y, normals[crnt_index.nid].z);
		glVertex3f(vertices[crnt_index.vid].x, vertices[crnt_index.vid].y, vertices[crnt_index.vid].z);
		glTexCoord2f(texcoords[crnt_index.tid].u, texcoords[crnt_index.tid].v);
	}

	glEnd();
}
