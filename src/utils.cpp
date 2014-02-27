#include <string.h>
#include <assert.h>

const char * const BLOCK_STR[Tetromino::BLOCK_NB]=
{
// BLOCK_O,
	"oooo"
	"o**o"
	"o**o"
	"oooo",

// BLOCK_I,
	"o*oo"
	"o*oo"
	"o*oo"
	"o*oo",

//	BLOCK_J,
	"oo*o"
	"oo*o"
	"o**o"
	"oooo",

//	BLOCK_L,
	"o*oo"
	"o*oo"
	"o**o"
	"oooo",

//	BLOCK_T,
	"oooo"
	"***o"
	"o*oo"
	"oooo",

//	BLOCK_Z,
	"oooo"
	"**oo"
	"o**o"
	"oooo",

//	BLOCK_S,
	"oooo"
	"oo**"
	"o**o"
	"oooo",
};

static unsigned int str2uint(const char *str)
{
	const int ORDER=Tetromino::ORDER;
	const int len=ORDER*ORDER;

	// make sure that string's the right format.
	assert((int)strlen(str)==len);
	for(int i=0; i<len; ++i)
		assert(str[i]=='o' || str[i]=='*');

	unsigned int result=0;
	for(int j=0; j<ORDER; ++j)
	for(int i=0; i<ORDER; ++i)
	{
		if(str[j*ORDER+i]=='*')
		{
			int digit=((ORDER-1-j)*ORDER)+i;
			result|=1<<digit; // note that Y direction is reversed.
		}
	}

	return result;
}

static bool formatBlockString(void)
{
	FILE* file=fopen("block.h", "wt");
	if(!file)
	{
		printf("file open failed!\n");
		return false;
	}

	for(int i=0; i<Tetromino::BLOCK_NB; ++i)
		fprintf(file, "\t0x%04x,\n", str2uint(BLOCK_STR[i]));

	fclose(file);
	return true;
}
