#include "texture.h"

Texture::Texture()
{
}

Texture::~Texture()
{
	delete_image();
}

void Texture::allocate(int width, int height)
{
	delete_image();
	w = width;
	h = height;

	tex_image = new GLubyte**[width];
	for(int i = 0 ; i < width ; i ++)
	{
		tex_image[i] = new GLubyte*[height];
		for(int j = 0 ; j < height ; j ++)
		{
			tex_image[i][j] = new GLubyte[4];
		}
	}
}

void Texture::delete_image()
{
	for(int i = 0 ; i < w ; i ++)
	{
		for(int j = 0 ; j < h ; j ++)
		{
			delete[](tex_image[i][j]);
		}
		delete[](tex_image[i]);
	}

	delete[](tex_image);
}

void Texture::load(int type, const char* file)
{
	FIBITMAP* bmp = FreeImage_Load(FREE_IMAGE_FORMAT(type), file);

	if(bmp)
	{
		unsigned width = FreeImage_GetWidth(bmp);
		unsigned height = FreeImage_GetHeight(bmp);

		allocate(width, height);

		for(unsigned int i = 0 ; i < width ; i ++)
		{
			for(unsigned int j = 0 ; j < height ; j ++)
			{
				RGBQUAD quad;

				FreeImage_GetPixelColor(bmp, i, j, &quad);

				tex_image[i][j][0] = quad.rgbRed;
				tex_image[i][j][1] = quad.rgbGreen;
				tex_image[i][j][2] = quad.rgbBlue;
				tex_image[i][j][3] = 255;
			}
		}

		glGenTextures(1, &tex_name);
		glBindTexture(GL_TEXTURE_2D, tex_name);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex_image);

		FreeImage_Unload(bmp);
	}
}

GLuint* Texture::get_name()
{
	return &tex_name;
}
