#ifndef PAINTDRAWRECTLINE_H
#define PAINTDRAWRECTLINE_H

#include "PaintDrawBase.h"

class PaintDrawRectLine : public PaintDrawBase
{
public:
    virtual void draw(QPainter *painter,const QwtScaleMap &xMap,
                      const QwtScaleMap &yMap,const QRectF &) const
    {
        const QPointF bPoint = QwtScaleMap::transform(xMap, yMap, beginPoint);
        const QPointF ePoint = QwtScaleMap::transform(xMap, yMap, endPoint);
        double x1 = bPoint.x();
        double y1 = bPoint.y();
        double x2 = ePoint.x();
        double y2 = ePoint.y();
        double x3,y3;
        if(fabs(y2-y1) > fabs(x2-x1))
        {
            if(x1 < x2 && y1 > y2)
            {
                x1 = x1;
                y1 = y1 -(y1-y2)/3;
            }
            else if(x1 < x2 && y1 < y2)
            {
                x1 = x1;
                y1 = y1;
            }
            else if(x1 > x2 && y1 > y2)
            {
                x1 = x2;
                y1 = y1 +(y2-y1)/3;
            }
            else if(x1 > x2 && y1 < y2)
            {
                x1 = x2;
                y1 = y1;
            }
            x2 = fabs(ePoint.x()-bPoint.x());
            y2 = fabs(ePoint.y()-bPoint.y())/3;
            x3 = ePoint.x();
            y3 = bPoint.y();
            QwtPainter::drawRect(painter,x1,y1,x2,y2);
            QwtPainter::drawLine(painter,x3,y3,x3,ePoint.y());
        }
        else
        {
            if(x1 < x2 && y1 > y2)
            {
                x1 = x1;
                y1 = y2;
            }
            else if(x1 < x2 && y1 < y2)
            {
                x1 = x1;
                y1 = y1;
            }
            else if(x1 > x2 && y1 > y2)
            {
                x1 = x1 -(x1-x2)/3;
                y1 = y2;
            }
            else if(x1 > x2 && y1 < y2)
            {
                x1 = x1 -(x1-x2)/3;
                y1 = y1;
            }
            x2 = fabs(ePoint.x()-bPoint.x())/3;
            y2 = fabs(ePoint.y()-bPoint.y());
            x3 = bPoint.x();
            y3 = ePoint.y();
            QwtPainter::drawRect(painter,x1,y1,x2,y2);
            QwtPainter::drawLine(painter,x3,y3,ePoint.x(),ePoint.y());
        }
        QwtPainter::drawText(painter,ePoint,text);
    }

    PaintDrawRectLine(QPointF xPoint,QPointF yPoint,QColor color)
    {
        beginPoint = xPoint;
        endPoint = yPoint;
        _color = color;
    }
    void setPoint(QPointF xPoint,QPointF yPoint)
    {
        beginPoint = xPoint;
        endPoint = yPoint;
    }
    void setInputText(QString str)
    {
        text = str;
    }
private:
    QPointF beginPoint;
    QPointF endPoint;
    QColor _color;
    QString text;
};
#endif // PAINTDRAWRECTLINE_H

