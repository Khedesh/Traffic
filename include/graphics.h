#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <SDL/SDL.h>

#include <Khagine/Khagine.hpp>
using namespace khagine;

#include "mesh.h"
#include "obj_mesh_loader.h"
#include "c3ds_mesh_loader.h"
#include "texture_loader.h"

class Graphics
{
	SDL_Surface* screen;

	int width;
	int height;

	std::vector<Mesh*> meshes;
	Vector3df cam_pos;
	Vector3df cam_rot;

	GLuint tex_top;
	GLuint tex_down;
	GLuint tex_right;
	GLuint tex_left;
	GLuint tex_front;
	GLuint tex_back;

	GLuint tex_car;

	TextureLoader tex_loader;

	Khagine* khagine;

	void draw();
	void draw_skybox();

	bool handle_event(SDL_Event* evt);

	void reshape();

	public:

	Graphics(const char* title = "Traffic, BMMMM", int w = 800, int h = 600);
	~Graphics();

	void init_window(const char* title, int w, int h);
	void init_gl();

	void set_khagine(Khagine* khg);

	bool update();

	void toggle_fullscreen();

	void swap_buffers();

}; // end class Graphics

#endif // GRAPHICS_H
