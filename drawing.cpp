#include "drawing.h"

GraphicsScene *myScene;
GraphicsView *myView;


EmeraldItem::EmeraldItem()
{
	setPixmap(myScene->sprites[FIRSTEMERALD]);
}

void drawemerald(Sint4 x, Sint4 y)
{
//	initmiscspr(x,y,4,10);
//	drawmiscspr(x,y,108,4,10);
//	getis();
	EmeraldItem *e = new EmeraldItem();
	myScene->addItem(e);
	e->setPos(x, y);
}


GraphicsScene::GraphicsScene()
{
	myScene = this;

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

	level = 1;//qrand() % 8;
}

void GraphicsView::drawBackground(QPainter *painter, const QRectF &rect)
{
	painter->fillRect(rect, QBrush(myScene->sprites[FIRSTBACKGROUND + level - 1]));
}

void GraphicsView::resizeEvent(QResizeEvent *)
{
	//fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
}
