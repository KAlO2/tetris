#ifndef TETRIS_ENGINE_H_
#define TETRIS_ENGINE_H_

#include "Grid.h"
#include "Tetromino.h"

class Engine
{
public:
	enum Key
	{
		LEFT,
		RIGHT,
		DOWN,
		SHIFT,
	};

private:
	Grid grid;
	Tetromino tetromino;

	int score;
	bool alive;
public:
	Engine();
	~Engine();

	int getGridWidth() const {return grid.getSideLength()+1;}
	bool isAlive() const {return alive;}

	void handleKey(Key key);
	void draw() const;
	void update();
};

#endif /* TETRIS_ENGINE_H_ */
