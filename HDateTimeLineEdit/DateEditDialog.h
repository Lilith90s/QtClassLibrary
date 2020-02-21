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
	// 隐藏对话框
	void hideDialogSlot();

	// 日期点击事件，设置天数
	void dayBtnClickSlot();

	// 点击确定事件
	void okButtonClickedSlot();

	// 点击取消事件
	void cancelButtonClickedSlot();


protected:

	// 鼠标按下事件
	//void mousePressEvent(QMouseEvent* event) override;

	// 事件过滤器
	bool eventFilter(QObject* obj, QEvent *event) override;

	// 绘制阴影
	void paintEvent(QPaintEvent* event) override;

	// 焦点移出自动隐藏
	void focusOutEvent(QFocusEvent *event) override;

private:

	// 初始化表格
	void initDayDisplay();
	
	// 初始化下拉框
	void initCombox();

	// 设置月份
	void setMonth(int year, int month);

	// 设置日期
	void setDate(QDate date);

	// 展示按钮的提示
	void showTip(QPushButton* btn);

	// 获取是周几
	void whichDay(int year,int month,int day);

	// 天数的按钮
	QVector<QPushButton*> m_vDayButtons;

	// 初始化监听时间
	void initInstallEventFilter();

	// 获取当前时间
	QDateTime getSelectTime();

	// 设置未点击的样式
	void clearStyleSheet(QPushButton* btn);

	// 设置点击后的样式
	void setClickedStyleSheet(QPushButton* btn);

	Ui::DateEditDialog ui;

	int month[12] = {
	31/*1*/,28/*2*/,31/*3*/,30/*4*/,
	31/*5*/,30/*6*/,31/*7*/,31/*8*/,
	30/*9*/,31/*10*/,30/*11*/,31/*12*/
	};

	// 记录上一次点击的按钮
	QPushButton* m_lastClickBtn{nullptr};

	// 当前年
	int m_iYear = 0;

	// 当前月
	int m_iMonth = 0;

	// 当前日
	int m_iDay = 0;

	// 当前时
	int m_iHour = 0;

	// 当前分
	int m_iMin = 0;

	// 当前秒
	int m_iSec = 0;


	bool m_isFcousme = false;
};
