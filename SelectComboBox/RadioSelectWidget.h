#pragma once
#include "AbstractSelectWidget.h"
#include "selectcombobox_global.h"
#include <QtWidgets/QRadioButton>
class SELECTCOMBOBOX_EXPORT RadioSelectWidget : public AbstractSelectWidget
{
public:
	RadioSelectWidget();
	void setLabelText(QString text) override;
private:
	QRadioButton* m_radio_button = nullptr;
};

