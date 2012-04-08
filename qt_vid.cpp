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
	//qDebug() << "puti" << x << y << w << h;
	QList<QGraphicsItem *> items = myScene->items(x * 2, y * 2, 32, 30, Qt::ContainsItemBoundingRect);
	for	(int i = 0; i < items.length(); i++)
	{
		//qDebug() << "remove" << ((Sprite*)items[i])->type;
		myScene->removeItem(items[i]);
	}
}

void vgageti(int16_t x, int16_t y, uint8_t * /*p*/, int16_t w, int16_t h)
{
	//qDebug() << "geti" << x << y << w << h;
}

int16_t vgagetpix(int16_t x, int16_t y)
{
	qDebug() << "getpix" << x << y;
	return 0;
}

void vgaputim(int16_t x, int16_t y, int16_t ch, int16_t w, int16_t h)
{
	//qDebug() << "putim" << x << y << w << h << "ch" << ch;
	myScene->addSprite(ch, x, y);
}

// used usually for text
void vgawrite(int16_t x, int16_t y, int16_t ch, int16_t c)
{
	int16_t textSpriteOffset = 55,
			numberSpriteOffset = 98;

	if ((ch - 32) >= 0x5f || ch < 32)
		return;

	if (ch >= 'A' && ch <= 'Z')
		myScene->addSprite(textSpriteOffset + ch, x, y);
	if (ch >= '0' && ch <= '9')
		myScene->addSprite(numberSpriteOffset + ch, x, y);
}

void vgatitle(void)
{

}
