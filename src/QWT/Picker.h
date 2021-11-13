#ifndef PICKER_H
#define PICKER_H

#endif // PICKER_H
#include "qwt_plot_picker.h"
#include <QCursor>


class Picker: public QwtPlotPicker
{
public:
    Picker( QWidget *canvas ):QwtPlotPicker( canvas )
    {
    }
public:
    virtual QwtText trackerTextF( const QPointF &pos ) const
    {
//        QCursor::setPos(0, 0);
        QString text;
        text += QString("%1").arg(pos.x(),0, 'f', 1)+" " + QString( "%1" ).arg( pos.y(), 0, 'f', 1 );
        QwtText qwttext( text );
        return qwttext;
    }
};
