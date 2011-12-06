#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include "def.h"

class EmeraldItem : public QGraphicsPixmapItem
{
public:
	EmeraldItem();
};
void drawemerald(int16_t x, int16_t y);


class BagItem : public QGraphicsPixmapItem
{
public:
	BagItem(int16_t sprite);
};
void drawbag(int16_t sprite, int16_t x, int16_t y);

class GraphicsScene : public QGraphicsScene
{
	Q_OBJECT
public:
	explicit GraphicsScene();

	QList<QPixmap> sprites;
private:
	void spritesInit();
};


class GraphicsView : public QGraphicsView
{
	Q_OBJECT
public:
	explicit GraphicsView(QGraphicsScene *parent = 0);
	void drawBackground(QPainter *painter, const QRectF &rect);
protected:
	void resizeEvent(QResizeEvent *);
};


extern int spriteDimensions[];
extern GraphicsScene *myScene;
extern GraphicsView *myView;

#endif // GRAPHICSVIEW_H
