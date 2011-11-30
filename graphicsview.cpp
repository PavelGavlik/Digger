#include "graphicsview.h"
#include "def.h"

GraphicsView::GraphicsView(QGraphicsScene *parent) :
    QGraphicsView(parent)
{
	setRenderHint(QPainter::Antialiasing);
	setCacheMode(QGraphicsView::CacheBackground);
	setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

	QImage spriteImage = QImage(":/images/sprites.png");
	int spriteDimensions[] = {
		/* Red digger - loaded */
		32,		16,		32,	30, /* right */
		120,	16,		32,	30,
		208,	16,		32,	30,
		296,	16,		32,	30, /* left */
		384,	16,		32,	30,
		472,	16,		32,	30,

		560,	16,		32,	30, /* up */
		648,	16,		32,	30,
		736,	16,		32,	30,
		824,	16,		32,	30, /* down */
		912,	16,		32,	30,
		1000,	16,		32,	30,

		/* Red digger - unloaded */
		32,		72,		32,	30, /* right */
		120,	72,		32,	30,
		208,	72,		32,	30,
		296,	72,		32,	30, /* left */
		384,	72,		32,	30,
		472,	72,		32,	30,

		560,	72,		32,	30, /* up */
		648,	72,		32,	30,
		736,	72,		32,	30,
		824,	72,		32,	30, /* down */
		912,	72,		32,	30,
		1000,	72,		32,	30,

		/* Green digger - loaded */
		32,		128,		32,	30, /* right */
		120,	128,		32,	30,
		208,	128,		32,	30,
		296,	128,		32,	30, /* left */
		384,	128,		32,	30,
		472,	128,		32,	30,

		560,	128,		32,	30, /* up */
		648,	128,		32,	30,
		736,	128,		32,	30,
		824,	128,		32,	30, /* down */
		912,	128,		32,	30,
		1000,	128,		32,	30,

		/* Green digger - unloaded */
		32,		184,		32,	30, /* right */
		120,	184,		32,	30,
		208,	184,		32,	30,
		296,	184,		32,	30, /* left */
		384,	184,		32,	30,
		472,	184,		32,	30,

		560,	184,		32,	30, /* up */
		648,	184,		32,	30,
		736,	184,		32,	30,
		824,	184,		32,	30, /* down */
		912,	184,		32,	30,
		1000,	184,		32,	30,

		/* Monsters */
		32,		240,		32,	30, /* first */
		120,	240,		32,	30,
		208,	240,		32,	30,
		296,	240,		32,	30,
		384,	240,		32,	30, /* second - right */
		472,	240,		32,	30,

		560,	240,		32,	30,
		648,	240,		32,	30,
		736,	240,		32,	30, /* second - left */
		824,	240,		32,	30,
		912,	240,		32,	30,
		1000,	240,		32,	30,

		/* Level Backgrounds */
		8,		512,	40,	8,
		96,		512,	40,	8,
		184,	512,	40,	8,
		272,	512,	40,	8,
		360,	512,	40,	8,
		448,	512,	40,	8,
		536,	512,	40,	8,
		624,	512,	40,	8,
	};

	for (int i = 0; i < SPRITES; i++)
	{
		int id = i * 4;
		sprites << QPixmap::fromImage(spriteImage.copy(
					   spriteDimensions[id], spriteDimensions[id + 1],
					   spriteDimensions[id + 2], spriteDimensions[id + 3]));
	}

	level = qrand() % 8;
}

void GraphicsView::drawBackground(QPainter *painter, const QRectF &rect)
{
	painter->fillRect(rect, QBrush(sprites[FIRSTBACKGROUND + level]));
}
