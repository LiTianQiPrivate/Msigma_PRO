#ifndef PAINTDRAWDOUBLEARROW_H
#define PAINTDRAWDOUBLEARROW_H
#include "PaintDrawBase.h"
class PaintDrawDoubleArrow : public PaintDrawBase
{
public:
    virtual void draw(QPainter *painter,const QwtScaleMap &xMap,
                      const QwtScaleMap &yMap,const QRectF &) const
    {
        double par = 10.0;
        const QPointF bPoint = QwtScaleMap::transform(xMap, yMap, beginPoint);
        const QPointF ePoint = QwtScaleMap::transform(xMap, yMap, endPoint);
        double x1 = bPoint.x();
        double y1 = bPoint.y();
        double x2 = ePoint.x();
        double y2 = ePoint.y();
        QPointF eePoint;
        eePoint.setX(bPoint.x()+(ePoint.x()-bPoint.x())/5*2);
        eePoint.setY(bPoint.y()+(ePoint.y()-bPoint.y())/5*2);
        double slopy = atan2((eePoint.y() - bPoint.y() ), (eePoint.x()  - bPoint.x()));
        double cosy = cos(slopy);
        double siny = sin(slopy);
        QPointF point1 = QPointF(bPoint.x()  - int(-par*cosy - (par / 2.0*siny)), bPoint.y()- int(-par*siny + (par / 2.0*cosy)));
        QPointF point2 = QPointF(bPoint.x()  - int(-par*cosy + (par / 2.0*siny)), bPoint.y() + int(par / 2.0*cosy + par*siny));
        slopy = (180 + slopy*180/3.1415926)*3.1415936/180;
        cosy = cos(slopy);
        siny = sin(slopy);
        int offsetX = int(par*siny / 3);
        int offsetY = int(par*cosy / 3);
        QPointF point3, point4;
        point3 = QPointF(bPoint.x()+ int(-par*cosy - (par / 2.0*siny)) + offsetX, bPoint.y() + int(-par*siny + (par / 2.0*cosy)) - offsetY);
        point4 = QPointF(bPoint.x() + int(-par*cosy + (par / 2.0*siny) - offsetX), bPoint.y() - int(par / 2.0*cosy + par*siny) + offsetY);
        QPolygonF pointV;
        QPolygonF pointS;
        pointV.append(bPoint);
        pointV.append(point1);
        pointV.append(point2);
        pointS.append(eePoint);
        pointS.append(point3);
        pointS.append(point4);
        QwtPainter::drawPolygon(painter,pointV);
        QwtPainter::drawPolygon(painter,pointS);

        /*****************第二个箭头******************/
        eePoint.setX(bPoint.x()+(ePoint.x()-bPoint.x())/5*3);
        eePoint.setY(bPoint.y()+(ePoint.y()-bPoint.y())/5*3);
        slopy = atan2((eePoint.y() - bPoint.y() ), (eePoint.x()  - bPoint.x()));
        cosy = cos(slopy);
        siny = sin(slopy);
        point1 = QPointF(ePoint.x()  + int(-par*cosy - (par / 2.0*siny)), ePoint.y() + int(-par*siny + (par / 2.0*cosy)));
        point2 = QPointF(ePoint.x()  + int(-par*cosy + (par / 2.0*siny)), ePoint.y() - int(par / 2.0*cosy + par*siny));
        offsetX = int(par*siny / 3);
        offsetY = int(par*cosy / 3);
        point3 = QPointF(ePoint.x() + int(-par*cosy - (par / 2.0*siny)) + offsetX, ePoint.y() + int(-par*siny + (par / 2.0*cosy)) - offsetY);
        point4 = QPointF(ePoint.x() + int(-par*cosy + (par / 2.0*siny) - offsetX), ePoint.y() - int(par / 2.0*cosy + par*siny) + offsetY);
        QPolygonF pointW;
        QPolygonF pointE;
        pointW.append(ePoint);
        pointW.append(point1);
        pointW.append(point2);
        pointE.append(eePoint);
        pointE.append(point3);
        pointE.append(point4);
        QwtPainter::drawPolygon(painter,pointW);
        QwtPainter::drawPolygon(painter,pointE);
        if(x1 < x2 && y1 <y2)
        {
            slopy = (atan2(fabs(y2-y1),fabs(x2-x1)))*180/3.1415926;
        }
        else if(x1 < x2 && y1 > y2)
        {
            slopy = 360 - (atan2(fabs(y2-y1),fabs(x2-x1)))*180/3.1415926;
        }
        else if(x1 > x2 && y1 > y2)
        {
            slopy = 180 +(atan2(fabs(y2-y1),fabs(x2-x1)))*180/3.1415926;
        }
        else if(x1 > x2 && y1 < y2)
        {
            slopy = 180 -(atan2(fabs(y2-y1),fabs(x2-x1)))*180/3.1415926;
        }
        painter->translate((x1+x2)/2,(y1+y2)/2);
        painter->rotate(slopy);
        int ii = ((PaintDrawBase*)this)->getFontWidth(painter,text);
        painter->drawText(-ii/2,5,text);
    }

    PaintDrawDoubleArrow(QPointF xPoint,QPointF yPoint,QColor color)
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
#endif // PAINTDRAWDOUBLEARROW_H
