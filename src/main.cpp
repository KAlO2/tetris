#include <stdio.h>

#include "Grid.h"
#include "Engine.h"

#include <GL/gl.h>
#include <GL/glu.h>

#ifdef USE_GLUT
#include <GL/glut.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#endif

const int FRAMES_PER_SECOND=60;
static const unsigned int interval=750; // milliseconds
Engine engine;

#ifdef USE_GLUT

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

#else

SDL_Window* window=NULL;
Uint32 timer(Uint32 interval, void* param)
{
	engine.update();
	glClear(GL_COLOR_BUFFER_BIT);
	engine.draw();
	
	return interval;
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	engine.draw();
}

#endif /* USE_GLUT */



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

#ifdef USE_GLUT
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

#else

	SDL_GLContext context;
    if(SDL_Init(SDL_INIT_EVERYTHING)!=0)
	{
		printf("Unable to initialize SDL: %s\n", SDL_GetError());;
    	SDL_Quit();
    	return 1;
	}
	else
	{
/*
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_SINGLE_BUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
*/
		window=SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_MOUSE_FOCUS);
		if(!window)
		{
			printf("Unable to create window: %s\n", SDL_GetError());
			SDL_Quit();
			return 2;
		}
		
		context=SDL_GL_CreateContext(window);
		SDL_GL_SetSwapInterval(1);

		if(!initGL(width, height))
		{
			printf("OpenGL initialized error!\n");
			SDL_GL_DeleteContext(context);
			SDL_DestroyWindow(window);
			return 3;
		}
	}
	
	SDL_AddTimer(interval, timer, NULL);
	
	SDL_Event event;
	bool quit=false;
	while(!quit)
	{
		SDL_PollEvent(&event);
		
		if(event.type==SDL_QUIT)
			break;
		else if(event.type==SDL_KEYDOWN)
		{
			switch(event.key.keysym.sym)
			{
				case SDLK_LEFT:	 engine.handleKey(Engine::LEFT);  break;
				case SDLK_RIGHT: engine.handleKey(Engine::RIGHT); break;
				case SDLK_DOWN:  engine.handleKey(Engine::DOWN);  break;
				case SDLK_UP:    engine.handleKey(Engine::SHIFT); break;
				case SDLK_ESCAPE: quit=true; break;
			}
		}
		
		glClear(GL_COLOR_BUFFER_BIT);
		engine.draw();
		SDL_GL_SwapWindow(window);
	}
	
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	
#endif /* USE_GLUT */

	return 0;
}


