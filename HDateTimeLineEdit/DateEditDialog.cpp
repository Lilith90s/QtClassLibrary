#include "DateEditDialog.h"
#include <QPushButton>
#include <QFile>
#include <QDebug>
#include <QComboBox>
#include <QString>
#include <QMouseEvent>
#include <QPainter>
static QString g_DateFormat = "yyyy/MM/dd HH:mm:ss";
DateEditDialog::DateEditDialog(QWidget *parent)
	: QWidget(nullptr)
{
	ui.setupUi(this);
	QFile qss("Resources/DialogStyleSheet.css");
	if (qss.open(QIODevice::ReadOnly))
	{
		qDebug() << qss.readAll();
		// this->setStyleSheet(qss.readAll());
		qss.close();
	}
	this->setAttribute(Qt::WA_ShowModal, true);
	this->setWindowOpacity(1);
	this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint | Qt::SubWindow);
	// this->setWindowModality(Qt::ApplicationModal);
	setAttribute(Qt::WA_TranslucentBackground, true);
	this->hide();

	connect(ui.closeBtn, &QPushButton::clicked, this, &DateEditDialog::hideDialogSlot);

	connect(ui.nextMonthBtn, &QPushButton::clicked, this, [&] {
		m_iMonth++;
		m_iYear += m_iMonth /13;
		m_iMonth = m_iMonth > 12 ? 1 : m_iMonth;
		setMonth(m_iYear, m_iMonth);
		qDebug() << m_iYear << m_iMonth;
		});
	connect(ui.nextYearBtn, &QPushButton::clicked, this, [&] {
		m_iYear++;
		setMonth(m_iYear, m_iMonth);
		});
	connect(ui.lastMonthBtn, &QPushButton::clicked, this, [&] {
		m_iMonth--;
		m_iMonth = m_iMonth < 1 ? m_iYear--, m_iMonth + 12 : m_iMonth;
		setMonth(m_iYear, m_iMonth);
		qDebug() << m_iYear << m_iMonth;
		});
	connect(ui.lastYearBtn, &QPushButton::clicked, this, [&] {
		m_iYear--;
		setMonth(m_iYear, m_iMonth);
		});
	connect(ui.todayBtn, &QPushButton::clicked, this, [&] {
		setTime(QDateTime::currentDateTime());
		});

	connect(ui.okBtn, &QPushButton::clicked, this, &DateEditDialog::okButtonClickedSlot);
	connect(ui.cancelBtn, &QPushButton::clicked, this, &DateEditDialog::cancelButtonClickedSlot);
	// connect(ui.okBtn)

	/*生成代码*/
	//for (int i = 1; i < 50; i++)
	//{
	//	qDebug() << "m_vDayButtons.append( " + QString("ui.Btn_") + QString::number(i) +")";
	//}
	//
	/*生成代码*/

	initCombox();
	initDayDisplay();
	initInstallEventFilter();
	setTime(QDateTime::currentDateTime());
}

DateEditDialog::~DateEditDialog()
{

}

void DateEditDialog::setTime(QDateTime &datetime)
{
	setMonth(datetime.date().year(), datetime.date().month());
	for (size_t i = 0,length = m_vDayButtons.size(); i < length; i++)
	{
		qDebug() << m_vDayButtons[i]->text() << ":" << datetime.date().day();
		if (m_vDayButtons[i]->text().toInt() == datetime.date().day())
		{
			setClickedStyleSheet(m_vDayButtons[i]);
			m_lastClickBtn = m_vDayButtons[i];
			m_iDay = datetime.date().day();
			break;
		}
	}
	ui.hourComboBox->setCurrentIndex(datetime.time().hour());
	ui.minuteComboBox->setCurrentIndex(datetime.time().minute());
	ui.secComboBox->setCurrentIndex(datetime.time().second());
}

void DateEditDialog::hideDialogSlot()
{
	hide();
}

