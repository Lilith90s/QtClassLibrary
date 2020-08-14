#pragma once

#include <QDialog>
#include <QThread>
#include "loadingwidget_global.h"
#include "ui_Loading.h"


class LOADINGWIDGET_EXPORT Loading : public QDialog
{
	Q_OBJECT

public:
	Loading(QWidget *parent = Q_NULLPTR);
	void showLoadingWidget();
	void showLoadingWidget(QRect& rect);
	void closeLoadingWidget();
	void setMaskWidget(QWidget* widget);
	~Loading();
protected:
	void mouseMoveEvent(QMouseEvent *event) override;
	void mousePressEvent(QMouseEvent* event) override;
private:
	Ui::Loading ui;
	QMovie* movie;
	QTimer* m_timer_;
	QWidget* main_widget_ = nullptr;
	bool current_exec_ = true;
	bool mouse_pressed = false;
	// 鼠标单击时x位置
	int m_cacheX;

	// 鼠标单击时y位置
	int m_cacheY;
	QRect draw_rect_;
};
