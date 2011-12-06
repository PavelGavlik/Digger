#include <QApplication>
#include <QTime>
#include "main.h"
#include "bags.h"
#include "def.h"
#include "digger.h"

extern int8_t leveldat[8][MHEIGHT][MWIDTH+1];

char pldispbuf[14];
int16_t curplayer = 0, nplayers = 1, penalty = 0, diggers = 1, startlev = 3;
bool unlimlives = false, gauntlet = false, timeout = false, synchvid = false;
int gtime = 0;

static struct game
{
	int16_t level;
	bool levdone;
} gamedat[2];

static bool levnotdrawn = false;//, alldead = false, started;

char levfname[132];
bool levfflag = false;
//static bool biosflag = false;
//static int32_t delaytime = 0;


int16_t levno(void);

int16_t getlevch(int16_t x, int16_t y, int16_t l)
{
//	if ((l==3 || l==4) && !levfflag && diggers==2 && y==9 && (x==6 || x==8))
//		return 'H';
	return leveldat[l-1][y][x];
}

void initlevel(void)
{
	gamedat[curplayer].levdone = FALSE;
	makefield();
	makeemfield();
	initbags();
	levnotdrawn = TRUE;
}

void drawscreen(void)
{
//	creatembspr();
	drawstatics();
	drawbags();
	drawemeralds();
//	initdigger();
//	initmonsters();
}

void game(void)
{
	gamedat[0].level = startlev;
	if (nplayers == 2)
		gamedat[1].level = startlev;

	initlevel();
	drawscreen();
}

int16_t levplan(void)
{
	int16_t l = levno();
	if (l > 8)
		l = (l & 3) + 5;		/* Level plan: 12345678, 678, (5678) 247 times, 5 forever */
	return l;
}

int16_t levof10(void)
{
	if (gamedat[curplayer].level > 10)
		return 10;
	return gamedat[curplayer].level;
}

int16_t levno(void)
{
	return gamedat[curplayer].level;
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
