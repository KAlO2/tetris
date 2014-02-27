#ifndef TETRIS_TETROMINO_H_
#define TETRIS_TETROMINO_H_

#include <stdlib.h>
#include <stdio.h>

#include <GL/gl.h>

class Tetromino
{
public:
	static const int ORDER=4; // 4x4 block

	enum Block
	{
		BLOCK_O,
		BLOCK_I,
		BLOCK_J,
		BLOCK_L,
		BLOCK_T,
		BLOCK_Z,
		BLOCK_S,
		BLOCK_NB // number of blocks, internal usage.
	};

private:
	static const unsigned int COLOR;
	static const float DEPTH;

	static const unsigned int BLOCKS[BLOCK_NB]; // must be the same order with BLOCK_X

private:
	friend class Engine;

	Block block;
	int pivot; // 0,1,2,3 -> 0, 90, 180, 270 degrees.
	int x,y;   // in Grid coordinate.
	GLuint color;

public:
	Tetromino();
	Tetromino(Block block);
	void reload();

	inline void setPosition(int x, int y)         {this->x=x; this->y=y;}
	inline void getPosition(int &x, int &y) const {x=this->x; y=this->y;}

	inline void setBlock(Block block) {this->block=block;}
	inline Block getBlock() const     {return block;}

	bool map(int x, int y) const;

	inline void move(int dx, int dy) {x+=dx; y+=dy;}

	/**
	 * rotate the tetronimo, there are 4 directions.
	 *
	 * @param ccw true means rotate counter clockwise, false means clockwise.
	 * counter clockwise: top->left->down->right->top
	 */
	inline void rotate(bool ccw=true) {pivot=(pivot+(ccw?1:3))&3;}

	/**
	 * draw the tetromino
	 *
	 * @param side the length of a square, not the block side length.
	 */
	void draw(const int side) const;
};

#endif /* TETRIS_TETROMINO_H_ */
