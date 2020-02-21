#include "HDateTimeLineEdit.h"
#include <QDebug>

HDateTimeLineEdit::HDateTimeLineEdit(QWidget* parent /*= nullptr*/)
	: QLineEdit(parent)
{
	m_pDateEditDialog = new DateEditDialog(this);
	m_pDateEditDialog->hide();
	m_pDateEditDialog->adjustSize();
	QIcon icon(":/HDateTimeEdit/Resources/Date.png");
	m_pSelectDateAction = new QAction(this);
	m_pSelectDateAction->setIcon(icon);
	this->addAction(m_pSelectDateAction, QLineEdit::TrailingPosition);
	connect(m_pSelectDateAction, &QAction::triggered, this, &HDateTimeLineEdit::showDateSelectDialogSlot);
	connect(m_pDateEditDialog, &DateEditDialog::dateChanged, this, &HDateTimeLineEdit::setTimeEditSlot);
}
void HDateTimeLineEdit::showDateSelectDialogSlot()
{
	m_pDateEditDialog->show();
	m_pDateEditDialog->setGeometry(this->pos().x() - 5, this->pos().y() + 10, m_pDateEditDialog->width(), m_pDateEditDialog->height());
}

void HDateTimeLineEdit::setTimeEditSlot(QDateTime& datetime)
{
	QString text = datetime.toString("yyyy/MM/dd HH:mm:ss");
	qDebug() << text;
	this->setText(text);
}