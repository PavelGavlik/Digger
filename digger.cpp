#include "def.h"
#include "main.h"
#include "drawing.h"

int16_t emmask = 0;
int8_t emfield[MSIZE];


void makeemfield()
{
	int16_t x, y;
	emmask = 1 << 0;//curplayer;
	for (x = 0; x < MWIDTH; x++)
		for (y = 0; y < MHEIGHT; y++)
			if (getlevch(x, y, levplan()) == 'C')
				emfield[y * MWIDTH + x] |= emmask;
			else
				emfield[y * MWIDTH + x] &= ~emmask;
}

void drawemeralds()
{
	int16_t x, y;
	emmask = 1 << 0;//curplayer;
	for (x = 0; x < MWIDTH; x++)
		for (y = 0; y < MHEIGHT; y++)
			if (emfield[y * MWIDTH + x] & emmask)
				drawemerald(x * 40 + 24, y * 36 + 36);
}
