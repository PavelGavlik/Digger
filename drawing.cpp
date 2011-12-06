#include "drawing.h"
#include "main.h"

int16_t field1[MSIZE], field2[MSIZE], field[MSIZE];

GraphicsScene *myScene;
GraphicsView *myView;

void drawfield(void);


void makefield(void)
{
	int16_t c, x, y;
	for (x = 0; x < MWIDTH; x++)
		for (y = 0; y < MHEIGHT; y++)
		{
			field[y * MWIDTH + x] = -1;
			c = getlevch(x, y, levplan());
			if (c == 'S' || c == 'V')
				field[y * MWIDTH + x] &= 0xd03f;
			if (c == 'S' || c == 'H')
				field[y * MWIDTH + x] &= 0xdfe0;
			if (curplayer == 0)
				field1[y * MWIDTH + x] = field[y * MWIDTH + x];
			else
				field2[y * MWIDTH + x] = field[y * MWIDTH + x];
		}
}

void drawstatics(void)
{
	int16_t x, y;
	for (x = 0; x < MWIDTH; x++)
		for (y = 0; y < MHEIGHT; y++)
			if (curplayer == 0)
				field[y * MWIDTH + x] = field1[y * MWIDTH + x];
			else
				field[y * MWIDTH + x] = field2[y * MWIDTH + x];

	drawfield();
}

void savefield(void)
{
	int16_t x, y;
	for (x = 0; x < MWIDTH; x++)
		for (y = 0; y < MHEIGHT; y++)
			if (curplayer == 0)
				field1[y * MWIDTH + x] = field[y * MWIDTH + x];
			else
				field2[y * MWIDTH + x] = field[y * MWIDTH + x];
}

void drawfield(void)
{
	int16_t x, y, xp, yp;
	for (x = 0; x < MWIDTH; x++)
		for (y = 0; y < MHEIGHT; y++)
			if ((field[y * MWIDTH + x] & 0x2000) == 0)
			{
				xp = x * 20 + 12;
				yp = y * 18 + 18;
				if ((field[y * MWIDTH + x] & 0xfc0) != 0xfc0)
				{
					field[y * MWIDTH + x] &= 0xd03f;
					drawbottomblob(xp, yp - 15);
					drawbottomblob(xp, yp - 12);
					drawbottomblob(xp, yp - 9);
					drawbottomblob(xp, yp - 6);
					drawbottomblob(xp, yp - 3);
					drawtopblob(xp, yp + 3);
				}
				if ((field[y * MWIDTH + x] & 0x1f) != 0x1f)
				{
					field[y * MWIDTH + x] &= 0xdfe0;
					drawrightblob(xp - 16, yp);
					drawrightblob(xp - 12, yp);
					drawrightblob(xp - 8, yp);
					drawrightblob(xp - 4, yp);
					drawleftblob(xp + 4, yp);
				}
				if (x < 14)
					if ((field[y * MWIDTH + x + 1] & 0xfdf) != 0xfdf)
						drawrightblob(xp, yp);
				if (y < 9)
					if ((field[(y + 1) * MWIDTH + x] & 0xfdf) != 0xfdf)
						drawbottomblob(xp, yp);
			}
}

void drawemerald(int16_t x, int16_t y)
{
	movedrawspr(FIRSTEMERALD, x, y);
}

void drawrightblob(int16_t x, int16_t y)
{
	movedrawspr(FIRSTSTATIC, x + 16, y - 1);//, 102, 2, 18);
}

void drawleftblob(int16_t x, int16_t y)
{
	movedrawspr(FIRSTSTATIC+1, x - 8, y - 1);//, 104, 2, 18);
}

void drawtopblob(int16_t x, int16_t y)
{
	movedrawspr(FIRSTSTATIC+2, x - 2, y - 6);//, 103, 6, 6);
}

void drawbottomblob(int16_t x, int16_t y)
{
	movedrawspr(FIRSTSTATIC+3, x - 2, y + 15);//, 105, 6, 6);
}

Sprite::Sprite(int16_t sprite)
{
	setPixmap(myScene->sprites[sprite]);
}


GraphicsScene::GraphicsScene()
{
	myScene = this;

	setSceneRect(0, 0, 640, 400);
	addRect(0, 0, 640, 28, QPen(), QBrush(Qt::black));
	this->spritesInit();
}

void movedrawspr(int16_t sprite, int16_t x, int16_t y)
{
	Sprite *s = new Sprite(sprite);
	myScene->addItem(s);
	s->setPos(x * 2, y * 2);
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
