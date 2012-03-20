#ifndef MAIN_H
#define MAIN_H

#include <QApplication>
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

int16_t getlevch(int16_t bp6, int16_t bp8, int16_t bpa);
void incpenalty(void);
int16_t levplan(void);
int16_t levof10(void);
void setdead(bool df);
void cleartopline(void);
void finish(void);
int16_t randno(int16_t n);
void game(void);
int mainprog(void);


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
public slots:
	void titlescreenframeslot(void);
	void gamephaseslot(void);
};

#endif // MAIN_H
