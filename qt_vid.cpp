#include "def.h"
#include <QGraphicsItem>
#include <QKeyEvent>
#include "drawing.h"
#include "qt_vid.h"

void PressKey(int16_t key);
void ReleaseKey(int16_t key);
int16_t levplan(void);

GraphicsScene *myScene;
GraphicsView *myView;


void graphicsoff(void)
{

}

void vgainit(void)
{

}

void vgaclear(void)
{
	myScene->clear();
}

void vgainten(int16_t /*inten*/)
{

}

void vgapal(int16_t /*pal*/)
{

}

void vgaputi(int16_t x, int16_t y, uint8_t *p, int16_t w, int16_t h)
{
	Q_UNUSED(p);
	Q_UNUSED(w);
	Q_UNUSED(h);
	//qDebug() << "puti" << x << y << w << h;

	QList<QGraphicsItem *> items = myScene->items(x * 2, y * 2, 32, 30, Qt::ContainsItemBoundingRect);
	for	(int i = 0; i < items.length(); i++)
	{
		//qDebug() << "remove" << ((Sprite*)items[i])->type;
		myScene->removeItem(items[i]);
	}
}

void vgageti(int16_t x, int16_t y, uint8_t *p, int16_t w, int16_t h)
{
	Q_UNUSED(x);
	Q_UNUSED(y);
	Q_UNUSED(p);
	Q_UNUSED(w);
	Q_UNUSED(h);
	//qDebug() << "geti" << x << y << w << h;
}

int16_t vgagetpix(int16_t x, int16_t y)
{
	Q_UNUSED(x);
	Q_UNUSED(y);
	//qDebug() << "getpix" << x << y;
	return 0;
}

void vgaputim(int16_t x, int16_t y, int16_t ch, int16_t w, int16_t h)
{
	Q_UNUSED(w);
	Q_UNUSED(h);
	//qDebug() << "putim" << x << y << w << h << "ch" << ch;
	myScene->addSprite(ch, x, y);
}

// used usually for text
void vgawrite(int16_t x, int16_t y, int16_t ch, int16_t c)
{
	Q_UNUSED(c);
	int16_t textSpriteOffset = 55,
			numberSpriteOffset = 98;

	if ((ch - 32) >= 0x5f || ch < 32)
		return;

	if (ch >= 'A' && ch <= 'Z')
		myScene->addSprite(textSpriteOffset + ch, x, y);
	else if (ch >= '0' && ch <= '9')
		myScene->addSprite(numberSpriteOffset + ch, x, y);
}

void vgatitle(void)
{

}


Sprite::Sprite(int16_t spriteId)
{
	setPixmap(myScene->sprites[spriteId]);

	// prevent digger and monster flickering by setting higher z-index
	if (spriteId <= 93)
		setZValue(1);

	this->type = spriteId;
}


GraphicsScene::GraphicsScene(QObject *parent)
	: QGraphicsScene(parent)
{
	myScene = this;

	setSceneRect(0, 0, 640, 400);
	addRect(0, 0, 640, 28, QPen(), QBrush(Qt::black));
	this->spritesInit();
}


void GraphicsScene::spritesInit()
{
	QImage spriteImage = QImage(":/images/sprites.png");
	for (int i = 0; i < 160; i++)
	{
		int id = i * 4;
		sprites << QPixmap::fromImage(spriteImage.copy(
					   spriteDimensions[id], spriteDimensions[id + 1],
					   spriteDimensions[id + 2], spriteDimensions[id + 3]));
	}
}

void GraphicsScene::addSprite(int16_t spriteId, int16_t x, int16_t y)
{
	if (spriteId <= 0 || spriteId >= myScene->sprites.length())
	{
		qDebug() << spriteId << "not found";
		return;
	}

	Sprite *s = new Sprite(spriteId);
	myScene->addItem(s);
	s->setPos(x * 2, y * 2);
}


GraphicsView::GraphicsView(QGraphicsScene *parent)
	: QGraphicsView(parent)
{
	myView = this;

	setCacheMode(QGraphicsView::CacheBackground);
	setRenderHint(QPainter::Antialiasing);
}

void GraphicsView::drawBackground(QPainter *painter, const QRectF &rect)
{
	int16_t lvl = levplan();
	if (lvl <= 0)
		painter->fillRect(rect, Qt::black);
	else
		painter->fillRect(rect, QBrush(myScene->sprites[96 + lvl - 1]));
}

void GraphicsView::keyPressEvent(QKeyEvent *event)
{
	PressKey(event->key());
}

void GraphicsView::keyReleaseEvent(QKeyEvent *event)
{
	ReleaseKey(event->key());
}

