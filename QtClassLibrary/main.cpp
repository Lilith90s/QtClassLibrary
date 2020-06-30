#include "QtClassLibrary.h"
#include <QtWidgets/QApplication>
#include <qfile.h>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QFile f(":/QtClassLibrary/qss/psblack.css");
	if (f.open(QIODevice::ReadOnly))
	{
		QString qss = f.readAll();
		QString paletteColor = qss.mid(20, 7);
		qApp->setPalette(QPalette(QColor(paletteColor)));
		qApp->setStyleSheet(qss);
	}
	QtClassLibrary w;
	w.show();
	return a.exec(); 
}
