#ifndef PAINTDRAWELIPSE_H
#define PAINTDRAWELIPSE_H

#include "PaintDrawBase.h"

class PaintDrawElipse : public PaintDrawBase
{
public:
    void draw(QPainter *painter,const QwtScaleMap &xMap,
                      const QwtScaleMap &yMap,const QRectF &) const
    {
        const QPointF bPoint = QwtScaleMap::transform(xMap, yMap, beginPoint);
        const QPointF ePoint = QwtScaleMap::transform(xMap, yMap, endPoint);
        QwtPainter::drawEllipse(painter,QRectF(bPoint.x(),bPoint.y(),ePoint.x()-bPoint.x(),ePoint.y()-bPoint.y()));
        QwtPainter::drawText(painter,bPoint,text);
    }

    PaintDrawElipse(QPointF xPoint,QPointF yPoint,QColor color)
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
#endif // PAINTDRAWELIPSE_H
