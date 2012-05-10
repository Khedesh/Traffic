#include "texture_loader.h"

bool TextureLoader::initialised = false;

TextureLoader::TextureLoader()
{
	if(initialised != true)
	{
		FreeImage_Initialise();
	}
}

TextureLoader::~TextureLoader()
{
}

void TextureLoader::load(GLuint* tex_name, FREE_IMAGE_FORMAT fif, const char* file)
{
	FIBITMAP* image = FreeImage_Load(fif, file);

	int tex_width = FreeImage_GetWidth(image);
	int tex_height = FreeImage_GetHeight(image);


	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, tex_name);
	glBindTexture(GL_TEXTURE_2D, *tex_name);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_DECAL);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_DECAL);

	//printf("BPP: %d\n", FreeImage_GetBPP(image));
	
	int bpp = FreeImage_GetBPP(image) / 8;

	GLenum format = GL_RGBA;

	if(bpp == 3)
		format = GL_RGB;

	gluBuild2DMipmaps(GL_TEXTURE_2D, bpp, tex_width, tex_height, format, GL_UNSIGNED_BYTE, FreeImage_GetBits(image));
}
