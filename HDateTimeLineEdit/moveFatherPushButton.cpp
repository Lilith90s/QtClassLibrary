#include "moveFatherPushButton.h"
#include <QDebug>

moveFatherPushButton::moveFatherPushButton(QWidget* parent /*= nullptr*/)
	: m_pParent(parent)
{
	this->setCursor(QCursor(Qt::DragMoveCursor));
}

moveFatherPushButton::~moveFatherPushButton()
{
}

void moveFatherPushButton::mouseMoveEvent(QMouseEvent* event)
{
	if (m_pParent != nullptr)
	{
		auto x = event->globalPos().x() - m_cacheX - this->geometry().x();
		auto y = event->globalPos().y() - m_cacheY - this->geometry().y();
		m_pParent->move(x, y);
		// qDebug() << "x" << event->globalPos().x() << m_cacheX << this->geometry().x();
		// qDebug() << "y" << event->globalPos().y() << m_cacheY << this->geometry().y();
		// qDebug() << x << y;
	}
	QPushButton::mouseMoveEvent(event);
}

void moveFatherPushButton::mousePressEvent(QMouseEvent* event)
{
	m_cacheX = event->pos().x();
	m_cacheY = event->pos().y();
	QPushButton::mousePressEvent(event);
}
