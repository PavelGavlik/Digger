#ifndef MAIN_H
#define MAIN_H

#include <QMainWindow>
#include <QMenuBar>
#include "drawing.h"

int16_t getlevch(int16_t x, int16_t y, int16_t l);
void game();


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
