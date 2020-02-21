#include "QtClassLibrary.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtClassLibrary w;
	w.show();
	return a.exec();
}
