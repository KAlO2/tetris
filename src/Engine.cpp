#include "Engine.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Engine::Engine()
:grid()
,tetromino(Tetromino::BLOCK_O)
,score(0)
,alive(true)
{
	srand((unsigned int)time(NULL));
	tetromino.reload();
}

Engine::~Engine()
{
	alive=false;
}

void Engine::handleKey(Key key)
{
	// suppose we can step forward the tetromino,
	// if the assumption fails, just discard the copied one.
	Tetromino tetromino2(tetromino);

	switch(key)
	{
	case LEFT:  tetromino2.move(-1, 0);  break;
	case RIGHT: tetromino2.move(+1, 0);  break;
	case DOWN:  tetromino2.move(0, -1);  break;
	case SHIFT: tetromino2.rotate(true); break;
	}

	if(!grid.collide(tetromino2))
		tetromino=tetromino2;
}

void Engine::draw() const
{
	grid.draw();
	tetromino.draw(grid.getSideLength());
}

void Engine::update()
{
	static int bonus[1+Tetromino::ORDER]={0, 10, 22, 35, 50};
	
	tetromino.move(0, -1); // fall down
	if(grid.collide(tetromino))
	{
		tetromino.move(0, +1); // recover
		grid.join(tetromino);

//		score+=Grid::WIDTH*grid.remove(tetromino.y);
//		use some bonus strategy to gain more fun!
		int lines=grid.remove(tetromino.y);
		score+=bonus[lines];
		
		tetromino.reload();

		// check for collision at the top
		if(grid.collide(tetromino))
		{
			alive=false;
			printf("GAME OVER!\n");
			printf("your score is %d.\n", score);
		}
	}
}
