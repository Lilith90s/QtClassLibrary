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

	// ��������ѡ��Ի���
	void showDateSelectDialogSlot();

	// �������ڸı��¼�
	void setTimeEditSlot(QDateTime& datetime);
private:
	// ѡ�����ڶ���
	QAction* m_pSelectDateAction;

	// ����ѡ��Ի���
	DateEditDialog* m_pDateEditDialog;
};
