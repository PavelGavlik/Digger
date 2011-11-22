#include "graphicsview.h"

GraphicsView::GraphicsView(QGraphicsScene *parent) :
    QGraphicsView(parent)
{
	setRenderHint(QPainter::Antialiasing);
	setCacheMode(QGraphicsView::CacheBackground);
	setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

	level = qrand() % 8;
}

void GraphicsView::drawBackground(QPainter *painter, const QRectF &rect)
{
	QImage sprites, bg;
	sprites = QImage(":/images/sprites.bmp");

	bg = sprites.copy(8 + level*88, 512, 40, 8);
	painter->fillRect(rect, QBrush(QPixmap::fromImage(bg)));
}
