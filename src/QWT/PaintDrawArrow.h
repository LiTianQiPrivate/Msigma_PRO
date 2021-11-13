#ifndef PAINTDRAWARROW_H
#define PAINTDRAWARROW_H

#include "PaintDrawBase.h"
#include <QInputDialog>
#include "DialogText.h"

class PaintDrawArrow :  public PaintDrawBase
{
public:
    PaintDrawArrow(QPointF xPoint,QPointF yPoint,QColor color)
    {
        beginPoint = xPoint;
        endPoint = yPoint;
        _color = color;
    }
    virtual void draw(QPainter *painter,const QwtScaleMap &xMap,
                      const QwtScaleMap &yMap,const QRectF &) const
    {
        double par = 10.0;
        const QPointF bPoint = QwtScaleMap::transform(xMap, yMap, beginPoint);
        const QPointF ePoint = QwtScaleMap::transform(xMap, yMap, endPoint);
        double slopy = atan2((ePoint.y() - bPoint.y() ), (ePoint.x()  - bPoint.x()));
        double cosy = cos(slopy);
        double siny = sin(slopy);
        QPointF point1 = QPointF(ePoint.x()  + int(-par*cosy - (par / 2.0*siny)), ePoint.y()+ int(-par*siny + (par / 2.0*cosy)));
        QPointF point2 = QPointF(ePoint.x()  + int(-par*cosy + (par / 2.0*siny)), ePoint.y() - int(par / 2.0*cosy + par*siny));
        int offsetX = int(par*siny / 3);
        int offsetY = int(par*cosy / 3);
        QPointF point3, point4;
        point3 = QPointF(ePoint.x()+ int(-par*cosy - (par / 2.0*siny)) + offsetX, ePoint.y() + int(-par*siny + (par / 2.0*cosy)) - offsetY);
        point4 = QPointF(ePoint.x() + int(-par*cosy + (par / 2.0*siny) - offsetX), ePoint.y() - int(par / 2.0*cosy + par*siny) + offsetY);
//        QBrush brush(QColor(0,255,0,100));
        QPolygonF pointV;
        QPolygonF pointS;
        pointV.append(ePoint);
        pointV.append(point1);
        pointV.append(point2);
        pointS.append(bPoint);
        pointS.append(point3);
        pointS.append(point4);
        QwtPainter::drawPolygon(painter,pointV);
        QwtPainter::drawPolygon(painter,pointS);
        double slopy1 = ((PaintDrawBase *)this)->getSlopy(bPoint,ePoint);
        painter->setRenderHint(QPainter::Antialiasing,true);
        painter->translate(bPoint.x()+(ePoint.x()-bPoint.x())/2,bPoint.y()+(ePoint.y()-bPoint.y())/2);
        painter->rotate(slopy1);
        int ii = ((PaintDrawBase*)this)->getFontWidth(painter,text);
        QwtPainter::drawText(painter,-ii/2,-5,text);
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
#endif // PAINTDRAWARROW_H
