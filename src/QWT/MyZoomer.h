#ifndef MYZOOMER_H
#define MYZOOMER_H
#include <qwt_plot.h>
#include <qwt_plot_spectrogram.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_intervalcurve.h>
#include <QWidget>
#include "MsigmaBase.h"
#include <QPointF>
#include <QMouseEvent>
#include "AddThresholdDot.h"
class MyZoomer: public QwtPlotZoomer
{
public:
    MyZoomer(QWidget *canvas);
    MyZoomer();
    enum DrawShapeType{
        EnumDrawArrow,
        EnumDrawEllipse,
        EnumDrawBrackets,
        EnumDrawRectLine,
        EnumDrawElipseArrow,
        EnumDrawDoubleArrow,
        EnumDrawAmplitudeLine,
        EnmuDrawKeyPoint,
        EnumDrawCanle,
        EnumDrawDelte,
        EnumDrawNone,
        EnumDrawNull,   //  暂未使用
        EnumDrawText,
        EnumDrawPicture,
    };
    virtual  QwtText trackerTextF(const QPointF &pos )const
    {
        std::vector<QPointF> point;
        QColor bg( Qt::white );
        bg.setAlpha( 200 );
        //point.push_back(pos);
        if(msigmaBase)
        {
             point = msigmaBase->mouseMove(pos);
        }
        QString text = QString("%1").arg(point[0].x(),0, 'f', 1)+" " + QString( "%1" ).arg( point[0].y(), 0, 'f', 1 );
        if(point.size() > 1)
        {
            for(int i = 1;i < point.size();i++)
            {
                text += "\r\n";
                text += QString("%1").arg(point[i].x(),0, 'f', 1)+" " + QString( "%1" ).arg( point[i].y(), 0, 'f', 1 );
            }
        }
        QwtText qwttext( text );
        qwttext.setBackgroundBrush( QBrush( bg ) );
        return qwttext;
    }
    void setMsigmaBase(MsigmaBase *value);

    void widgetMousePressEvent( QMouseEvent * event);

    void widgetMouseReleaseEvent(QMouseEvent * event);

    void widgetMouseMoveEvent(QMouseEvent* event);

    void widgetMouseDoubleClickEvent( QMouseEvent * event);

    QPointF getBeginPoint();

    QPointF getEndPoint();

    void setDrawShapeType(int index);

    QPointF beginPointChange();

    QPointF endPointChange();

private:
    MsigmaBase* msigmaBase = NULL;
    QPointF beginPoint;
    QPointF endPoint;
    QPointF changeBeginPoint;
    QPointF changeEndPoint;
    int m_drawShapeType = EnumDrawNone;
};
#endif // MYZOOMER_H
