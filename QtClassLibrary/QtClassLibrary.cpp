#include "QtClassLibrary.h"
#include <QDateTime>
#include <QDebug>
#include <QCompleter>
#include <QAbstractItemView>
#include <MaskWidget.h>
#include <QTimer>
#include <QStackedWidget>
#include "TableWidgetDialog.h"
QtClassLibrary::QtClassLibrary(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	qDebug() << DateEditDialog::g_DateFormat;
	ui.comboBox->init();
	m_loading_dialog = new LoadingWidget;
	//m_loading_dialog->setModal(true);
	
	//m_loading_dialog.hide();
	// ui.comboBox->setEditable(true);
	// QStringList strings;
	// strings << "hello" << "hi" << "word"; 
	// 
	// QCompleter* completer = new QCompleter(strings, this); 
	// completer->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
	// completer->popup()->setStyleSheet("    background-color: #294662;\
	//                                     color: #ffffff;\
	//                                     border: 1px solid #375C80;\
	//                                     border-radius: 5px;\
	//                                     padding: 0px 0px 0px 0px;\
	//                                     min-width: 17px;\
	//                                     font: 14px \"Arial\";");
	// ui.comboBox->setCompleter(completer);
	MaskWidget::Instance()->setMainWidget(this);
	connect(ui.loadingButton, &QPushButton::clicked, this, &QtClassLibrary::loadingButton_clicked);
	connect(ui.loadingButton, &QPushButton::clicked, [this]() {
		//setAttribute(Qt::WA_TransparentForMouseEvents, false);
		// m_loading_dialog->show();
		int length = 10000;
		for (size_t i = 0; i < length; i++)
		{
			ui.lineEdit->setText(QString::number(i));
			qApp->processEvents();
		}
		//this->activateWindow();
		m_loading_dialog->close();
	});
	

	connect(ui.setTableData, &QPushButton::clicked, [this]() {
		TableWidgetDialog dialog;
		// dialog.show();
		if (dialog.exec() == QDialog::Accepted)
		{
			QVector<QStringList> data = dialog.getData();
			if (data.size() <= 0)
			{
				return;
			}
			ui.stackedWidget->setCurrentIndex(1);
			ui.tableWidget_2->setData(data);
			//ui.tableWidget->widget();
		}
	});

	initWebScraping();
	

	// 初始化可合并表头
	QStringList header;
	header << QString::fromLocal8Bit("班次")
		<< QString::fromLocal8Bit("人数")
		<< QString::fromLocal8Bit("重量")
		<< QString::fromLocal8Bit("备注");
	ui.tableWidget_2->setHorizontalHeaderLabels(header);

}

void QtClassLibrary::testButton()
{
	QDateTime date =  QDateTime::fromString( ui.lineEdit->text(),DateEditDialog::g_DateFormat);
	qDebug() << date;
}

// 加载框示例
void QtClassLibrary::loadingButton_clicked()
{
	m_loading_dialog->show();
}

void QtClassLibrary::initWebScraping()
{
	connect(ui.searchSongButton, &QPushButton::clicked, [this]() {
		ui.songListWidget->clear();
		QString song_name = ui.songNameEdit->text();
		WebScraping web_scraping;
		m_song_infos = web_scraping.findSongs(song_name);
		for (auto song_info : m_song_infos)
		{
			ui.songListWidget->addItem(song_info.name);
		}

	});
	connect(ui.downloadButton, &QPushButton::clicked, [this]() {
		QString song_name = ui.songNameEdit->text();
		WebScraping web_scraping;
		if (m_song_infos.size()!= 0)
		{
			web_scraping.downloadSong(m_song_infos[ui.songListWidget->currentRow()],QString("C:\\Users\\22579\\Documents\\tmp\\songs"));
		}
	});
}
