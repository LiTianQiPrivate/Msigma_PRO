#ifndef CURVEPLOT_H
#define CURVEPLOT_H
#include "QwtPlotBase.h"
/**
 * @brief The CurvePlot class
 * 一维曲线图
 */
class CurvePlot : public  QwtPlotBase
{
    Q_OBJECT
public:
    CurvePlot(QWidget *parent = nullptr, QString className = "CurvePlot");
    ~CurvePlot();
    void resizeEvent(QResizeEvent *e);
    void setModelBases(std::vector<ModelBase*> modelObjects, int index);
    void addModelBase(ModelBase* modelObject);
    void clearModelBase();
    void showModelBase(int index);
    void hideModelBase(int index);
    bool isVisible(int index);
    void removeModelBase(int index);
    ModelBase* getModelObject(int index);
    void getPeakValue(ModelBase* modelObject);
    void on_lineStyleComboBoxActivated(int v,int index);

    void drawRibbonCruve(ModelBase *modelObject, double y1, double y2,bool v);
    void drawThresholdDotCruve(std::vector<QPointF> dot, bool v);
    void drawXRiboonCruve(ModelBase *modelObject, double x1, double x2, bool v);
    void drawXBackRiboonCruve(ModelBase *modelObject, double x1, double x2, bool v);
    std::vector<QPointF> mouseMove(QPointF m_point);
    QPointF findMinDistPoints(std::vector<Point2D>& points, Point2D p);

public:
    void on_checkBoxPointClick(bool v);
    void on_checkMinBoxPointClick(bool v);
    void on_checkMaxBoxPointClick(bool v);
    void on_checkTurnBoxPointClick(bool v);
    void on_checkCurveSelectClick(bool v);
    void on_checkManyCurveSelectClick(bool v);
private:
    std::vector<QwtPlotCurve*> curves; // 曲线
    std::vector<QwtPlotCurve*> minCurves; // 装载最小值
    std::vector<QwtPlotCurve*> maxCurves; // 装载最大值
    std::vector<QwtPlotCurve*> turnCurves; // 曲线翻转
    std::vector<QwtPlotCurve*> upRibbonCurves; // 宽色带上边界
    std::vector<QwtPlotCurve*> downRibbonCurves; // 款色带下边界
    QwtPlotCurve *thresholdDotCruve = nullptr;
    QwtPlotCurve *upCurve = nullptr;
    QwtPlotCurve *downCurve = nullptr;
    QwtPlotCurve* selectCurve = nullptr;   // 单曲线选取和多曲线选取显示曲线  单曲线时只存入一个点

    bool falgsR = false;
    bool flagThresholdDot = false;
    PaintDrawRect *paint = nullptr;
    bool flagXRibbon = false;
    PaintDrawRect *xPaint = nullptr;
    bool flagXBackRibbon =false;
    PaintDrawRect *xBackLeftPaint = nullptr;
    PaintDrawRect *xBackRightPaint = nullptr;
    bool isSingleSniff = false; //  单曲线嗅探
    bool isManySingleSniff = false;

public:
    void setAxisX(double xMin, double xMax,double xstep);
    void setAxisY(double yMin, double yMax,double ystep);
};

#endif // CURVEPLOT_H
