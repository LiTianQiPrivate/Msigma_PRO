#ifndef DISTSCALEDRAW_H
#define DISTSCALEDRAW_H

#include <QWidget>
#include "qwt_scale_draw.h"
#include "qwt_scale_div.h"

class DistScaleDraw : public QwtScaleDraw
{
//    Q_OBJECT

public:
    explicit DistScaleDraw(QStringList labels,int orientation);
    ~DistScaleDraw();
    QStringList d_labels;
    int d_orientation;
    QwtText label(double value) const;
    void drawLabel(QPainter *painter, double val) const;
};

#endif // DISTSCALEDRAW_H
