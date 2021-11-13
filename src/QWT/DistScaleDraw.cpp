#include "DistScaleDraw.h"
#include <QPainter>

DistScaleDraw::DistScaleDraw(QStringList labels,int orientation )
    :QwtScaleDraw()
{
    d_labels = labels;
    d_orientation = orientation;
    //设置间距、中间刻度、主刻度
    setTickLength(QwtScaleDiv::MinorTick, 0);
    setTickLength(QwtScaleDiv::MediumTick, 0);
    setTickLength(QwtScaleDiv::MajorTick, 5);

    //不显示主轴线
    enableComponent(QwtScaleDraw::Backbone, false);

}

DistScaleDraw::~DistScaleDraw()
{

}

QwtText DistScaleDraw::label(double value) const
{
    return QString::fromLocal8Bit("               ");
}

void DistScaleDraw::drawLabel(QPainter *painter, double val) const
{
        //qDebug() << val;
    QFont font = this->label(val).font();
    QRectF rect = this->labelRect(font, val);

    QString text("");
    int index = int(val);

    if (index >= 0 && index < d_labels.size())
        text = d_labels[index];
    QFontMetrics fm(font);
    int width = fm.width(text);

    //获取左边的坐标
    int x = (rect.width() - width - 13) / 2;
    QPointF point = this->labelPosition(val);
    int left = point.x() - rect.width() / 2 + x;
    if(d_orientation == 0)
    {
    //painter->drawPixmap(QPointF(left, point.y()), QPixmap(":/BarLevel.png"));
        painter->drawText(QRect(left + 13, point.y()-3, rect.width() - x - 13, rect.height()*2), Qt::AlignLeft, text);
    }
    else
    {
        painter->drawText(QRect(left, point.y()-10, rect.width() - x - 13, rect.height()*2), Qt::AlignLeft, text);
    }
}
