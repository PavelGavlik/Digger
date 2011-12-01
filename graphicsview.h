#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphicsView(QGraphicsScene *parent = 0);
	void drawBackground(QPainter *painter, const QRectF &rect);

	QList<QPixmap> sprites;
private:
	void spritesInit();

	int level;

signals:

public slots:

};

#endif // GRAPHICSVIEW_H
