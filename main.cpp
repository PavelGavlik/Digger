#include <QApplication>
#include <QTime>
#include "main.h"
#include "def.h"
#include "digger.h"

extern Sint3 leveldat[8][MHEIGHT][MWIDTH+1];

bool levnotdrawn=FALSE,alldead=FALSE,unlimlives=FALSE,started;


Sint4 getlevch(Sint4 x, Sint4 y, Sint4 l)
{
//	if ((l==3 || l==4) && !levfflag && diggers==2 && y==9 && (x==6 || x==8))
//		return 'H';
	return leveldat[l-1][y][x];
}

void initlevel()
{
//	gamedat[curplayer].levdone=FALSE;
//	makefield();
	makeemfield();
//	initbags();
	levnotdrawn=TRUE;
}

void drawscreen()
{
//  creatembspr();
//  drawstatics();
//  drawbags();
	drawemeralds();
//  initdigger();
//  initmonsters();
}

void game()
{
	initlevel();
	drawscreen();
}


MainWindow::MainWindow(QWidget* parent, Qt::WindowFlags f) :
	QMainWindow(parent, f)
{
	menu = menuBar();
	QMenu* menu_game = new QMenu("G&ame", menu);
	menu_game->addAction("End game", qApp, SLOT(quit()), QKeySequence::Quit);
	menu->addMenu(menu_game);

	scene = new GraphicsScene;
	view = new GraphicsView(scene);

	setWindowTitle(QObject::tr("D I G G E R"));
	setCentralWidget(view);
	setMinimumSize(640, 400);

	game();
	show();
}


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
	MainWindow window;

	return app.exec();
}
