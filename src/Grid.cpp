#include "Grid.h"
#include "utils.h"

#include <assert.h>
#include <string.h>

#include <GL/gl.h>

const unsigned int Grid::COLOR_LINE=COLOR_RGB(0x58, 0x24, 0x91); // #582491
const unsigned int Grid::COLOR_QUAD=COLOR_RGB(200, 52, 78);

const float Grid::DEPTH=0;

Grid::Grid(int side_length)
:side(side_length)
{
//	memset(&grid[0][0], 0/*false*/, WIDTH*HEIGHT*sizeof(bool));
	for(int j=0; j<HEIGHT; ++j)
		for(int i=0; i<WIDTH; ++i)
			grid[j][i]=false;
}

void Grid::draw() const
{
	const int side1=side+1; // grid_line_width=1

	glColor4ubv((GLubyte*)&COLOR_QUAD);
	glBegin(GL_QUADS);
	for(int j=0; j<HEIGHT; ++j)
	{
		const int y1=j*side1+1, y2=y1+side;
		for(int i=0; i<WIDTH; ++i)
		{
			if(grid[j][i])
			{
				int x1=i*side1+1, x2=x1+side;
				glVertex2i(x1, y1);
				glVertex2i(x2, y1);
				glVertex2i(x2, y2);
				glVertex2i(x1, y2);
			}
		}
	}
	glEnd();

	glColor4ubv((GLubyte*)&COLOR_LINE);
	glBegin(GL_LINES);
	const int xmax=WIDTH*side1;
	const int ymax=HEIGHT*side1;
	for(int j=0; j<=ymax; j+=side1)
	{
		glVertex2i(0, j);
		glVertex2i(xmax, j);
	}
	for(int i=0; i<xmax; i+=side1)
	{
		glVertex2i(i, 0);
		glVertex2i(i, ymax);
	}
	glEnd();
}

bool Grid::collide(const Tetromino &block)
{
	int x0=0, y0=0;
	block.getPosition(x0, y0);

	for(int j=0; j<Tetromino::ORDER; ++j)
	{
		for(int i=0; i<Tetromino::ORDER; ++i)
		{
			if(!block.map(i, j))
				continue;

			int x=x0+i, y=y0+j;

			// hit a wall or the floor
			if(x<0 || x>=WIDTH || y<0)// || y>HEIGHT)
				return true;

			// hit a block IN the grid
			if(y<HEIGHT && isFilled(x, y))
				return true;
		}
	}

	return false;
}

void Grid::join(const Tetromino &block)
{
	int x0=0, y0=0;
	block.getPosition(x0, y0);
	for(int i=0; i<Tetromino::ORDER*Tetromino::ORDER; ++i)
	{
		int x=x0+i%Tetromino::ORDER;
		int y=y0+i/Tetromino::ORDER;

		if(0<=x && x<WIDTH && 0<=y && y<HEIGHT && !isFilled(x, y))
			grid[y][x]=block.map(i%Tetromino::ORDER, i/Tetromino::ORDER);
	}
}

inline bool Grid::isFilled(int x, int y) const
{
	// (i, j) => (column, row)
	return grid[y][x];
}

int Grid::remove(const int line)
{
	int lines_removed=0;
	for(int j=line; j<line+Tetromino::ORDER;)
	{
		bool removable=true;
		for(int i=0; i<WIDTH; ++i)
		{
			if(!isFilled(i, j))
			{
				removable=false;
				break;
			}
		}

		if(removable)
		{
			memcpy(&grid[j], &grid[j+1], WIDTH*(HEIGHT-1-j));
			memset(&grid[HEIGHT-1], 0/*false*/, WIDTH); // clear the top line
			++lines_removed;
		}
		else
			++j;
	}

	return lines_removed;
}
