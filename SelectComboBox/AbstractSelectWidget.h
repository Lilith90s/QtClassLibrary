#pragma once
#include <QtWidgets/QWidget>
#include "ui_AbstractSelectWidget.h"
#include "selectcombobox_global.h"

class AbstractSelectWidget : public QWidget
{
	Q_OBJECT

public:
	AbstractSelectWidget(QWidget *parent = Q_NULLPTR);
	~AbstractSelectWidget();
	// 设置标签名字
	virtual void setLabelText(QString text) = 0;
	// 添加到组
	virtual void addGroup();
protected slots:
	virtual void on_pushButton_clicked();
protected:
	void selectFile(QString title,QString path,QString filter);
	void selectDir(QString title, QString path);
	void setButton(QAbstractButton* widget);
private:
	Ui::AbstractSelectWidget ui;
};
