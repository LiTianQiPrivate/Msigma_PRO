#ifndef PAINTDRAWPICTURE_H
#define PAINTDRAWPICTURE_H
#include "PaintDrawBase.h"
#include<QFileDialog>

class PaintDrawPicture : public PaintDrawBase
{
public:
    void draw(QPainter *painter,const QwtScaleMap &xMap,
                      const QwtScaleMap &yMap,const QRectF &) const
    {
        const QPointF bPoint = QwtScaleMap::transform(xMap, yMap, beginPoint);
        const QPointF ePoint = QwtScaleMap::transform(xMap, yMap, endPoint);
        //QwtPainter::drawRect(painter,QRectF(bPoint.x(),bPoint.y(),ePoint.x()-bPoint.x(),ePoint.y()-bPoint.y()));
        QwtPainter::drawPixmap(painter,QRectF(bPoint.x(),bPoint.y(),ePoint.x()-bPoint.x(),ePoint.y()-bPoint.y()),image);
        //QwtPainter::drawText(painter,bPoint,text);
    }
    PaintDrawPicture(QPointF xPoint,QPointF yPoint,QColor color)
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
    void setPicture(QPixmap img)
    {
        image = img;
    }
private:
    QPointF beginPoint;
    QPointF endPoint;
    QColor _color;
    QString text;
    QPixmap image;

};
#endif // PAINTDRAWPICTURE_H
