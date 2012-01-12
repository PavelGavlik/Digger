#include "def.h"

QMap<int16_t, bool> states;
int16_t key_buffer;

void initkeyb(void)
{
	key_buffer = -1;
}

bool GetAsyncKeyState(int16_t key)
{
	if (states.find(key) == states.end())
		return false;
	return states[key];
}

void PressKey(int16_t key)
{
	states[key] = true;
	key_buffer = key;
}

void ReleaseKey(int16_t key)
{
	states[key] = false;
}

void restorekeyb(void)
{
}

int16_t getkey(void)
{
	qDebug() << key_buffer;
	int16_t key = key_buffer;
	key_buffer = -1;
	return key;
}

bool kbhit(void)
{
	return key_buffer != -1;
}
