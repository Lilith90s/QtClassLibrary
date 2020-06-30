#pragma once

#include "ganntview_global.h"
#include <QtCharts/QChartView>
QT_CHARTS_USE_NAMESPACE
class GANNTVIEW_EXPORT GanntView
	:public QChartView
{
public:
    GanntView(QWidget* parent = nullptr);
};
