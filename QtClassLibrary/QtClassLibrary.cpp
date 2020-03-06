#include "QtClassLibrary.h"
#include <QDateTime>
#include <QDebug>
#include <QCompleter>
#include <QAbstractItemView>
QtClassLibrary::QtClassLibrary(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	qDebug() << DateEditDialog::g_DateFormat;
	ui.comboBox->init();
	// ui.comboBox->setEditable(true);
	// QStringList strings;
	// strings << "hello" << "hi" << "word"; 
	// 
	// QCompleter* completer = new QCompleter(strings, this); 
	// completer->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
	// completer->popup()->setStyleSheet("    background-color: #294662;\
	//                                     color: #ffffff;\
	//                                     border: 1px solid #375C80;\
	//                                     border-radius: 5px;\
	//                                     padding: 0px 0px 0px 0px;\
	//                                     min-width: 17px;\
	//                                     font: 14px \"Arial\";");
	// ui.comboBox->setCompleter(completer);
}

void QtClassLibrary::testButton()
{
	QDateTime date =  QDateTime::fromString( ui.lineEdit->text(),DateEditDialog::g_DateFormat);
	qDebug() << date;
}
