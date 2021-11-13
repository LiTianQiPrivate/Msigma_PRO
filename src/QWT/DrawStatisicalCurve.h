#ifndef DRAWSTATISICALCURVE_H
#define DRAWSTATISICALCURVE_H

#include <QWidget>
#include "MsigmaBase.h"
#include "ModelBase.h"
#include <qwt_plot.h>
#include <qwt_plot_spectrogram.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_intervalcurve.h>

class DrawStatisicalCurve : public QwtPlot , public MsigmaBase
{
    Q_OBJECT

public:
    explicit DrawStatisicalCurve(QWidget *parent = nullptr,QString className = "");
    ~DrawStatisicalCurve();
public:
    void resizeEvent(QResizeEvent *e);
    void setModelBases(std::vector<ModelBase*> modelObjects,int index);
    void addModelBase(ModelBase *modelObject);
    void clearModelBase();
public:
    QwtPlotCanvas* backgroundCurve = nullptr; // 画布
    QwtPlotGrid *grid = nullptr; // 网格线
    QwtPlotCurve* selectCurve = nullptr;   // 单曲线选取和多曲线选取显示曲线  单曲线时只存入一个点
    QwtPlotZoomer* zoomer = nullptr;
    QwtPlotMagnifier *magnifier = nullptr;
    QwtPlotPanner *panner = nullptr;
public:
    std::vector<QwtPlotCurve *> curves;
    PaintDrawRect *rect1 = nullptr;
    PaintDrawRect *rect2 = nullptr;
    double xMin = 9999,xMax = -9999;
    double yMin = 9999,yMax = -9999;
    void drawStatisicalAnalysis(double x1,double x2,double x3,double x4);
public:
    std::vector<double> minPoints;
    std::vector<double> maxPoints;
    std::vector<double> centrePoints;
    std::vector<double> meanPoints;
    void clearDateVluess();
    void clearRect();
    double getXMaxValue()
    {
        return xMax;
    }
    double getXMinValue()
    {
        return xMin;
    }
};

#endif // DRAWSTATISICALCURVE_H
