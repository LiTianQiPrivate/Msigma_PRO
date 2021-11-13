#ifndef PAINTDRAWKEYPOINT_H
#define PAINTDRAWKEYPOINT_H
#include "PaintDrawBase.h"

class PaintDrawKeyPoint : public PaintDrawBase
{
public:
    void draw(QPainter *painter,const QwtScaleMap &xMap,
                      const QwtScaleMap &yMap,const QRectF &) const
    {
        const QPointF bPoint = QwtScaleMap::transform(xMap, yMap, beginPoint);
        const QPointF ePoint = QwtScaleMap::transform(xMap, yMap, endPoint);
        const QPointF m_xPoint = QwtScaleMap::transform(xMap, yMap, pointPoint);
        QBrush sh(QColor(255,255,0,50));
        QPainterPath path;
        path.addEllipse(bPoint.x(),bPoint.y(),30,30);
        painter->fillPath(path,sh);
        if(drawLineFlag)
        {
            QPen pen;
            pen.setStyle(Qt::DashDotLine);
            pen.setWidth(1);
            pen.setBrush(_color);
            painter->setPen(pen);
            painter->drawLine(bPoint.x()+15,bPoint.y()+15,m_xPoint.x(),bPoint.y()+15);
            painter->drawLine(bPoint.x()+15,bPoint.y()+15,ePoint.x()+15,ePoint.y());
        }
        //QwtPainter::drawText(painter,bPoint,text);
    }

    PaintDrawKeyPoint(QPointF xPoint,QPointF yPoint,QColor color)
    {
        // 根据圆心和半径构造出圆的外接矩形
        beginPoint = xPoint;
        endPoint = yPoint;
        _color = color;
        text = "";
    }
    void setPoint(QPointF xPoint,QPointF yPoint)
    {
        beginPoint = xPoint;
        endPoint = yPoint;
    }
    void setXPoint(QPointF xPoint,bool flag)
    {
        pointPoint = xPoint;
        drawLineFlag = flag;
    }
    void setInputText(QString str)
    {
        text = str;
    }
private:
    QPointF beginPoint;
    QPointF endPoint;
    QPointF pointPoint;
    QColor _color;
    bool drawLineFlag = false;
    QString text;

};
#endif // PAINTDRAWKEYPOINT_H
