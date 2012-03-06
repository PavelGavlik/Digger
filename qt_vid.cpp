#include "def.h"
#include <QGraphicsItem>
#include "drawing.h"


void graphicsoff(void)
{

}

void vgainit(void)
{

}

void vgaclear(void)
{

}

void vgainten(int16_t /*inten*/)
{

}

void vgapal(int16_t /*pal*/)
{

}

void vgaputi(int16_t x, int16_t y, uint8_t * /*p*/, int16_t w, int16_t h)
{
	qDebug() << "puti" << x << y << w << h;
	QList<QGraphicsItem *> items = myScene->items(x * 2, y * 2, w , h );
	for	(int i = 0; i < items.length(); i++)
	{
		QPointF xy = items[i]->pos();
		if (xy.x() == x * 2 && xy.y() == y * 2)
		{
			myScene->removeItem(items[i]);
		}
	}
}

void vgageti(int16_t x, int16_t y, uint8_t * /*p*/, int16_t /*w*/, int16_t /*h*/)
{
	qDebug() << "geti" << x << y;
}

int16_t vgagetpix(int16_t /*x*/, int16_t /*y*/)
{
	return 0;
}

void vgaputim(int16_t x, int16_t y, int16_t /*ch*/, int16_t /*w*/, int16_t /*h*/)
{
	qDebug() << "putim" << x << y;
}

void vgawrite(int16_t x, int16_t y, int16_t /*ch*/, int16_t /*c*/)
{
	qDebug() << "write" << x << y;
}

void vgatitle(void)
{

}
