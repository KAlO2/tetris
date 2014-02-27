#ifndef TETRIS_UTILS_
#define TETRIS_UTILS_

// RGBA data stored in little endian
#define COLOR_RGBA(R,G,B,A) \
	(unsigned int)(((R)&0xff)|(((G)&0xff)<<8)|(((B)&0xff)<<16)|(((A)&0xff)<<24))
#define COLOR_RGB(R,G,B) COLOR_RGBA(R,G,B,255u)

#define ARRAY_SIZE(array) (sizeof(array)/sizeof(array[0]))


#endif /* TETRIS_UTILS_ */
