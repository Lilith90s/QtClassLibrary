#include "RadioSelectWidget.h"
#include <QRadioButton>
RadioSelectWidget::RadioSelectWidget()
{
	m_radio_button = new QRadioButton(this);
	setButton(m_radio_button);
	setLabelText("hello wrold");
}

void RadioSelectWidget::setLabelText(QString text)
{
	m_radio_button->setText(text);
}
