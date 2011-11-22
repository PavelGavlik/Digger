#include "window_main.h"
#include <QApplication>
#include <QLabel>
#include <QTime>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
	MainWindow window;

	return app.exec();
}
