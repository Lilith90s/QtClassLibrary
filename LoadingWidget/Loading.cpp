#include "Loading.h"
#include <QMovie>
#include <QWidget>
#include <qdebug.h>
#include <QTimer>
#include <QEventLoop>
#include <QMouseEvent>

Loading::Loading(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	this->setModal(true);
	this->setWindowFlags(Qt::FramelessWindowHint);
	//setWindowModality(Qt::ApplicationModal);
	setAttribute(Qt::WA_TranslucentBackground);//背景透明
	movie = new QMovie(":/loading.gif");
	// movie->start();
	m_timer_ = new QTimer;
	ui.label->setMovie(movie);
	
	
}

void Loading::showLoadingWidget()
{
	if ( main_widget_ != nullptr)
	{
		this->setGeometry(main_widget_->geometry());
		qDebug() << main_widget_->geometry();
		qDebug() << main_widget_->contentsMargins();
	} 
	movie->start();
	this->show();
}

void Loading::showLoadingWidget(QRect& rect)
{
	this->draw_rect_ = rect;
	this->setGeometry(rect);
	movie->start();
	this->show();
}

void Loading::closeLoadingWidget()
{
	movie->stop();
	close();
}

void Loading::setMaskWidget(QWidget* widget)
{
	this->main_widget_ = widget;
}

Loading::~Loading()
{

}

void Loading::mouseMoveEvent(QMouseEvent* event)
{
	if (main_widget_ != nullptr)
	{
		QPointF screen_pos = event->globalPos();
		QPoint mouse_pos = event->pos();
		QPoint pos(screen_pos.x() - m_cacheX,screen_pos.y()- m_cacheY-30);
		qDebug() << screen_pos << "------" << mouse_pos << "------" << pos;
		main_widget_->move(pos);
		this->setGeometry(main_widget_->geometry());
	}
	QDialog::mouseMoveEvent(event);
}

void Loading::mousePressEvent(QMouseEvent* event)
{
	// 记录点击时起始位置
	m_cacheX = event->pos().x();
	m_cacheY = event->pos().y();
	QDialog::mousePressEvent(event);
}
