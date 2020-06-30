#include "MergeTable.h"
#include <QStringList>

struct DataTree
{
	// ���׽ڵ�
	QString father;
	// ���ӽڵ�
	QStringList children;
};
MergeTable::MergeTable(QWidget* parent /*= nullptr*/)
	:QTableWidget(parent)
{

}

void MergeTable::setData(QVector<QStringList> &data)
{
	if (data.size() <= 0)
	{
		return;
	}
	setRowCount(data.size());
	setColumnCount(data[0].size());
	// ��ʼ������
	for (int i = 0, length = data.size(); i < length; i++)
	{
		for (int j = 0, length = data[i].size(); j < length; j++)
		{
			QTableWidgetItem* item = new QTableWidgetItem;
			item->setText(data[i][j]);
			this->setItem(i, j, item);
		}
	}
	mergeItems(data);
}


QRect MergeTable::findSameContent(QVector<QStringList> &data,int i_, int j_, QVector<bool> &visited_table)
{
	if (data.size() <= 1)
	{
		return QRect(0,0,0,0);
	}
	int min_length = data[0].size();
	for (int i = i_, length = data.size(); i < length; i++)
	{
		for (int j = 0, length = data[i].size(); j < length; j++)
		{
			if (data[i][j] == data[i-1][j])
			{
				visited_table[i] = true;
			}
			else
			{
				if (j == 0)
				{
					QRect rect(i_, 0, i-i_, min_length);
					return rect;
				}
				else if (j < min_length) // ��������
				{
					min_length = j;
				}
				break;
			}
		}
	}
	return QRect(i_, 0, min_length, data.size()-i_);
}

// ���ù���������������б�ϲ�
void MergeTable::mergeItems(QVector<QStringList> &data)
{
	if (data.size() <= 0)
	{
		return;
	}
	QVector<bool> visited_table(data.size()); // �ѷ����б�
	


	for (int i=0,length = data.size();i<length ;i++)
	{
		if (visited_table[i] == true)
		{
			continue;
		}
		QRect rect = findSameContent(data, i + 1, 0, visited_table);
		if (!rect.isEmpty())
		{
			for (int j=0; j< rect.width();j++)
			{
				this->setSpan(rect.x() - 1, rect.y()+j, rect.height() + 1, 1);
			}
			
		}
	}
}
