#include "TableWidgetDialog.h"
#include <QVector>
#include <QStringList>
#include <QPushButton>
#include <QTableWidgetItem>
TableWidgetDialog::TableWidgetDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	ui.tableWidget->setColumnCount(4);
	QStringList header;
	header << QString::fromLocal8Bit("班次")
		<< QString::fromLocal8Bit("人数")
		<< QString::fromLocal8Bit("重量")
		<< QString::fromLocal8Bit("备注");
	ui.tableWidget->setHorizontalHeaderLabels(header);
	connect(ui.okButton, &QPushButton::clicked, [this]() {
		accept();
	});
	connect(ui.cancelButton, &QPushButton::clicked, [this]() {
		reject();
	});
	connect(ui.addRowPushButton, &QPushButton::clicked, [this]() {
		int row = ui.tableWidget->rowCount();
		ui.tableWidget->insertRow(row);
		QTableWidgetItem* item1 = new QTableWidgetItem;
		QTableWidgetItem* item2 = new QTableWidgetItem;
		QTableWidgetItem* item3 = new QTableWidgetItem;
		QTableWidgetItem* item4 = new QTableWidgetItem;
		ui.tableWidget->setItem(row, 0,item1);
		ui.tableWidget->setItem(row, 1, item2);
		ui.tableWidget->setItem(row, 2, item3);
		ui.tableWidget->setItem(row, 3, item4);
	});
}

TableWidgetDialog::~TableWidgetDialog()
{

}

QVector<QStringList> TableWidgetDialog::getData()
{
	QVector<QStringList> ret;
	for (size_t i = 0,length = ui.tableWidget->rowCount(); i < length; i++)
	{
		QString text1, text2, text3, text4;
		QStringList line;
		line << ui.tableWidget->item(i,0)->text() 
			<< ui.tableWidget->item(i, 1)->text() 
			<< ui.tableWidget->item(i, 2)->text() 
			<< ui.tableWidget->item(i, 3)->text();
		ret.append(line);
	}
	return ret;
}
