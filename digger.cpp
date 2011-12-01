#include "def.h"
#include "main.h"
#include "drawing.h"

Sint4 emmask = 0;
Sint3 emfield[MSIZE];


void makeemfield()
{
	Sint4 x, y;
	emmask = 1 << 0;//curplayer;
	for (x = 0; x < MWIDTH; x++)
		for (y = 0; y < MHEIGHT; y++)
			if (getlevch(x, y, 1/*levplan()*/) == 'C')
				emfield[y * MWIDTH + x] |= emmask;
			else
				emfield[y * MWIDTH + x] &= ~emmask;
}

void drawemeralds()
{
	Sint4 x, y;
	emmask = 1 << 0;//curplayer;
	for (x = 0; x < MWIDTH; x++)
		for (y = 0; y < MHEIGHT; y++)
			if (emfield[y * MWIDTH + x] & emmask)
				drawemerald(x * 32 + 12, y * 30 + 21);
}
