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

	// ��굥��ʱxλ��
	int m_cacheX;

	// ��굥��ʱyλ��
	int m_cacheY;

};