void DateEditDialog::dayBtnClickSlot()
{
	QPushButton* btn = qobject_cast<QPushButton*>(sender());
	if (btn	== nullptr && btn->text() != "")
	{
		m_iDay = btn->text().toInt();
	}
}

void DateEditDialog::okButtonClickedSlot()
{
	QDateTime datetime = getSelectTime();
	qDebug() << datetime;
	emit dateChanged(datetime);
	this->hide();
}

void DateEditDialog::cancelButtonClickedSlot()
{
	this->hide();
}

void DateEditDialog::initDayDisplay()
{
	m_vDayButtons.append( ui.Btn_1);
	m_vDayButtons.append( ui.Btn_2);
	m_vDayButtons.append( ui.Btn_3);
	m_vDayButtons.append( ui.Btn_4);
	m_vDayButtons.append( ui.Btn_5);
	m_vDayButtons.append( ui.Btn_6);
	m_vDayButtons.append( ui.Btn_7);
	m_vDayButtons.append( ui.Btn_15);
	m_vDayButtons.append( ui.Btn_16);
	m_vDayButtons.append( ui.Btn_17);
	m_vDayButtons.append( ui.Btn_18);
	m_vDayButtons.append( ui.Btn_19);
	m_vDayButtons.append( ui.Btn_20);
	m_vDayButtons.append( ui.Btn_21);
	m_vDayButtons.append( ui.Btn_22);
	m_vDayButtons.append( ui.Btn_23);
	m_vDayButtons.append( ui.Btn_24);
	m_vDayButtons.append( ui.Btn_25);
	m_vDayButtons.append( ui.Btn_26);
	m_vDayButtons.append( ui.Btn_27);
	m_vDayButtons.append( ui.Btn_28);
	m_vDayButtons.append( ui.Btn_29);
	m_vDayButtons.append( ui.Btn_30);
	m_vDayButtons.append( ui.Btn_31);
	m_vDayButtons.append( ui.Btn_32);
	m_vDayButtons.append( ui.Btn_33);
	m_vDayButtons.append( ui.Btn_34);
	m_vDayButtons.append( ui.Btn_35);
	m_vDayButtons.append( ui.Btn_36);
	m_vDayButtons.append( ui.Btn_37);
	m_vDayButtons.append( ui.Btn_38);
	m_vDayButtons.append( ui.Btn_39);
	m_vDayButtons.append( ui.Btn_40);
	m_vDayButtons.append( ui.Btn_41);
	m_vDayButtons.append( ui.Btn_42);
	m_vDayButtons.append( ui.Btn_43);
	m_vDayButtons.append( ui.Btn_44);
	m_vDayButtons.append( ui.Btn_45);
	m_vDayButtons.append( ui.Btn_46);
	m_vDayButtons.append( ui.Btn_47);
	m_vDayButtons.append( ui.Btn_48);
	m_vDayButtons.append( ui.Btn_49);

	for (size_t i = 0,length = m_vDayButtons.length(); i < length; i++)
	{
		m_vDayButtons.at(i)->setStyleSheet("QPushButton{								\
												background-color: rgb(245, 245, 245);	\
												}										\
											QPushButton:hover{							\
												border-color: rgb(75, 130, 192);		\
												border-width:1px;						\
												border-style:solid;						\
																						\
												color: rgb(0, 0, 0);					\
											}");
	}
	setMonth(m_iYear, m_iMonth);

}

void DateEditDialog::initCombox()
{

	for (int i = 0; i <= 9; i++)
	{
		ui.hourComboBox->addItem("0" + QString::number(i));
		ui.minuteComboBox->addItem("0" + QString::number(i));
		ui.secComboBox->addItem("0" + QString::number(i));
	}

	for (int i = 10; i <= 59; i++)
	{
		if (i <= 23)
		{
			ui.hourComboBox->addItem(QString::number(i));
		}
		ui.minuteComboBox->addItem(QString::number(i));
		ui.secComboBox->addItem(QString::number(i));
	}
}

