#pragma once
#include <qpushbutton.h>
#include <QWidget>
#include <QMouseEvent>
class moveFatherPushButton :
	public QPushButton
{
public:
	moveFatherPushButton(QWidget* parent = nullptr);
	~moveFatherPushButton();
private:

	void mouseMoveEvent(QMouseEvent* event) override;

	void mousePressEvent(QMouseEvent* event) override;

	QWidget* m_pParent{nullptr};

	// 鼠标单击时x位置
	int m_cacheX;

	// 鼠标单击时y位置
	int m_cacheY;

};

