#include "AbstractSelectWidget.h"
#include <QtWidgets/QPushButton>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QHBoxLayout>
AbstractSelectWidget::AbstractSelectWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	
}

AbstractSelectWidget::~AbstractSelectWidget()
{
}

void AbstractSelectWidget::addGroup()
{

}

void AbstractSelectWidget::on_pushButton_clicked()
{

}

void AbstractSelectWidget::selectFile(QString title, QString path, QString filter)
{
	QString file_name = QFileDialog::getOpenFileName(this, title, path, filter);
	ui.lineEdit->setText(file_name);
}

void AbstractSelectWidget::selectDir(QString title, QString path)
{
	QString dir_name = QFileDialog::getExistingDirectory(this, title, path);
	ui.lineEdit->setText(dir_name);
}

void AbstractSelectWidget::setButton(QAbstractButton* widget)
{
	QHBoxLayout* h_layout = new QHBoxLayout;
	h_layout->addWidget(widget);
	h_layout->setContentsMargins(0, 0, 0, 0);
	widget->setChecked(true);
	ui.widget->setLayout(h_layout);
	//ui.widget->layout()->addWidget(widget);
}
