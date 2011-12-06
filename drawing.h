#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include "def.h"


void movedrawspr(int16_t sprite, int16_t x, int16_t y);
void drawemerald(int16_t x, int16_t y);
void savefield(void);
void makefield(void);
void drawstatics(void);
void drawrightblob(int16_t x, int16_t y);
void drawleftblob(int16_t x, int16_t y);
void drawtopblob(int16_t x, int16_t y);
void drawbottomblob(int16_t x, int16_t y);


class Sprite : public QGraphicsPixmapItem
{
public:
	Sprite(int16_t sprite);
};


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
