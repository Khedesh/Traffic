#include "Traffic.hpp"
#include <GL/glut.h>

namespace 
{
	Vector3df cam_pos;
	Mesh test_mesh(0.0f, 0.0f, -100.0f);

} // end namespace

void init_scene()
{
	ObjMeshLoader loader("data/spaceship.obj", &test_mesh);
	loader.load();
}

bool handle_event(SDL_Event* evt)
{
	bool running = true;

	if(evt->type == SDL_QUIT)
		running = false;
	else if(evt->type == SDL_KEYDOWN)
	{
		unsigned char key = evt->key.keysym.sym;

		if(key == 'q')
			running = false;
		else if(key == 'd')
			cam_pos.x ++;
		else if(key == 'a')
			cam_pos.x --;
		else if(key == 's')
			cam_pos.z ++;
		else if(key == 'w')
			cam_pos.z --;
		else if(key == 'e')
			cam_pos.y ++;
		else if(key == 'c')
			cam_pos.y --;
	}

	return running;
}

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glTranslatef(-cam_pos.x, -cam_pos.y, -cam_pos.z);

	glPushMatrix();

	glColor3f(0.1f, 0.5f, 0.8f);
	test_mesh.draw();

	glPopMatrix();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	Graphics grp("Traffic, BMMMM");

	init_scene();

	grp.set_event_func(handle_event);
	grp.set_draw_func(draw);
	SDL_EnableKeyRepeat(1, 30);

	bool running = true;

	while(running)
	{
		running = grp.update();
		grp.swap_buffers();
	}

	return 0;
}
