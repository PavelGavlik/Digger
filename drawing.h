#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include "def.h"


void outtext(char *p, int16_t x, int16_t y, int16_t c);

void creatembspr(void);
void initmbspr(void);
void drawmon(int16_t n, bool nobf, int16_t dir, int16_t x, int16_t y);
void drawdigger(int n, int16_t t, int16_t x, int16_t y, bool f);
void drawgold(int16_t n, int16_t t, int16_t x, int16_t y);
void drawemerald(int16_t x, int16_t y);
void eraseemerald(int16_t x, int16_t y);
void drawbonus(int16_t x, int16_t y);
void drawlives(void);
void savefield(void);
void makefield(void);
void drawstatics(void);
void drawfire(int n, int16_t x, int16_t y, int16_t t);
void eatfield(int16_t x, int16_t y, int16_t dir);
void drawrightblob(int16_t x, int16_t y);
void drawleftblob(int16_t x, int16_t y);
void drawtopblob(int16_t x, int16_t y);
void drawbottomblob(int16_t x, int16_t y);
void drawmondie(int16_t n, bool nobf, int16_t dir, int16_t x, int16_t y);
void drawfurryblob(int16_t x, int16_t y);
void drawsquareblob(int16_t x, int16_t y);

extern int16_t field[];
extern int16_t fireheight;


void movedrawspr(int16_t n, int16_t x, int16_t y);


class Sprite : public QGraphicsPixmapItem
{
public:
	Sprite(int16_t sprite);
	int16_t type;
private:
	int16_t getNewId(int16_t oldId);
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
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
};


extern int spriteDimensions[];
extern GraphicsScene *myScene;
extern GraphicsView *myView;

#endif // GRAPHICSVIEW_H
