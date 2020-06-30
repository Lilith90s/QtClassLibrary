#include "LoadingWidget.h"
#include <QMovie>
#include "MaskWidget.h"
#include <QThread>
#include <QKeyEvent>
#include <QDebug>

LoadingWidget::LoadingWidget(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	this->setWindowFlags(Qt::FramelessWindowHint| Qt::SubWindow);
	setWindowModality(Qt::ApplicationModal);
	setAttribute(Qt::WA_TranslucentBackground);//背景透明
	movie = new QMovie(":/loading.gif");
	movie->start();
	ui.label->setMovie(movie);
	
	MaskWidget::Instance()->setDialogNames(QStringList() << "loadingWidget");
	MaskWidget::Instance()->setDialogWidget(this);
	setObjectName("loadingWidget");
	connect(qApp, &QApplication::applicationStateChanged, [this](Qt::ApplicationState state) {
		if (state == Qt::ApplicationActive)
		{
			 MaskWidget::Instance()->getMainWidget()->activateWindow();
		}
	});
	//this->setModal(true);
}

LoadingWidget::~LoadingWidget()
{

}

void LoadingWidget::showEvent(QShowEvent *event) 
{
	QWidget* main_widget = MaskWidget::Instance()->getMainWidget();
	if (main_widget != nullptr)
	{
		//this->setGeometry(main_widget->x() + main_widget->width() / 2, (main_widget->y() + 20) + main_widget->height() / 2, 36, 36);
		//this->setGeometry(main_widget->x()+8, main_widget->y()+31,
		//	 main_widget->width(),main_widget->height());
		this->setGeometry(main_widget->geometry());
		// main_widget->show();
	}
	QDialog::showEvent(event);
}



void LoadingWidget::closeEvent(QCloseEvent* event)
{
	if (!m_closeable)
	{
		event->ignore();
	}
	else
	{
		QDialog::closeEvent(event);
	}
}

void LoadingWidget::keyPressEvent(QKeyEvent* event)
{
	if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_F1))
	{
		//m_closeable = true;
		exit(0);
	}	
}

