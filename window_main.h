#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include "graphicsview.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	/**
	 * @brief Constructor
	 */
	MainWindow(QWidget* parent=0, Qt::WindowFlags f=0);
	//int heightForWidth(int) const;

private:
        QMenuBar *menu;
        GraphicsView *view;
        QGraphicsScene *scene;
};

#endif // MAINWINDOW_H
