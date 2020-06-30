#pragma once

#include <QDialog>
#include "ui_TableWidgetDialog.h"

class TableWidgetDialog : public QDialog
{
	Q_OBJECT

public:
	TableWidgetDialog(QWidget *parent = Q_NULLPTR);
	~TableWidgetDialog();

	QVector<QStringList> getData();

private:
	Ui::TableWidgetDialog ui;
};
