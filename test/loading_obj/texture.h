#ifndef TEXTURE_H
#define TEXTURE_H

#include <FreeImage.h>
#include <GL/gl.h>
#include <GL/glu.h>

struct Texture
{
	GLuint tex_name;

	int w;
	int h;

	GLubyte*** tex_image;

	public:

	Texture();
	~Texture();

	void allocate(int width, int height);
	void delete_image();

	void load(int type, const char* file);

	GLuint* get_name();
};

#endif // TEXTURE_H
