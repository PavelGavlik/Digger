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

	//scene->addPixmap(view->sprites[LASTDIGGER-1]);
	scene->addPixmap(view->sprites[LASTBAG-1]);

	setCentralWidget(view);
	setMinimumSize(800, 400);

//	QSizePolicy s(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
//	s.setHeightForWidth(true);
//	setSizePolicy(s);
//	qDebug() << sizePolicy().hasHeightForWidth();

	show();
}

//int MainWindow::heightForWidth( int w ) const
//{
//	qDebug() << w;
//	return w;
//}
