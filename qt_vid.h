#ifndef QT_VID_H
#define QT_VID_H
class Sprite : public QGraphicsPixmapItem
{
public:
	Sprite(int16_t spriteId);
	int16_t type;
private:
	int16_t getNewId(int16_t oldId);
};


class GraphicsScene : public QGraphicsScene
{
public:
	explicit GraphicsScene(QObject *parent = 0);
	void addSprite(int16_t spriteId, int16_t x, int16_t y);

	QList<QPixmap> sprites;
private:
	void spritesInit();
};


class GraphicsView : public QGraphicsView
{
public:
	explicit GraphicsView(QGraphicsScene *parent = 0);
	void drawBackground(QPainter *painter, const QRectF &rect);
protected:
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
};


extern int spriteDimensions[];
extern GraphicsScene *myScene;
extern GraphicsView *myView;
#endif // QT_VID_H
