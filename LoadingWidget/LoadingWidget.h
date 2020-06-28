#pragma once
#include <QtWidgets/QDialog>
#include "ui_LoadingDialog.h"
#include "loadingwidget_global.h"
class MovieThread;
class LOADINGWIDGET_EXPORT LoadingWidget : public QDialog
{
	Q_OBJECT

public:
	LoadingWidget(QWidget *parent = Q_NULLPTR);
	~LoadingWidget();
	
protected:
	void showEvent(QShowEvent *event);
	void keyPressEvent(QKeyEvent* event) override;

private:
	Ui::LoadingDialog ui;
	QMovie *movie;
	MovieThread* movie_thread;
};
