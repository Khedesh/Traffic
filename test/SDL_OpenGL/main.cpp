#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <FreeImage.h>

namespace
{
	int w;
	int h;

	static GLuint tex_name;
}

GLuint add_texture(FREE_IMAGE_FORMAT fif, const char* file)
{
	GLuint tex_ret;

	FIBITMAP* image = FreeImage_Load(fif, file);

	int tex_width = FreeImage_GetWidth(image);
	int tex_height = FreeImage_GetHeight(image);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, &tex_ret);
	glBindTexture(GL_TEXTURE_2D, tex_ret);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_DECAL);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_DECAL);

	gluBuild2DMipmaps(GL_TEXTURE_2D, FreeImage_GetBPP(image) / 8, tex_width, tex_height, GL_RGBA, GL_UNSIGNED_BYTE, image->data);

	return tex_ret;
}

void init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	tex_name = add_texture(FIF_JPEG, "BG.jpg");

}

void reshape()
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, 1.0f, 1.0f, 100000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glTranslatef(-0.5f, -0.5f, -2.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_name);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 0.0f, -1.0f);
	glEnd();
}

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	w = 800; h = 600;
	SDL_SetVideoMode(w, h, 32, SDL_HWSURFACE | SDL_OPENGL);

	bool running = true;
	init();

	while(running)
	{
		SDL_Event evt;
		if(SDL_PollEvent(&evt))
		{
			if(evt.type == SDL_QUIT)
				running = false;
			else if(evt.type == SDL_KEYDOWN)
			{
				unsigned char key = evt.key.keysym.sym;

				if(key == 'q')
					running = false;
			}
		}

		reshape();
		display();

		SDL_GL_SwapBuffers();
	}

	SDL_Quit();

	return 0;
}
