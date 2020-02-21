#pragma once

#include <QWidget>
#include <QObject>
#include <QStandardItemModel>
#include <QVector>
#include "ui_DateEditDialog.h"
#include <QDate>
class DateEditDialog : public QWidget
{
	Q_OBJECT

public:
	DateEditDialog(QWidget *parent = Q_NULLPTR);
	~DateEditDialog();
	void setTime(QDateTime &datetime);

	static QString g_DateFormat;

signals:
	void dateChanged(QDateTime &datetime);

private slots:
	// ���ضԻ���
	void hideDialogSlot();

	// ���ڵ���¼�����������
	void dayBtnClickSlot();

	// ���ȷ���¼�
	void okButtonClickedSlot();

	// ���ȡ���¼�
	void cancelButtonClickedSlot();


protected:

	// ��갴���¼�
	//void mousePressEvent(QMouseEvent* event) override;

	// �¼�������
	bool eventFilter(QObject* obj, QEvent *event) override;

	// ������Ӱ
	void paintEvent(QPaintEvent* event) override;

	// �����Ƴ��Զ�����
	void focusOutEvent(QFocusEvent *event) override;

private:

	// ��ʼ�����
	void initDayDisplay();
	
	// ��ʼ��������
	void initCombox();

	// �����·�
	void setMonth(int year, int month);

	// ��������
	void setDate(QDate date);

	// չʾ��ť����ʾ
	void showTip(QPushButton* btn);

	// ��ȡ���ܼ�
	void whichDay(int year,int month,int day);

	// �����İ�ť
	QVector<QPushButton*> m_vDayButtons;

	// ��ʼ������ʱ��
	void initInstallEventFilter();

	// ��ȡ��ǰʱ��
	QDateTime getSelectTime();

	// ����δ�������ʽ
	void clearStyleSheet(QPushButton* btn);

	// ���õ�������ʽ
	void setClickedStyleSheet(QPushButton* btn);

	Ui::DateEditDialog ui;

	int month[12] = {
	31/*1*/,28/*2*/,31/*3*/,30/*4*/,
	31/*5*/,30/*6*/,31/*7*/,31/*8*/,
	30/*9*/,31/*10*/,30/*11*/,31/*12*/
	};

	// ��¼��һ�ε���İ�ť
	QPushButton* m_lastClickBtn{nullptr};

	// ��ǰ��
	int m_iYear = 0;

	// ��ǰ��
	int m_iMonth = 0;

	// ��ǰ��
	int m_iDay = 0;

	// ��ǰʱ
	int m_iHour = 0;

	// ��ǰ��
	int m_iMin = 0;

	// ��ǰ��
	int m_iSec = 0;


	bool m_isFcousme = false;
};
