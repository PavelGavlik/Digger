#include <QWaitCondition>
#include <QMutex>
#include <QTime>
#include "def.h"

uint32_t prev = 0;
extern uint32_t ftime;
QTime t;

void inittimer(void)
{
	t.start();
}

int32_t getlrt(void)
{
	return (0);
}

uint32_t gethrt(void)
{
	int32_t diff;

//	doscreenupdate();

	// Speed controlling stuff
	if (prev == 0)
	{
		prev = t.elapsed();
	}
	else
	{
		diff = (ftime / 1000 - (t.elapsed() - prev));
		//qDebug() << diff;
		if (diff > 0)
		{
			QWaitCondition sleep;
			QMutex m;
			sleep.wait(&m, diff);
		}
		prev = t.elapsed();
	}
	return (0);
}

int32_t getkips(void)
{
	return (1);
}

void s0initint8(void)
{
}

void s0restoreint8(void)
{
}

void s1initint8(void)
{
}

void s1restoreint8(void)
{
}

void s0soundoff(void)
{
}

void s0setspkrt2(void)
{
}

void s0settimer0(uint16_t)
{
}

void s0settimer2(uint16_t)
{
}

void s0timer0(uint16_t)
{
}

void s0timer2(uint16_t)
{
}

void s0soundkillglob(void)
{
}

