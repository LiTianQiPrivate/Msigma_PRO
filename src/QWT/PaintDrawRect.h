#ifndef PAINTDRAWRECT_H
#define PAINTDRAWRECT_H

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

class PaintDrawRect : public QwtPlotItem
{
public:
    virtual void draw(QPainter *painter,const QwtScaleMap &xMap,
                      const QwtScaleMap &yMap,const QRectF &) const
    {
        // 坐标的转换,_rect是一个逻辑坐标系下的矩形
        // rect是转换后实际物理坐标下的矩形
        const QRectF rect = QwtScaleMap::transform(xMap, yMap, _rect);
        //painter->setPen(_color);
        QBrush brush(QColor(0,255,0,100));
        {
            QwtPainter::fillRect(painter, rect,brush);
        }
    }

    PaintDrawRect(double x1,double y1,double x2,double y2,QColor color)
    {
        // 根据圆心和半径构造出圆的外接矩形
        _rect.setRect(x1,y1,x2,y2);
        _color = color;
    }
private:
    QRectF _rect;
    QColor _color;
};
#endif // PAINTDRAWRECT_H
