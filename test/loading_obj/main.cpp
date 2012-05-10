#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>

#include "obj.h"
#include "texture.h"

namespace 
{
	float cx, cy, cz;
	float rx, ry, rz;
}

/*	Create checkerboard texture	*/
#define	checkImageWidth 64
#define	checkImageHeight 64
static GLubyte checkImage[checkImageHeight][checkImageWidth][4];

#ifdef GL_VERSION_1_1
static GLuint texName;
#endif

void makeCheckImage(void)
{
	int i, j, c;

	for (i = 0; i < checkImageHeight; i++) {
		for (j = 0; j < checkImageWidth; j++) {
			c = ((((i&0x8)==0)^((j&0x8))==0))*255;
			checkImage[i][j][0] = (GLubyte) c;
			checkImage[i][j][1] = (GLubyte) c;
			checkImage[i][j][2] = (GLubyte) c;
			checkImage[i][j][3] = (GLubyte) 255;
		}
	}
}


void init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glShadeModel(GL_SMOOTH);

	cx = cy = 0.0f;
	cz = -100.0f;
	rx = ry = rz = 0.0f;

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	makeCheckImage();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

#ifdef GL_VERSION_1_1
	glGenTextures(1, &texName);
	glBindTexture(GL_TEXTURE_2D, texName);
#endif

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
#ifdef GL_VERSION_1_1
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth, checkImageHeight, 
			0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);
#else
	glTexImage2D(GL_TEXTURE_2D, 0, 4, checkImageWidth, checkImageHeight, 
			0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);
#endif
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	glTranslatef(cx, cy, cz);
	glRotatef(rx, 1.0f, 0.0f, 0.0f);
	glRotatef(ry, 0.0f, 1.0f, 0.0f);
	glRotatef(rz, 0.0f, 0.0f, 1.0f);

	/*glBegin(GL_QUADS);
	  glColor3f(0.5f, 1.0f, 0.5f);
	  glVertex3f(-200.0f, -200.0f, 0.0f);
	  glVertex3f(200.0f, -200.0f, 0.0f);
	  glVertex3f(200.0f, 200.0f, 0.0f);
	  glVertex3f(-200.0f, 200.0f, 0.0f);
	  glEnd();
	 */

	glPushMatrix();
	glTranslatef(40.0f, 25.0f, 10.0f);
	glRotatef(90.0f, -1.0f, 0.0f, 0.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texName);

	Mesh mesh;
	mesh.load("untitled.obj");
	mesh.draw();
	glPopMatrix();

	glPopMatrix();

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, float(w) / h, 0.2f, 100000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
	if(key == 'q')
	{
		exit(0);
	}
	else if(key == 'w')
	{
		cz += 0.1f;
	}
	else if(key == 's')
	{
		cz -= 0.1f;
	}
	else if(key == 'a')
	{
		cx += 0.1f;
	}
	else if(key == 'd')
	{
		cx -= 0.1f;
	}
	else if(key == 'e')
	{
		cy -= 0.1f;
	}
	else if(key == 'c')
	{
		cy += 0.1f;
	}
	else if(key == 'u')
	{
		rx -= 0.5f;
	}
	else if(key == 'j')
	{
		rx += 0.5f;
	}
	else if(key == 'k')
	{
		ry += 0.5f;
	}
	else if(key == 'h')
	{
		ry -= 0.5f;
	}
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_RGBA | GLUT_STENCIL | GLUT_DEPTH | GLUT_DOUBLE);
	glutCreateWindow(".obj file loader");

	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
	return 0;
}
