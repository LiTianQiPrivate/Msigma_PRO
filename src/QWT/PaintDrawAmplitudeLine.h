#ifndef PAINTDRAWAMPLITUDELINE_H
#define PAINTDRAWAMPLITUDELINE_H
#include "PaintDrawBase.h"

class PaintDrawAmplitudeLine : public PaintDrawBase
{
public:
    void draw(QPainter *painter,const QwtScaleMap &xMap,
                      const QwtScaleMap &yMap,const QRectF &) const
    {
        const QPointF bPoint = QwtScaleMap::transform(xMap, yMap, beginPoint);
        const QPointF ePoint = QwtScaleMap::transform(xMap, yMap, endPoint);
        painter->drawLine(bPoint.x(),bPoint.y(),bPoint.x()+(ePoint.x() - bPoint.x())*0.45,bPoint.y()+(ePoint.y() - bPoint.y())*0.45);
        painter->drawLine(bPoint.x()+(ePoint.x() - bPoint.x())*0.6,bPoint.y()+(ePoint.y() - bPoint.y())*0.6,ePoint.x(),ePoint.y());
        double slopy = ((PaintDrawBase *)this)->getSlopy(bPoint,ePoint);
        painter->setRenderHint(QPainter::Antialiasing,true);
        painter->translate(bPoint.x()+(ePoint.x() - bPoint.x())*0.45,bPoint.y()+(ePoint.y() - bPoint.y())*0.45);
        painter->rotate(slopy);
        QwtPainter::drawText(painter,0,0,text);
    }

    PaintDrawAmplitudeLine(QPointF xPoint,QPointF yPoint,QColor color)
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
#endif // PAINTDRAWAMPLITUDELINE_H
