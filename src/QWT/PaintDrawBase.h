#ifndef PAINTDRAWBASE_H
#define PAINTDRAWBASE_H
#define QWT_DLL
#include<qwt_plot.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_renderer.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_histogram.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_magnifier.h>
#include <qwt_legend.h>
#include <qwt_legend_label.h>
#include <qwt_column_symbol.h>
#include <qwt_series_data.h>
#include <qpen.h>
#include <qwt_symbol.h>
#include <qwt_picker_machine.h>
#include <qwt_painter.h>
#include <qwt_scale_map.h>
#include "QPointF"
#include "QColor"

class PaintDrawBase: public QwtPlotItem
{

public:
    virtual void draw(QPainter *painter,const QwtScaleMap &xMap,
                      const QwtScaleMap &yMap,const QRectF &) const
    {

    }
    virtual void setInputText(QString str){ };
    //PaintDrawBase(QPointF xPoint = QPointF(0,0),QPointF yPoint = QPointF(0,0),QColor color = Qt::blue);
    virtual void setPoint(QPointF xPoint,QPointF yPoint){}
    virtual void setXPoint(QPointF xPoint,bool flag = false){}  // 画关键点使用
    virtual void setPicture(QPixmap img){}  //  加载图片
    virtual double getSlopy(QPointF bPoint,QPointF ePoint)
    {
        double x1 = bPoint.x();
        double y1 = bPoint.y();
        double x2 = ePoint.x();
        double y2 = ePoint.y();
        double slopy;
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
        return slopy;
    }
    int getFontWidth(QPainter *painter,QString text)
    {
        QFont wordfont = painter->font();
        QFontMetrics fm(wordfont);
        QRect rec = fm.boundingRect( text);
        int ii = rec.width();//这个就获得了字符串所占的像素宽度
        return ii;
    }
};
#endif // PAINTDRAWBASE_H
