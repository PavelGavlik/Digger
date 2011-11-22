#include <QApplication>
#include <QBoxLayout>
#include "window_main.h"
#include "def.h"

extern Uint3 *vgatable[];

MainWindow::MainWindow(QWidget* parent, Qt::WindowFlags f) :
	QMainWindow(parent, f)
{
	setWindowTitle(QObject::tr("D I G G E R"));

	menu = menuBar();
	QMenu* menu_game = new QMenu("G&ame", menu);
	menu_game->addAction("End game", qApp, SLOT(quit()), QKeySequence::Quit);
	menu->addMenu(menu_game);

	scene = new QGraphicsScene;
	view = new GraphicsView(scene);

	scene->addEllipse(5, 5, 50, 100, QPen(Qt::gray), QBrush(Qt::green, Qt::DiagCrossPattern));
	scene->addRect(-20, 20, 100, 10, QPen(Qt::transparent), QBrush(QColor(255, 0, 0, 150)));
	scene->addLine(0, 0, 100, 100);

	//scene->addPixmap(QPixmap(QString(":/images/sprites.bmp")).scaledToHeight(230));

	setCentralWidget(view);
	setMinimumSize(800, 400);
	show();
}
