#ifndef PAINTDRAWBRACKET_H
#define PAINTDRAWBRACKET_H

#include "PaintDrawBase.h"
class PaintDrawBracket : public PaintDrawBase
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
        QPixmap pixmap;
        double slopy;
        pixmap.load("../Image/1.png");
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
        double left = sqrt(x1*x1+y1*y1);
        double right = sqrt((x2 - x1)*(x2 - x1)+(y2 - y1)*(y2 - y1));
        QPoint offsetPoint(x2 - x1, y2 - y1);
        int w = 20;
        painter->setRenderHint(QPainter::Antialiasing,true);
        painter->translate(x1, y1 - w/2);
        painter->rotate(slopy);
        QRectF rect(x1,y1, x2 - x1,y2-y1);
        painter->drawPixmap(0,0, right,w,pixmap);
        int ii = ((PaintDrawBase*)this)->getFontWidth(painter,text);
        qDebug() <<"ii == " << ii;
//        ssss();
        //int textLenght = text.length()
        painter->drawText((right-ii)/2, -w/2,text);
    }

    PaintDrawBracket(QPointF xPoint,QPointF yPoint,QColor color)
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
#endif // PAINTDRAWBRACKET_H
