#include "GanntView.h"

#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalPercentBarSeries>
#include <QTimer>

GanntView::GanntView(QWidget* parent /*= nullptr*/)
	: QChartView(parent)
{
	//![1]
	QBarSet *set0 = new QBarSet("Jane");
	QBarSet *set1 = new QBarSet("John");
	QBarSet *set2 = new QBarSet("Axel");
	QBarSet *set3 = new QBarSet("Mary");
	QBarSet *set4 = new QBarSet("Samantha"); 
	QBrush brush;
	brush.setColor(qRgba(0, 0, 0, 150));
	set0->setBrush(brush);
	*set0 << 1 << 2 << 3 << 4 << 5 << 6;
	*set1 << 5 << 0 << 0 << 4 << 0 << 7;
	*set2 << 3 << 5 << 8 << 13 << 8 << 5;
	*set3 << 5 << 6 << 7 << 3 << 4 << 5;
	*set4 << 9 << 7 << 5 << 3 << 1 << 2;
	//![1]

	//![2]

	QHorizontalPercentBarSeries *series = new QHorizontalPercentBarSeries();
	series->append(set0);
	series->append(set1);
	series->append(set2);
	series->append(set3);
	series->append(set4);

	QTimer* timer = new QTimer;
	timer->start(5000);
	QObject::connect(timer, &QTimer::timeout, [series, set4]() {
		QBarSet *set5 = new QBarSet("test");
		*set5 << 1 << 1 << 1 << 1 << 1 << 1;
		series->append(set5);
	});
	//![2]

	//![3]
	QChart *chart = new QChart();
	chart->addSeries(series);
	chart->setTitle(QStringLiteral("aa"));
	chart->setAnimationOptions(QChart::SeriesAnimations);
	//![3]

	//![4]
	QStringList categories;
	categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun";
	QBarCategoryAxis *axis = new QBarCategoryAxis();
	axis->append(categories);
	chart->createDefaultAxes();
	chart->setAxisY(axis, series);

	QStringList categories_y;
	categories_y << "121" << "202" << "33" << "Apr" << "May" << "Jun";
	QBarCategoryAxis *axis_y = new QBarCategoryAxis();
	axis_y->append(categories_y);
	chart->setAxisX(axis_y);
	//![4]



	//![5]
	chart->legend()->setVisible(true);
	chart->legend()->setAlignment(Qt::AlignBottom);
	setChart(chart);
	setRenderHint(QPainter::Antialiasing);
}
