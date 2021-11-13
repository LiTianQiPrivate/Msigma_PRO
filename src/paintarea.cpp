#include <QtWidgets>
#include "paintarea.h"
#include "qwt_painter.h"
#include <QPolygonF>
PaintArea::PaintArea(QWidget *parent)
    : QwtPlot(parent)
{
    //---------设置画布---------//
    backgroundCurve=new QwtPlotCanvas();
    backgroundCurve->setPalette(Qt::white);
    backgroundCurve->setBorderRadius(10);
    setCanvas( backgroundCurve );
    plotLayout()->setAlignCanvasToScales( true );
    setAxisTitle(QwtPlot::yLeft, "Y" );
    setAxisTitle(QwtPlot::xBottom, "X" );

    m_isModify=false;
    m_beginPoint = QPoint(0, 0);
    m_endPoint = QPoint(0, 0);
//    createArrow();
//    m_drawShapeType = EnumDrawNone;
}

PaintArea::~PaintArea()
{
    delete backgroundCurve;
    qDeleteAll(m_nones);
    qDeleteAll(m_lines);
    qDeleteAll(m_arrows);
    qDeleteAll(m_rects);
    qDeleteAll(m_ellipses);

    qDeleteAll(m_nonesStack);
    qDeleteAll(m_linesStack);
    qDeleteAll(m_arrowsStack);
    qDeleteAll(m_rectsStack);
    qDeleteAll(m_ellipsesStack);
    qDeleteAll(arrows);
    //        for(int i = 0; i < drawBases.size(); i++)
    //        {
    //            if()
    //            {

    //                this->removeItem(drawBases[i]);
    //                delete drawBases[i];
    //                drawBases.erase(drawBases.begin() + i);
    //                break;
    //            }
    //        }
//    m_undoStack.clear();
//    m_redoStack.clear();
}

void PaintArea::setDrawShape(DrawShapeType drawShapeType)
{
    m_drawShapeType = drawShapeType;
}

void PaintArea::setDrawShapeColor(QColor color)
{
    m_color = color;
}

void PaintArea::paintNone(QPoint beginPoint, QPoint endPoint, QImage &image)
{
    QPainter paint(&image);
    paint.setRenderHint(QPainter::Antialiasing, true);
    paint.setPen(QPen(m_color, 1, Qt::SolidLine, Qt::FlatCap));
    paint.setBrush(QBrush(m_color));

    paint.drawLine(beginPoint / m_scale, endPoint / m_scale);

    m_isModify = true;
}

void PaintArea::paintLine(QPoint beginPoint, QPoint endPoint, QImage &image)
{
    QPainter paint(&image);
    paint.setRenderHint(QPainter::Antialiasing, true);
    paint.setPen(QPen(m_color, 1, Qt::SolidLine, Qt::FlatCap));
    paint.setBrush(QBrush(m_color));

    paint.drawLine(beginPoint / m_scale, endPoint / m_scale);

    m_isModify = true;
}

void PaintArea::paintArrow(QPoint beginPoint, QPoint endPoint)
{
    double par = 10.0;  //箭头部分三角形的腰长
    double slopy = atan2((endPoint.y() / m_scale - beginPoint.y() / m_scale), (endPoint.x() / m_scale - beginPoint.x() / m_scale));
    double cosy = cos(slopy);
    double siny = sin(slopy);
    QPointF point1 = QPointF(endPoint.x() / m_scale + int(-par*cosy - (par / 2.0*siny)), endPoint.y() / m_scale + int(-par*siny + (par / 2.0*cosy)));
    QPointF point2 = QPointF(endPoint.x() / m_scale + int(-par*cosy + (par / 2.0*siny)), endPoint.y() / m_scale - int(par / 2.0*cosy + par*siny));
    int offsetX = int(par*siny / 3);
    int offsetY = int(par*cosy / 3);
    QPointF point3, point4;
    point3 = QPointF(endPoint.x() / m_scale + int(-par*cosy - (par / 2.0*siny)) + offsetX, endPoint.y() / m_scale + int(-par*siny + (par / 2.0*cosy)) - offsetY);
    point4 = QPointF(endPoint.x() / m_scale + int(-par*cosy + (par / 2.0*siny) - offsetX), endPoint.y() / m_scale - int(par / 2.0*cosy + par*siny) + offsetY);
}

