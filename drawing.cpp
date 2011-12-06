#include "drawing.h"
#include "main.h"

GraphicsScene *myScene;
GraphicsView *myView;


EmeraldItem::EmeraldItem()
{
	setPixmap(myScene->sprites[FIRSTEMERALD]);
}

void drawemerald(int16_t x, int16_t y)
{
	EmeraldItem *e = new EmeraldItem();
	myScene->addItem(e);
	e->setPos(x, y);
}


BagItem::BagItem(int16_t sprite)
{
	setPixmap(myScene->sprites[sprite]);
}

void drawbag(int16_t sprite, int16_t x, int16_t y)
{
	BagItem *b = new BagItem(sprite);
	myScene->addItem(b);
	b->setPos(x, y);
}


GraphicsScene::GraphicsScene()
{
	myScene = this;

	setSceneRect(0, 0, 640, 400);
	addRect(0, 0, 640, 28, QPen(), QBrush(Qt::black));
	this->spritesInit();
}

void GraphicsScene::spritesInit()
{
	QImage spriteImage = QImage(":/images/sprites.png");
	for (int i = 0; i < SPRITES; i++)
	{
		int id = i * 4;
		sprites << QPixmap::fromImage(spriteImage.copy(
					   spriteDimensions[id], spriteDimensions[id + 1],
					   spriteDimensions[id + 2], spriteDimensions[id + 3]));
	}
}


GraphicsView::GraphicsView(QGraphicsScene *parent) :
	QGraphicsView(parent)
{
	myView = this;

	setCacheMode(QGraphicsView::CacheBackground);
	setRenderHint(QPainter::Antialiasing);
	setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
}

void GraphicsView::drawBackground(QPainter *painter, const QRectF &rect)
{
	painter->fillRect(rect, QBrush(myScene->sprites[FIRSTBACKGROUND + levplan() - 1]));
}

void GraphicsView::resizeEvent(QResizeEvent *)
{
	//fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
}
