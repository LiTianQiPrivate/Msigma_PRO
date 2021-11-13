#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>
#include <QStack>
#include "qwt_plot.h"
#include "PaintDrawRect.h"
#include "PaintDrawArrow.h"
class PaintArea : public QwtPlot
{
    Q_OBJECT

public:
    enum DrawShapeType{
        EnumDrawNone,
        EnumDrawLine,
        EnumDrawArrow,
        EnumDrawRect,
        EnumDrawEllipse,
    };

    struct None{
        QPoint beginPoint;
        QPoint endPoint;
    };

    struct Line{
        QPoint beginPoint;
        QPoint endPoint;
    };

    struct Arrow{
        QPoint beginPoint;
        QPoint endPoint;
    };

    struct Rect{
        QPoint beginPoint;
        QPoint endPoint;
    };

    struct Ellipse{
        QPoint beginPoint;
        QPoint endPoint;
    };

    explicit PaintArea(QWidget *parent = 0);
    virtual ~PaintArea();

    void setDrawShape(DrawShapeType drawShapeType);
    void setDrawShapeColor(QColor color);


    void paintNone(QPoint beginPoint, QPoint endPoint, QImage &image);
    void paintLine(QPoint beginPoint, QPoint endPoint, QImage &image);
    void paintArrow(QPoint beginPoint, QPoint endPoint);
    void paintRect(QPoint beginPoint, QPoint endPoint, QImage &image);
    void paintEllipse(QPoint beginPoint, QPoint endPoint, QImage &image);
    void paintImage(QImage &image);

    void createArrow();
    PaintDrawArrow *getLastArrow();

protected:
    void resizeEvent(QResizeEvent *e);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    QImage    m_image;
    QImage    m_tmpImage;
    QColor    m_imageBgColor;

    qreal     m_scale;
    qreal     m_angle;
    qreal     m_shear;

    bool      m_isDraw;
    bool      m_isModify;
    QPoint    m_beginPoint;
    QPoint    m_endPoint;

    DrawShapeType   m_drawShapeType;
    QColor          m_color;

    QVector<None*>          m_nones;
    QVector<Line*>          m_lines;
    QVector<Arrow*>         m_arrows;
    QVector<Rect*>          m_rects;
    QVector<Ellipse*>       m_ellipses;

    QStack<None*>           m_nonesStack;
    QStack<Line*>           m_linesStack;
    QStack<Arrow*>          m_arrowsStack;
    QStack<Rect*>           m_rectsStack;
    QStack<Ellipse*>        m_ellipsesStack;
    QStack<DrawShapeType>   m_undoStack;
    QStack<DrawShapeType>   m_redoStack;
//    PaintDrawArrow *arrow = nullptr;
    std::vector<PaintDrawArrow *> arrows;
    PaintDrawRect *m_rect = nullptr;

    QwtPlotCanvas* backgroundCurve = nullptr; // 画布

};

#endif // PAINTAREA_H
