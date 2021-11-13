#ifndef QWTPLOTBASE_H
#define QWTPLOTBASE_H

#include <QWidget>
#include "ModelRAM.h"
#include "ModelRCS.h"
#include "ModelRCSF.h"
#include "MsigmaBase.h"
#include "QCheckBox"
#include "QComboBox"
#include "MyZoomer.h"

class QwtPlotBase : public QwtPlot , public MsigmaBase
{
    Q_OBJECT

public:
    explicit QwtPlotBase(QWidget *parent = nullptr,QString className = "");
    ~QwtPlotBase();
public:
    QVector<QwtPlotIntervalCurve *>intervalCurves;
    QwtPlotCanvas* backgroundCurve = nullptr; // 画布
    QwtPlotGrid *grid = nullptr; // 网格线
    QwtPlotCurve* selectCurve = nullptr;   // 单曲线选取和多曲线选取显示曲线  单曲线时只存入一个点
    QwtPlotZoomer* zoomer = nullptr;
    QwtPlotMagnifier *magnifier = nullptr;
    QwtPlotPanner *panner = nullptr;
    MyZoomer* picker = nullptr;
public:
    void paintArrow(QPointF beginPoint, QPointF endPoint);
    void createArrow(QPointF beginPoint, QPointF endPoint);
public:
    void paintRectLine(QPointF beginPoint, QPointF endPoint);
    void createRectLine(QPointF beginPoint, QPointF endPoint);
public:
    void paintElipse(QPointF beginPoint, QPointF endPoint);
    void createElipse(QPointF beginPoint, QPointF endPoint);
public:
    void paintBracket(QPointF beginPoint, QPointF endPoint);
    void createBracket(QPointF beginPoint, QPointF endPoint);
public:
    void paintElipseArrow(QPointF beginPoint, QPointF endPoint);
    void createElipseArrow(QPointF beginPoint, QPointF endPoint);
public:
    void paintDoubleArrow(QPointF beginPoint, QPointF endPoint);
    void createDoubleArrow(QPointF beginPoint, QPointF endPoint);
public:
    void paintPaintDrawDoubleMouse(QPointF beginPoint, QPointF endPoint);
    void createPaintDrawDoubleMouse(QPointF beginPoint, QPointF endPoint);
public:
    void paintPicture(QPointF beginPoint, QPointF endPoint);
    void createPicture(QPointF beginPoint, QPointF endPoint);
public:
    std::vector<Point2D > minPoint;
    std::vector<Point2D > maxPoint;
    void paintAmplitudeLine(QPointF beginPoint, QPointF endPoint);
    void createAmplitudeLine(QPointF beginPoint, QPointF endPoint);
public:
    void paintKeyPoint(QPointF beginPoint, QPointF endPoint);
    void createKeyPoint(QPointF beginPoint, QPointF endPoint);
    bool drawLineFlag = false;
public:
    std::vector<PaintDrawBase *> drawBases;
    PaintDrawBase *drawBase = nullptr;
    PaintDrawBase *getLastDrawBase();
    void getStandIndex(int index);
    void setInputText(QString str);
    void setGridState(bool v);
    void setBackGroupLightDark(int index);
public:
    double xMin = 10000000, xMax = -10000000;
    double yMin = 10000000, yMax = -10000000;
public:
    int setPenWidth(int width)
    {
        penWidth = width;
        return penWidth;
    }
    int penWidth = 1;

};

#endif // QWTPLOTBASE_H
