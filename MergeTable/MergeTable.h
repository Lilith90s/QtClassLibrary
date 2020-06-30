#pragma once
#include "mergetable_global.h"
#include <QtWidgets/QTableWidget>
#include <QVector>

class MERGETABLE_EXPORT MergeTable : public QTableWidget
{
public:
    MergeTable(QWidget* parent = nullptr);
	
	void setData(QVector<QStringList> &data);

protected:
	QRect findSameContent(QVector<QStringList> &data,int i_,int j_,QVector<bool> &visited_table);
private:
	void mergeItems(QVector<QStringList> &data);

};
