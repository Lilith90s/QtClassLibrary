#include "QtClassLibrary.h"
#include <QDateTime>
#include <QDebug>
QtClassLibrary::QtClassLibrary(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	qDebug() << DateEditDialog::g_DateFormat;

}

void QtClassLibrary::testButton()
{
	QDateTime date =  QDateTime::fromString( ui.lineEdit->text(),DateEditDialog::g_DateFormat);
	qDebug() << date;
}
