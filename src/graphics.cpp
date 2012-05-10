#include "graphics.h"

Graphics::Graphics(const char* title, int w, int h)
{
	init_window(title, w, h);
	init_gl();
}

Graphics::~Graphics()
{
	//delete tTexture;
	SDL_FreeSurface(screen);
	SDL_Quit();
}

void Graphics::reshape()
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, 1.0f /*float(width) / height*/, 1.0f, 1000000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}

void Graphics::init_window(const char* title, int w, int h)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	screen = SDL_SetVideoMode(w, h, 32, SDL_HWSURFACE | SDL_OPENGL);
	SDL_WM_SetCaption(title, NULL);
	SDL_EnableKeyRepeat(1, 10);

	width = w;
	height = h;
}

void Graphics::init_gl()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glShadeModel(GL_SMOOTH);

	// opt.
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	//glEnable(GL_CULL_FACE);

	// light
	glEnable(GL_LIGHTING);

	GLfloat light_ambient[] = {0.3f, 0.3f, 0.3f, 1.0f};
	GLfloat light_diffuse[] = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat light_position[] = {0.0f, 10.0f, -10.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHT0);

	// material
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	GLfloat mat_specref[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specref);
	glMateriali(GL_FRONT, GL_SHININESS, 128);

	// other
	glEnable(GL_NORMALIZE);
	glEnable(GL_AUTO_NORMAL);
	
	/*// texture test
	static bool tFlag = true;
	if(tFlag)
	{
		tLoader.load(&tex_test, FIF_JPEG, "data/sky12.jpg");
		tFlag = false;
	}*/

	tex_loader.load(&tex_top, FIF_JPEG, "data/skybox/003/top62.jpg");
	tex_loader.load(&tex_down, FIF_JPEG, "data/skybox/003/top62.jpg");
	tex_loader.load(&tex_right, FIF_JPEG, "data/skybox/003/right62.jpg");
	tex_loader.load(&tex_left, FIF_JPEG, "data/skybox/003/left62.jpg");
	tex_loader.load(&tex_front, FIF_JPEG, "data/skybox/003/front62.jpg");
	tex_loader.load(&tex_back, FIF_JPEG, "data/skybox/003/back62.jpg");

	tex_loader.load(&tex_car, FIF_BMP, "data/texture/spaceshiptexture.bmp");
}

void Graphics::set_khagine(Khagine* khg)
{
	khagine = khg;
}

bool Graphics::update()
{
	bool ret = true;

	SDL_Event evt;
	if(SDL_PollEvent(&evt))
	{
		ret = handle_event(&evt);
	}

	reshape();

	draw();

	swap_buffers();

	return ret;
}

bool Graphics::handle_event(SDL_Event* evt)
{
	bool running = true;

	if(evt->type == SDL_QUIT)
		running = false;
	else if(evt->type == SDL_KEYDOWN)
	{
		printf("Key pressed.\n");
		const float foot_step = 0.5f;
		unsigned char key = evt->key.keysym.sym;


		if(key == 'q')
			running = false;
		else if(key == 'd')
			cam_pos.x += foot_step;
		else if(key == 'a')
			cam_pos.x -= foot_step;
		else if(key == 's')
			cam_pos.z += foot_step;
		else if(key == 'w')
			cam_pos.z -= foot_step;
		else if(key == 'e')
			cam_pos.y += foot_step;
		else if(key == 'c')
			cam_pos.y -= foot_step;

		else if(key == 'j')
			cam_rot.x ++;
		else if(key == 'u')
			cam_rot.x --;
		else if(key == 'k')
			cam_rot.y ++;
		else if(key == 'h')
			cam_rot.y --;
	}

	return running;

}

void Graphics::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// transforming
	glTranslatef(-cam_pos.x, -cam_pos.y, -cam_pos.z);
	glRotatef(cam_rot.x, 1.0f, 0.0f, 0.0f);
	glRotatef(cam_rot.y, 0.0f, 1.0f, 0.0f);
	glRotatef(cam_rot.z, 0.0f, 0.0f, 1.0f);

	// drawing skybox
	glPushMatrix();
	glScalef(1000.0f, -1000.0f, 1000.0f);
	draw_skybox();
	glPopMatrix();

	// draw a test mesh
	static Mesh test_mesh;
	static C3DSMeshLoader loader("data/mesh/spaceship.3ds", &test_mesh);
	static bool flag = false;
	if(!flag)
	{
		loader.load();
		flag = true;
	}

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_car);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glEnd();
	glTranslatef(0.0f, 0.0f, -100.0f);
	test_mesh.draw();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void Graphics::draw_skybox()
{
	glEnable(GL_TEXTURE_2D);
	// top
	glBindTexture(GL_TEXTURE_2D, tex_top);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glEnd();

	// down
	glBindTexture(GL_TEXTURE_2D, tex_down);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glEnd();

	// right
	glBindTexture(GL_TEXTURE_2D, tex_right);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();

	// left
	glBindTexture(GL_TEXTURE_2D, tex_left);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glEnd();
	
	// front
	glBindTexture(GL_TEXTURE_2D, tex_front);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();

	// back
	glBindTexture(GL_TEXTURE_2D, tex_back);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void Graphics::toggle_fullscreen()
{
	SDL_WM_ToggleFullScreen(screen);
}

void Graphics::swap_buffers()
{
	SDL_GL_SwapBuffers();
}