void DateEditDialog::setMonth(int year, int month)
{
	
	QDate date = QDate::currentDate();
	date.setDate(year, month, 1);
	qDebug() << date;
	QString day = date.toString("ddd");
	int start = 0;
	if (day == QString::fromLocal8Bit("周日"))
	{
		start = 0;
	}
	else if (day == QString::fromLocal8Bit("周一"))
	{
		start = 1;
	}
	else if (day == QString::fromLocal8Bit("周二"))
	{
		start = 2;
	}
	else if (day == QString::fromLocal8Bit("周三"))
	{
		start = 3;
	}
	else if (day == QString::fromLocal8Bit("周四"))
	{
		start = 4;
	}
	else if (day == QString::fromLocal8Bit("周五"))
	{
		start = 5;
	}
	else if (day == QString::fromLocal8Bit("周六"))
	{
		start = 6;
	}
	m_iYear = year;
	m_iMonth = month;
	QString daytext = QString::number(m_iMonth) + QString::fromLocal8Bit("月,") + QString::number(m_iYear);
	ui.MonthAndYear->setText(daytext);
	int monthDays = date.daysInMonth();
	// 这个月之前的按钮
	for (size_t i = 0,length = start; i < length; i++)
	{
		m_vDayButtons[i]->setText("");
		m_vDayButtons[i]->setWindowOpacity(0);
		m_vDayButtons[i]->setStyleSheet("QPushButton{background-color: transparent;}");
	}
	// 这个月的按钮
	for (size_t i = start, length = start + monthDays; i < length; i++)
	{
		m_vDayButtons[i]->setText(QString::number(i - start + 1));
		m_vDayButtons.at(i)->setStyleSheet("QPushButton{								\
												background-color: rgb(245, 245, 245);	\
												}										\
											QPushButton:hover{							\
												border-color: rgb(75, 130, 192);		\
												border-width:1px;						\
												border-style:solid;						\
																						\
												color: rgb(0, 0, 0);					\
											}");
		//m_vDayButtons[i]->show();
	}
	// 这个月之后的按钮
	for (size_t i = start + monthDays, length = m_vDayButtons.length(); i < length; i++)
	{
		m_vDayButtons[i]->setText("");
		m_vDayButtons[i]->setStyleSheet("QPushButton{background-color: transparent;}");
	}
	this->adjustSize();
}

void DateEditDialog::setDate(QDate date)
{

}

void DateEditDialog::showTip(QPushButton* btn)
{
	if (btn == nullptr)
	{
		return;
	}
	else if (btn == ui.MonthAndYear)
	{
		ui.tipBtn->setText(QString::fromLocal8Bit("拖动"));
	}
	else if (btn == ui.lastYearBtn)
	{
		ui.tipBtn->setText(QString::fromLocal8Bit("上一年"));
	}
	else if (btn == ui.lastMonthBtn)
	{
		ui.tipBtn->setText(QString::fromLocal8Bit("上个月"));
	}
	else if (btn == ui.todayBtn)
	{
		ui.tipBtn->setText(QString::fromLocal8Bit("转到今日"));
	}
	else if (btn == ui.nextMonthBtn) 
	{
		ui.tipBtn->setText(QString::fromLocal8Bit("下个月"));
	}
	else if (btn == ui.nextYearBtn)
	{
		ui.tipBtn->setText(QString::fromLocal8Bit("下一年"));
	}
	else
	{
		for (size_t i = 0,length = m_vDayButtons.size(); i < length; i++)
		{
			if (btn == m_vDayButtons[i] && m_vDayButtons[i]->text() != "")
			{
				int showday = m_vDayButtons[i]->text().toInt();
				QDate date;
				date.setDate(m_iYear, m_iMonth, showday);
				QString day = date.toString("ddd");
				ui.tipBtn->setText(day + "," + QString::number(m_iMonth) + QString::fromLocal8Bit("月") + QString::number(showday));
			}
		}
	}
}

