#ifndef MASKWIDGET_H
#define MASKWIDGET_H

/**
 * �������ֲ�ؼ� ����:feiyangqingyun(QQ:517216493) 2016-12-26
 * 1:��������Ҫ���ֵ�������,�Զ�����������λ����ʾ�������
 * 2:ֻ��Ҫ���������������һ��ʼ������м���,�㹻��
 * 3:������͸����
 * 4:���������ֲ���ɫ
 * 5:��������Ϣѭ��
 */

#include <QWidget>
#include "loadingwidget_global.h"

#ifdef quc
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT MaskWidget : public QWidget
#else
class LOADINGWIDGET_EXPORT MaskWidget : public QWidget
#endif

{
	Q_OBJECT
public:
	static MaskWidget *Instance();
	explicit MaskWidget(QWidget *parent = 0);
	QWidget* getMainWidget();
protected:
	void showEvent(QShowEvent *);
	bool eventFilter(QObject *obj, QEvent *event);

private:
	static QScopedPointer<MaskWidget> self;
	QWidget *mainWidget;        //��Ҫ���ֵ�������
	QStringList dialogNames;    //���ܵ����Ĵ���������Ƽ�������
	QWidget *dialogWidget; // ����

public Q_SLOTS:
	void setMainWidget(QWidget *mainWidget);
	void setDialogNames(const QStringList &dialogNames);
	void setDialogWidget(QWidget *widget);
	void setBgColor(const QColor &bgColor);
	void setOpacity(double opacity);
};

#endif // MASKWIDGET_H
