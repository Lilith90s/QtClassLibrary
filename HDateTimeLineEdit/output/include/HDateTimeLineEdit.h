#pragma once

#include "hdatetimelineedit_global.h"
#include <qlineedit.h>
#include <QWidget>
#include <QAction>
#include "DateEditDialog.h"
class HDATETIMELINEEDIT_EXPORT HDateTimeLineEdit
	:public QLineEdit
{
public:
	explicit HDateTimeLineEdit(QWidget* parent = nullptr);

private slots:

	// 弹出日期选择对话框
	void showDateSelectDialogSlot();

	// 接受日期改变事件
	void setTimeEditSlot(QDateTime& datetime);
private:
	// 选择日期动作
	QAction* m_pSelectDateAction;

	// 日期选择对话框
	DateEditDialog* m_pDateEditDialog;
};
