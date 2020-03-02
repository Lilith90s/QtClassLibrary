#pragma once

#include <QtWidgets/QWidget>
#include <QLineEdit>
#include "ui_QtClassLibrary.h"
#include <HDateTimeLineEdit.h>
class QtClassLibrary : public QWidget
{
	Q_OBJECT

public:
	QtClassLibrary(QWidget *parent = Q_NULLPTR);
	void testButton();
private:
	Ui::QtClassLibraryClass ui;
	
};
