#include "HRetrievalCombox.h"
#include <qlineedit.h>
#include <QCursor>
#include <QDebug>
#include <QCompleter>
#include <QAbstractItemView>


HRetrievalCombox::HRetrievalCombox(QWidget* parent)
	:QComboBox(parent)
{
	connect(this, &QComboBox::editTextChanged, this, &HRetrievalCombox::editTextChangedSlot);
	data.insert("HB", "he bei");
	data.insert("Hb", "hu bei");
	data.insert("NJ", "nan jing");
	// qDebug() << data;
}

void HRetrievalCombox::init()
{
	setEditable(true);

}

void HRetrievalCombox::setData(QMultiMap<QString, QString> data)
{
	this->data = data;
}

void HRetrievalCombox::editTextChangedSlot(const QString &text)
 {
	
	QStringList strings;
	// strings << "hello" << "hi" << "word";
	for (QMultiMap<QString, QString>::iterator it = data.begin(); it != data.end(); it++)
	{
		if (it.key().toLower().contains(text.toLower()))
		{
			strings << it.value();
		}
	}
	qDebug() << strings;
	QCompleter* completer = new QCompleter(strings, this);
	completer->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
	//completer->popup()->setStyleSheet("    background-color: #294662;\
    //                                    color: #ffffff;\
    //                                    border: 1px solid #375C80;\
    //                                    border-radius: 5px;\
    //                                    padding: 0px 0px 0px 0px;\
    //                                    min-width: 17px;\
    //                                    font: 14px \"Arial\";");
	this->setCompleter(completer);
 }
