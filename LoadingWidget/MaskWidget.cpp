#pragma execution_character_set("utf-8")

#include "maskwidget.h"
#include "qmutex.h"
#include "qapplication.h"
#include "qdesktopwidget.h"
#include "qdebug.h"
#include <QHBoxLayout>

QScopedPointer<MaskWidget> MaskWidget::self;
MaskWidget *MaskWidget::Instance()
{
	if (self.isNull()) {
		static QMutex mutex;
		QMutexLocker locker(&mutex);
		if (self.isNull()) {
			self.reset(new MaskWidget);
		}
	}

	return self.data();
}

MaskWidget::MaskWidget(QWidget *parent) : QWidget(parent)
{
	mainWidget = 0;
	setOpacity(0.0);
	setBgColor(QColor(0, 0, 0));
	setWindowFlags(Qt::SubWindow);
	//�����������������ֲ��СΪĬ�������С
	this->setGeometry(qApp->desktop()->geometry());
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);

	//��ȫ���¼�,���˵���������д���
	qApp->installEventFilter(this);
}

QWidget* MaskWidget::getMainWidget()
{
	return mainWidget;
}

void MaskWidget::setMainWidget(QWidget *mainWidget)
{
	if (this->mainWidget != mainWidget) {
		this->mainWidget = mainWidget;
	}
}

void MaskWidget::setDialogNames(const QStringList &dialogNames)
{
	if (this->dialogNames != dialogNames) {
		this->dialogNames = dialogNames;
	}
}

void MaskWidget::setDialogWidget(QWidget *widget)
{
	dialogWidget = widget;
}

void MaskWidget::setOpacity(double opacity)
{
	this->setWindowOpacity(opacity);
}

void MaskWidget::setBgColor(const QColor &bgColor)
{
	QPalette palette = this->palette();
	palette.setBrush(QPalette::Background, bgColor);
	this->setPalette(palette);
}

void MaskWidget::showEvent(QShowEvent *)
{
	if (mainWidget != 0) {
		this->setGeometry(mainWidget->geometry());
	} 
}

bool MaskWidget::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::Show) {
		//if (dialogNames.contains(obj->objectName())) {
		//	this->show();
		//	this->activateWindow();
		//	QWidget *w = (QWidget *)obj;
		//	w->activateWindow();
		//}
	}
	else if (event->type() == QEvent::Hide) {
		if (dialogNames.contains(obj->objectName())) {
			this->hide();
		}
	}
	else if (event->type() == QEvent::WindowActivate) {
		//�������弤��ʱ,ͬʱ�������ֲ�
		if (mainWidget != 0) {
			//qDebug() << obj->objectName();
			if (obj->objectName() == mainWidget->objectName()) {
				if (this->isVisible()) {
					this->activateWindow();
				}
			}
		}
	}
	return QObject::eventFilter(obj, event);
}
