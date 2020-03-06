#pragma once
#include <QComboBox>
#include "hretrievalcombox_global.h"

#include <QMultiMap>
#include <QString>

class HRETRIEVALCOMBOX_EXPORT HRetrievalCombox
	:public QComboBox
{
	Q_OBJECT
public:
	HRetrievalCombox(QWidget* parent = nullptr);
	void init();
	void setData(QMultiMap<QString, QString> data);
public slots:
	void editTextChangedSlot(const QString &text);
private:

	// ¼üÖµ¶Ô
	QMultiMap<QString, QString> data;

	// µ¯³ö¿ò
	QCompleter* completer;
};
