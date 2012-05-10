#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <FreeImage.h>
#include <stdio.h>

class TextureLoader
{
	static bool initialised;

	public:

	TextureLoader();
	~TextureLoader();

	void load(GLuint* tex_name, FREE_IMAGE_FORMAT fif, const char* file);
};

#endif // TEXTURE_LOADER_H
