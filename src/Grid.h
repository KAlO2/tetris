#ifndef TETRIS_GRID_H_
#define TETRIS_GRID_H_

#include "Tetromino.h"

class Grid
{
public:
	static const int WIDTH=10, HEIGHT=20;
	static const float DEPTH;
	static const unsigned int COLOR_LINE;
	static const unsigned int COLOR_QUAD;

private:
	friend class Engine;

	int side; // square side length

	bool grid[HEIGHT][WIDTH];

public:
	Grid(int side_length=20);

	bool isFilled(int x, int y) const;
	void setSideLength(int length) {side=length;}
	int getSideLength() const {return side;}

	void draw() const;

	bool collide(const Tetromino &block);
	void join(const Tetromino &block);
	int remove(const int line);
};

#endif /* TETRIS_GRID_H_ */

