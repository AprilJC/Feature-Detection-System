#include "Detect.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Detect w;
	w.show();
	return a.exec();
}
