#ifndef PAINTDRAWELIPSEARROW_H
#define PAINTDRAWELIPSEARROW_H
#include "PaintDrawBase.h"
class PaintDrawElipseArrow : public PaintDrawBase
{
public:
    virtual void draw(QPainter *painter,const QwtScaleMap &xMap,
                      const QwtScaleMap &yMap,const QRectF &) const
    {
        const QPointF bPoint = QwtScaleMap::transform(xMap, yMap, beginPoint);
        const QPointF ePoint = QwtScaleMap::transform(xMap, yMap, endPoint);
        QwtPainter::drawEllipse(painter,QRectF(bPoint.x(),bPoint.y(),ePoint.x()-bPoint.x(),ePoint.y()-bPoint.y()));
        QPointF pointW(bPoint.x()+(ePoint.x()-bPoint.x())/2,ePoint.y());
        double par = 10.0;
        double slopy = atan2((ePoint.y() - pointW.y() ), (ePoint.x()  - pointW.x()));
        double cosy = cos(slopy);
        double siny = sin(slopy);
        QPointF point1 = QPointF(ePoint.x()  + int(-par*cosy - (par / 2.0*siny)), ePoint.y()+ int(-par*siny + (par / 2.0*cosy)));
        QPointF point2 = QPointF(ePoint.x()  + int(-par*cosy + (par / 2.0*siny)), ePoint.y() - int(par / 2.0*cosy + par*siny));
        int offsetX = int(par*siny / 3);
        int offsetY = int(par*cosy / 3);
        QPointF point3, point4;
        point3 = QPointF(ePoint.x()+ int(-par*cosy - (par / 2.0*siny)) + offsetX, ePoint.y() + int(-par*siny + (par / 2.0*cosy)) - offsetY);
        point4 = QPointF(ePoint.x() + int(-par*cosy + (par / 2.0*siny) - offsetX), ePoint.y() - int(par / 2.0*cosy + par*siny) + offsetY);
        QPolygonF pointV;
        QPolygonF pointS;
        pointV.append(ePoint);
        pointV.append(point1);
        pointV.append(point2);
        pointS.append(pointW);
        pointS.append(point3);
        pointS.append(point4);
        QwtPainter::drawPolygon(painter,pointV);
        QwtPainter::drawPolygon(painter,pointS);
        QwtPainter::drawText(painter,ePoint,text);
    }

    PaintDrawElipseArrow(QPointF xPoint,QPointF yPoint,QColor color)
    {
        // 根据圆心和半径构造出圆的外接矩形
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
#endif // PAINTDRAWELIPSEARROW_H
