#ifndef MAIN_H
#define MAIN_H

#include <QMainWindow>
#include <QMenuBar>
#include "drawing.h"

extern int16_t nplayers, diggers, curplayer, startlev;
extern bool levfflag;
extern char levfname[];
extern char pldispbuf[];
extern int32_t randv;
extern int gtime;
extern bool gauntlet, timeout, synchvid, unlimlives;

int16_t getlevch(int16_t x, int16_t y, int16_t l);
void game(void);
int16_t levplan(void);
int16_t levof10(void);


class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	/**
	 * @brief Constructor
	 */
	MainWindow(QWidget* parent=0, Qt::WindowFlags f=0);

	GraphicsView *view;
	GraphicsScene *scene;
private:
	QMenuBar *menu;
};

#endif // MAIN_H
