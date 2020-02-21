#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtClassLibrary.h"

class QtClassLibrary : public QWidget
{
	Q_OBJECT

public:
	QtClassLibrary(QWidget *parent = Q_NULLPTR);

private:
	Ui::QtClassLibraryClass ui;
};