void PaintArea::paintRect(QPoint beginPoint, QPoint endPoint, QImage &image)
{
    QPainter paint(&image);
    paint.setPen(QPen(m_color, 1, Qt::SolidLine, Qt::FlatCap));

    int x, y, w, h;
    x = beginPoint.x() / m_scale;
    y = beginPoint.y() / m_scale;
    w = endPoint.x() / m_scale - x;
    h = endPoint.y() / m_scale - y;
    m_rect = new PaintDrawRect(x,y,w,h,Qt::black);
    m_rect->setRenderHint(QwtPlotItem::RenderAntialiased);
    m_rect->attach(this);
    //paint.drawRect(x, y, w, h);
    m_isModify = true;
}

void PaintArea::paintEllipse(QPoint beginPoint, QPoint endPoint, QImage &image)
{
    QPainter paint(&image);
    paint.setRenderHint(QPainter::Antialiasing, true);
    paint.setPen(QPen(m_color, 1, Qt::SolidLine, Qt::FlatCap));

    int x, y, w, h;
    x = beginPoint.x() / m_scale;
    y = beginPoint.y() / m_scale;
    w = endPoint.x() / m_scale - x;
    h = endPoint.y() / m_scale - y;

    paint.drawEllipse(x, y, w, h);

    m_isModify = true;
}

void PaintArea::paintImage(QImage &image)
{
    if (m_drawShapeType == EnumDrawNone) {
        paintNone(m_beginPoint, m_endPoint, image);
        m_beginPoint = m_endPoint;
    }
    else if (m_drawShapeType == EnumDrawLine) {
        paintLine(m_beginPoint, m_endPoint, image);
    }
    else if (m_drawShapeType == EnumDrawArrow) {
//        paintArrow(m_beginPoint, m_endPoint, image);
    }
    else if (m_drawShapeType == EnumDrawRect) {
        paintRect(m_beginPoint, m_endPoint, image);
    }
    else if (m_drawShapeType == EnumDrawEllipse) {
        paintEllipse(m_beginPoint, m_endPoint, image);
    }

    update();
}

void PaintArea::createArrow()
{

}

PaintDrawArrow *PaintArea::getLastArrow()
{
    if(arrows.size() > 0)
    {
        return arrows[arrows.size() - 1];
    }
    return NULL;
}

void PaintArea::resizeEvent(QResizeEvent *e)
{
    QwtPlot::resizeEvent(e);
}

void PaintArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_beginPoint = event->pos();
        m_isDraw = true;
    }
}

void PaintArea::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        m_endPoint = event->pos();
        paintArrow(m_beginPoint, m_endPoint);
    }
}

void PaintArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_endPoint = event->pos();
        m_isDraw = false;
        if (m_drawShapeType == EnumDrawNone) {
            None *none = new None;
            none->beginPoint = QPoint(0, 0);
            none->endPoint = QPoint(0, 0);
            m_nones.push_back(none);
            m_undoStack.push_back(EnumDrawNone);
        }
        else if (m_drawShapeType == EnumDrawLine) {
            Line *line = new Line;
            line->beginPoint = m_beginPoint;
            line->endPoint = m_endPoint;

            m_lines.push_back(line);
            m_undoStack.push_back(EnumDrawLine);
        }
        else if (m_drawShapeType == EnumDrawArrow) {
            Arrow *arrow = new Arrow;
            arrow->beginPoint = m_beginPoint;
            arrow->endPoint = m_endPoint;
            this->createArrow();
            m_arrows.push_back(arrow);
            m_undoStack.push_back(EnumDrawArrow);
        }
        else if (m_drawShapeType == EnumDrawRect) {
            Rect *rect = new Rect;
            rect->beginPoint = m_beginPoint;
            rect->endPoint = m_endPoint;
            m_rects.push_back(rect);
            m_undoStack.push_back(EnumDrawRect);
        }
        else if (m_drawShapeType == EnumDrawEllipse) {
            Ellipse *ellipse = new Ellipse;
            ellipse->beginPoint = m_beginPoint;
            ellipse->endPoint = m_endPoint;
            m_ellipses.push_back(ellipse);
            m_undoStack.push_back(EnumDrawEllipse);
        }

        paintImage(m_image);
    }
}
