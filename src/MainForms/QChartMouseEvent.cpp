#include "QChartMouseEvent.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QValueAxis>
#include <QPainter>

QChartMouseEvent::QChartMouseEvent(QWidget *parent) :
    QChartView(parent)
{

}

QChartMouseEvent::~QChartMouseEvent()
{

}
void QChartMouseEvent::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
            m_isPress = true;
            this->setRubberBand(QChartView::RectangleRubberBand);
            QPointF curVal = this->chart()->mapToValue(event->pos());
            emit mousePress(curVal);

            if (!m_coordPointFront) {
                m_coordPointFront = new QGraphicsSimpleTextItem(this->chart());
                m_coordPointFront->setZValue(5);
                m_coordPointFront->show();
            }
            m_coordPointFront->setVisible(true);

            /// 获取纵轴
            QValueAxis* axisY = (QValueAxis*)chart()->axisY();
            QPointF curTemp = this->chart()->mapToPosition(QPointF(curVal.x(), axisY->max()));
            m_coordPointFront->setPos(curTemp.x(), curTemp.y());
            m_coordPointFront->setText(QString("X:%1").arg(curVal.x()));
        }
        QChartView::mousePressEvent(event);
}
void QChartMouseEvent::mouseMoveEvent(QMouseEvent* event)
{
    if (!m_coordItem) {
            m_coordItem = new QGraphicsSimpleTextItem(this->chart());
            m_coordItem->setZValue(5);
            m_coordItem->show();
        }
        m_coordItem->setVisible(true);
        const QPoint curPos = event->pos();
        QPointF curVal = this->chart()->mapToValue(curPos);
        QString coordStr = QString("X = %1\nY = %2").arg(curVal.x()).arg(curVal.y());
        m_coordItem->setText(coordStr);
        m_coordItem->setPos(curPos.x(), curPos.y() - 40);

        emit mouseMoving(curVal);

        QChartView::mouseMoveEvent(event);
}
void QChartMouseEvent::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && m_isPress) {
            m_isPress = !m_isPress;
            QPointF curVal = this->chart()->mapToValue(event->pos());
            emit mouseLeftRelease(curVal);

            if (!m_coordPointBack) {
                m_coordPointBack = new QGraphicsSimpleTextItem(this->chart());
                m_coordPointBack->setZValue(5);
                m_coordPointBack->show();
            }
            m_coordPointBack->setVisible(true);

            /// 获取纵轴
            QValueAxis* axisY = (QValueAxis*)chart()->axisY();
            QPointF curTemp = this->chart()->mapToPosition(QPointF(curVal.x(), axisY->max()));
            m_coordPointBack->setPos(curTemp.x(), curTemp.y());
            m_coordPointBack->setText(QString("X:%1").arg(curVal.x()));
        }
        if (event->button() == Qt::RightButton) {
            emit mouseRightRelease();
            m_coordPointBack->setVisible(false);
            m_coordPointFront->setVisible(false);
        }
        this->setRubberBand(QChartView::NoRubberBand);
        QChartView::mouseReleaseEvent(event);
}
void QChartMouseEvent::leaveEvent(QEvent* event)
{
    emit mouseLeave();
    m_coordItem->setVisible(false);
}
