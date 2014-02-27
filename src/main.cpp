#include <stdio.h>

#include "Grid.h"
#include "Engine.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

const int FRAMES_PER_SECOND=60;
static const unsigned int interval=750; // milliseconds
Engine engine;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	engine.draw();
	glutSwapBuffers();
}

void special(int key, int x, int y)
{
	switch(key)
	{
	case GLUT_KEY_LEFT:
		engine.handleKey(Engine::LEFT);
		break;
	case GLUT_KEY_RIGHT:
		engine.handleKey(Engine::RIGHT);
		break;
	case GLUT_KEY_DOWN:
		engine.handleKey(Engine::DOWN);
		break;
	case GLUT_KEY_UP:
		engine.handleKey(Engine::SHIFT);
		break;
	}
	display();
}

void timer(int value)
{
	glutSpecialFunc(NULL);
	engine.update();
	glutSpecialFunc(special);
	display();
	
	if(engine.isAlive())
		glutTimerFunc(interval, timer, value);
}

void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 27: // ESC ASCII code
		exit(EXIT_SUCCESS);
		break;
	}
}

bool initGL(int width, int height)
{
	GLenum error=GL_NO_ERROR;
	
	glClearColor(0, 0, 0.25, 0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, (GLdouble)width, 0, (GLdouble)height, 0, 1.0);
	glDisable(GL_DEPTH_TEST);
	
	error = glGetError();
	if(error!=GL_NO_ERROR)
	{
		printf("Error initializing OpenGL! %s\n", gluErrorString(error));
		return false;
	}
	
	return true;
}

int main( int argc, char **argv )
{
	const char* title="Tetris";
	int width =Grid::WIDTH *engine.getGridWidth();
	int height=Grid::HEIGHT*engine.getGridWidth();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(title);
	
	initGL(width, height);
	
	timer(0);

	glutDisplayFunc(display);
	glutSpecialFunc(special);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}


