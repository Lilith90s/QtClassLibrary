#pragma once

#include <QtWidgets/QWidget>
#include <QLineEdit>
#include "ui_QtClassLibrary.h"
#include <HDateTimeLineEdit.h>
#include <LoadingWidget.h>
class QtClassLibrary : public QWidget
{
	Q_OBJECT

public:
	QtClassLibrary(QWidget *parent = Q_NULLPTR);
	void testButton();
private slots:
	void loadingButton_clicked();
private:
	Ui::QtClassLibraryClass ui;
	LoadingWidget* m_loading_dialog;
};