void DateEditDialog::initInstallEventFilter()
{
	ui.helpBtn->installEventFilter(this);
	ui.lastYearBtn->installEventFilter(this);
	ui.lastMonthBtn->installEventFilter(this);
	ui.todayBtn->installEventFilter(this);
	ui.nextMonthBtn->installEventFilter(this);
	ui.nextYearBtn->installEventFilter(this);
	for (size_t i = 0,length = m_vDayButtons.size(); i < length; i++)
	{
		m_vDayButtons[i]->installEventFilter(this);
	}
}

QDateTime DateEditDialog::getSelectTime()
{
	QDate date;
	QTime time;
	date.setDate(m_iYear, m_iMonth, m_iDay);
	time.setHMS(ui.hourComboBox->currentText().toInt(), ui.minuteComboBox->currentText().toInt(),ui.secComboBox->currentText().toInt());
	QDateTime datetime;
	datetime.setDate(date);
	datetime.setTime(time);
	return datetime;
}

void DateEditDialog::clearStyleSheet(QPushButton* btn)
{
	if (btn != nullptr)
	{
		btn->setStyleSheet("QPushButton{							\
											background-color: rgb(245, 245, 245);	\
											}										\
										QPushButton:hover{							\
											border-color: rgb(75, 130, 192);		\
											border-width:1px;						\
											border-style:solid;						\
																					\
											color: rgb(0, 0, 0);					\
										}");
	}
}

void DateEditDialog::setClickedStyleSheet(QPushButton* btn)
{
	if (btn != nullptr)
	{
		btn->setStyleSheet("background-color:rgb(75, 130, 192);"
			"color: rgb(255, 255, 255);"
			""
		);
	}
}

bool DateEditDialog::eventFilter(QObject* obj, QEvent *event)
{
	m_isFcousme = true;
	if (event->type() == QEvent::MouseButtonPress)
	{
		QPushButton* btn = qobject_cast<QPushButton*>(obj);
		if (btn == nullptr || btn->text() == nullptr)
		{
			return false;
		}
		for (size_t i = 0,length = m_vDayButtons.size(); i < length; i++)
		{
			if (btn == m_vDayButtons[i])
			{
				if (m_lastClickBtn != nullptr)
				{
					clearStyleSheet(m_lastClickBtn);
				}
				setClickedStyleSheet(btn);
				m_iDay = btn->text().toInt();
				m_lastClickBtn = btn;
			}
		}

	}
	else if (event->type() == QEvent::HoverEnter)
	{
		QPushButton* btn = qobject_cast<QPushButton*>(obj);
		showTip(btn);
		this->adjustSize();
	}
	else if (event->type() == QEvent::HoverLeave)
	{
		ui.tipBtn->setText(QString::fromLocal8Bit("拖动"));
	}
	
	m_isFcousme = false;
	return QWidget::eventFilter(obj, event);
}

void DateEditDialog::paintEvent(QPaintEvent* event)
{
	QPainterPath path;
	path.setFillRule(Qt::WindingFill);
	path.addRect(10, 10, this->width() - 20, this->height() - 20);

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.fillPath(path, QBrush(Qt::white));

	QColor color(92, 93, 95, 50);
	int arr[10] = { 150,120,80,50,40,30,20,10,5,5 };
	for (int i = 0; i < 10; i++)
	{
		QPainterPath path;
		path.setFillRule(Qt::WindingFill);
		if (i == 5)
			path.addRect(10 - i - 1, 10 - i - 1, this->width() - (10 - i) * 2, this->height() - (10 - i) * 2);
		else
			path.addRoundedRect(10 - i - 1, 10 - i - 1, this->width() - (10 - i) * 2, this->height() - (10 - i) * 2, 2, 2);

		color.setAlpha(arr[i]);
		painter.setPen(color);
		painter.drawPath(path);
	}
}

void DateEditDialog::focusOutEvent(QFocusEvent *event)
{
	if (!m_isFcousme)
	{
		this->hide();
	}
	
}
