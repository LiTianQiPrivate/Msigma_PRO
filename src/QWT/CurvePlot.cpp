#include "CurvePlot.h"
#include <QVector>
#include "VTKGeometry.h"
#include "qwt_plot_intervalcurve.h"
#include "qwt_legend_label.h"
#include <QMessageBox>
#include <QPushButton>
#include <DialogText.h>
CurvePlot::CurvePlot(QWidget *parent, QString className):QwtPlotBase(parent,className)
{

    upCurve = new QwtPlotCurve;
    downCurve = new QwtPlotCurve;
    thresholdDotCruve = new QwtPlotCurve;
    selectCurve = new QwtPlotCurve;
}
CurvePlot::~CurvePlot()
{
    for(int i = 0; i < curves.size(); i++)
    {
        delete curves[i];
        delete minCurves[i];
        delete maxCurves[i];
        delete turnCurves[i];
    }
    delete selectCurve;
    delete upCurve;
    delete downCurve;
    delete thresholdDotCruve;
}

void CurvePlot::resizeEvent(QResizeEvent *e)
{
    QwtPlot::resizeEvent(e);
    int thisW = this->width();
    int thisH = this->height();
}

void CurvePlot::setModelBases(std::vector<ModelBase *> modelObjects, int index)
{
    clearModelBase();
    if(flagXRibbon == false)
    {
        if(xPaint)
        {
            delete xPaint;
            xPaint = NULL;
        }
    }
    if(flagThresholdDot == false)
    {
        if(thresholdDotCruve)
        {
            delete thresholdDotCruve;
            thresholdDotCruve = NULL;
        }
    }
    if(falgsR == false)
    {
        if(upCurve)
        {
            delete upCurve;
            upCurve = NULL;
        }
        if(downCurve)
        {
            delete downCurve;
            downCurve = NULL;
        }
        if(paint)
        {
            delete paint;
            paint = NULL;
        }
    }
    for(int i = 0; i < modelObjects.size(); i++)
    {
        getPeakValue(modelObjects[i]);
        setAxisScale(QwtPlot::yLeft,yMax, yMin);
        setAxisScale(QwtPlot::xBottom,xMin,xMax);
        setAxisScale(QwtPlot::yRight,yMax, yMin);
        setAxisScale(QwtPlot::xTop,xMin,xMax);
        addModelBase(modelObjects[i]);
    }
    falgsR = false;
    flagThresholdDot = false;
    flagXRibbon = false;
}

void CurvePlot::addModelBase(ModelBase *modelObject)
{
    modelBases.push_back(modelObject);
    //-----------设置x，y坐标和范围--------------//

    for(int i = 0; i < modelBases.size(); i++)
    {
        ModelBase* object = modelBases[i];
        std::vector<Point2D> points = object->getPoint2D();
        for(int j = 0; j < points.size(); j++)
        {
            Point2D p = points[j];
            double x = p.x, y = p.y;

            if(xMin > x)
            {
                xMin = x;
            }
            if(xMax < x)
            {
                xMax = x;
            }
            if(yMin > y)
            {
                yMin = y;
            }
            if(yMax < y)
            {
                yMax = y;
            }
        }
    }

    //-------------------curve------------------------//
    QwtPlotCurve *curve = new QwtPlotCurve("curve");
    curve->setTitle(modelObject->FileName());
    curve->setPen(modelObject->getColor(),penWidth);//设置曲线颜色 粗细
    curve->setRenderHint(QwtPlotItem::RenderAntialiased,true);//线条光滑化
    QVector<double> xVector, yVector;
    std::vector<Point2D> points = modelObject->getPoint2D();
    for(int j = 0; j < points.size(); j++)
    {
        Point2D p = points[j];
        xVector.push_back(p.x);
        yVector.push_back(p.y);
    }
//    curve->setStyle(QwtPlotCurve::NoCurve);
    curve->setSamples(xVector, yVector);
    curve->attach( this );
    curve->setLegendAttribute(curve->LegendShowLine);//显示图例的标志，这里显示线的颜色。
    //-----------------turnCruve--------------------------//
    QwtPlotCurve *turnCruve = new QwtPlotCurve();
    turnCruve->setPen(modelObject->getColor(),penWidth);
    turnCruve->setRenderHint(QwtPlotItem::RenderAntialiased,true);
    QVector<double> xTurnVector,yTurnVector;
    std::vector<Point2D> turnPoints = modelObject->getPoint2D();
    for(int j = 0; j < turnPoints.size(); j++)
    {
        Point2D p = points[j];
        yTurnVector.push_back(p.x);
        xTurnVector.push_back(p.y);
    }
    turnCruve->setSamples(xTurnVector, yTurnVector);
    turnCruve->attach( this );
    turnCruve->setLegendAttribute(turnCruve->LegendShowLine);//显示图例的标志，这里显示线的颜色。
    turnCruve->hide();
    //-----------------minCruve--------------------------//
    QwtPlotCurve *minCurve = new QwtPlotCurve();
    minCurve->setPen(modelObject->getColor(),penWidth);
    minCurve->setRenderHint(QwtPlotItem::RenderAntialiased,true);
    QVector<double> xMinVector,yMinVector;
    for (int i=0;i<minPoint.size();i++)
    {
        xMinVector.push_back(minPoint[i].x);
        yMinVector.push_back(minPoint[i].y);
    }
    QwtSymbol *symbol = new QwtSymbol(QwtSymbol::Triangle,
    QBrush( Qt::yellow ), QPen(minCurve->pen().color(), 2 ), QSize( 10, 10) );//设置样本点的颜色、大小
    minCurve->setSymbol(symbol);
    minCurve->setStyle(QwtPlotCurve::NoCurve);
    minCurve->setSamples(xMinVector,yMinVector);
    minCurve->attach(this);
    minCurve->setLegendAttribute(minCurve->LegendShowSymbol);
    minCurve->hide();
    //-----------------maxCruve--------------------------//
    QwtPlotCurve *maxCurve = new QwtPlotCurve();
    maxCurve->setPen(modelObject->getColor(),penWidth);
    maxCurve->setRenderHint(QwtPlotItem::RenderAntialiased,true);
    QVector<double> xMaxVector,yMaxVector;
    for (int i=0;i<maxPoint.size();i++)
    {
        xMaxVector.push_back(maxPoint[i].x);
        yMaxVector.push_back(maxPoint[i].y);
    }
    QwtSymbol *symbolm = new QwtSymbol(QwtSymbol::Hexagon,
    QBrush( Qt::red ), QPen(minCurve->pen().color(), 2 ), QSize( 10, 10) );
    maxCurve->setStyle(QwtPlotCurve::NoCurve);
    maxCurve->setSymbol(symbolm);
    maxCurve->setSamples(xMaxVector,yMaxVector);
    maxCurve->attach(this);
    maxCurve->setLegendAttribute(maxCurve->LegendShowSymbol);
    maxCurve->hide();
    //-------------------------------------------//
    this->replot();
    setAutoReplot( true );//设置自动重画，相当于更新

    curves.push_back(curve);
    minCurves.push_back(minCurve);
    maxCurves.push_back(maxCurve);
    turnCurves.push_back(turnCruve);
}

void CurvePlot::clearModelBase()
{
    modelBases.clear();
    for(int i = 0; i < curves.size(); i++)
    {
        delete curves[i];
        delete minCurves[i];
        delete maxCurves[i];
        delete turnCurves[i];
    }
    curves.clear();
    minCurves.clear();
    maxCurves.clear();
    turnCurves.clear();
}

void CurvePlot::showModelBase(int index)
{
    QwtPlotCurve* curve = curves[index];
    curve->show();
}

void CurvePlot::hideModelBase(int index)
{
    QwtPlotCurve* curve = curves[index];
    curve->hide();
}

bool CurvePlot::isVisible(int index)
{
    QwtPlotCurve* curve = curves[index];
    return curve->isVisible();
}

void CurvePlot::removeModelBase(int index)
{
    if(curves.size() > index)
    {
        QwtPlotCurve* curve = curves[index];
        delete curve;
        curve = minCurves[index];
        delete curve;
        curve = maxCurves[index];
        delete curve;
        curve = turnCurves[index];
        delete curve;
        curves.erase(curves.begin() + index);
        minCurves.erase(minCurves.begin() + index);
        maxCurves.erase(maxCurves.begin() + index);
        turnCurves.erase(turnCurves.begin() + index);
        modelBases.erase(modelBases.begin() + index);
    }

}

ModelBase *CurvePlot::getModelObject(int index)
{
    return modelBases[index];
}

void CurvePlot::getPeakValue(ModelBase *modelObject)
{
    //for(int i = 0; i < modelBases.size(); i++)
    {
        ModelBase* object = modelObject;
        std::vector<Point2D> points = object->getPoint2D();
        for(int j = 0; j < points.size(); j++)
        {
            Point2D p = points[j];
            double x = p.x, y = p.y;
            double y1 = points[0].y;
            if(xMin > x)
            {
                xMin = x;
            }
            if(xMax < x)
            {
                xMax = x;
            }
            if(yMin > y)
            {
                yMin = y;
            }
            if(yMax < y)
            {
                yMax = y;
            }
            if(j == 0)
            {
                if(y1 < points[1].y)
                {
                    maxPoint.push_back(points[0]);
                }
                else
                {
                    minPoint.push_back(points[0]);
                }
            }
            else if(j>0 && j<points.size())
            {
                Point2D p1 = points[j+1];
                Point2D p2 = points[j-1];
                if(y > p2.y && y > p1.y)
                {
                    minPoint.push_back(points[j]);
                }
                else if(y < p1.y && y<p2.y)
                {
                    maxPoint.push_back(points[j]);
                }
            }
            else if(j == (points.size()-1))
            {
                if(y < points[j-1].y)
                {
                    maxPoint.push_back(points[j]);
                }
                else
                {
                    minPoint.push_back(points[j]);
                }
            }
        }
    }
}

void CurvePlot::on_checkBoxPointClick(bool v)
{
    std::vector<QwtSymbol::Style> symbolType;
    symbolType.push_back(QwtSymbol::Ellipse);
    symbolType.push_back(QwtSymbol::Rect);
    symbolType.push_back(QwtSymbol::Diamond);
    symbolType.push_back(QwtSymbol::Triangle);
    symbolType.push_back(QwtSymbol::Cross);
    symbolType.push_back(QwtSymbol::Hexagon);
    if(v)
    {
        int currentIndex = 0;
        for(int i = 0; i < curves.size(); i++)
        {
            QwtPlotCurve* curve = curves[i];
            QwtSymbol *symbol = new QwtSymbol(symbolType[currentIndex],
            QBrush( Qt::yellow ), QPen(curve->pen().color(), 2 ), QSize( 6, 6) );//设置样本点的颜色、大小
            curve->setSymbol(symbol);
            if(currentIndex > 5)
            {
                currentIndex = 0;
            }
            currentIndex++;
        }
    } else {
        for(int i = 0; i < curves.size(); i++)
        {
            QwtPlotCurve* curve = curves[i];
            curve->setSymbol(NULL);//添加样本点形状
        }
    }
}

void CurvePlot::on_lineStyleComboBoxActivated(int v, int index)
{
    //for(int i = 0; i < curves.size(); i++)
    {
        QwtPlotCurve* curve = curves[index];
        if(v == 0)
        {
            curve->setStyle(QwtPlotCurve::Lines);

        } else if(v == 1){
            curve->setStyle(QwtPlotCurve::Dots);
        } else if(v == 2){
            curve->setStyle(QwtPlotCurve::Sticks);
        }  else if(v == 3){
            curve->setStyle(QwtPlotCurve::Steps);
        }  else if(v == 4){
            curve->setStyle(QwtPlotCurve::NoCurve);
        }
    }

}

void CurvePlot::on_checkMinBoxPointClick(bool v)
{
    if(v)
    {
        for(int i = 0;i<minCurves.size();i++)
        {
            minCurves[i]->show();
        }
    }
    else
    {
        for(int i = 0;i<minCurves.size();i++)
        {
            minCurves[i]->hide();
        }
    }
}

void CurvePlot::on_checkMaxBoxPointClick(bool v)
{
    if(v)
    {
        for(int i = 0;i<maxCurves.size();i++)
        {
            maxCurves[i]->show();
        }
    }
    else
    {
        for(int i = 0;i<maxCurves.size();i++)
        {
            maxCurves[i]->hide();
        }
    }
}

void CurvePlot::on_checkTurnBoxPointClick(bool v)
{
    // 曲线翻转 x轴与y轴翻转显示
    if(v)
    {
        setAxisTitle(QwtPlot::yLeft, "X" );
        setAxisTitle(QwtPlot::xBottom, "Y" );
        setAxisScale(QwtPlot::yLeft,xMin,xMax);
        setAxisScale(QwtPlot::xBottom,yMin,yMax);
        setAxisScale(QwtPlot::yRight,xMin,xMax);
        setAxisScale(QwtPlot::xTop,yMin,yMax);
        this->replot();
        setAutoReplot( true );//设置自动重画，相当于更新
        for (int i = 0;i<turnCurves.size();i++)
        {
            curves[i]->hide();
            minCurves[i]->hide();
            maxCurves[i]->hide();
            turnCurves[i]->show();
        }
    }
    else
    {
        setAxisTitle(QwtPlot::yLeft, "Y" );
        setAxisTitle(QwtPlot::xBottom, "X" );
        setAxisScale(QwtPlot::yLeft,yMax,yMin);
        setAxisScale(QwtPlot::xBottom,xMin,xMax);
        setAxisScale(QwtPlot::yRight,yMax, yMin);
        setAxisScale(QwtPlot::xTop,xMin,xMax);
        this->replot();
        setAutoReplot( true );//设置自动重画，相当于更新
        for (int i = 0;i<turnCurves.size();i++)
        {
            turnCurves[i]->hide();
            minCurves[i]->hide();
            maxCurves[i]->hide();
            curves[i]->show();
        }
    }
}

void CurvePlot::on_checkCurveSelectClick(bool v)
{

    if(v)
    {
        isSingleSniff = true;
    }
    else
    {
        isSingleSniff = false;
    }
}

void CurvePlot::on_checkManyCurveSelectClick(bool v)
{
    if(v)
    {
        isManySingleSniff = true;
    }
    else
    {
        isManySingleSniff = false;
    }
}

void CurvePlot::drawRibbonCruve(ModelBase* modelObject, double y1, double y2, bool v)
{
    // 在setModelBase时已经判断 此处增加与否不影响效果
    if(v == false)
    {
        if(upCurve)
        {
            delete upCurve;
            upCurve = NULL;
        }
        if(downCurve)
        {
            delete downCurve;
            downCurve = NULL;
        }
        if(paint)
        {
            delete paint;
            paint = NULL;
        }
        return;
    }
    falgsR = true;
    std::vector<Point2D> points = modelObject->getPoint2D();
    for(int j = 0; j < points.size(); j++)
    {
        Point2D p = points[j];
        double x = p.x, y = p.y;
        double y1 = points[0].y;
        if(xMin > x)
        {
            xMin = x;
        }
        if(xMax < x)
        {
            xMax = x;
        }
        if(yMin > y)
        {
            yMin = y;
        }
        if(yMax < y)
        {
            yMax = y;
        }
    }
    setAxisScale(QwtPlot::yLeft,yMax, yMin);
    setAxisScale(QwtPlot::xBottom,xMin,xMax);
    setAxisScale(QwtPlot::yRight,yMax, yMin);
    setAxisScale(QwtPlot::xTop,xMin,xMax);
    //-------------------upcurve------------------------//
    if(upCurve)
    {
        delete upCurve;
        upCurve = NULL;
    }
    upCurve = new QwtPlotCurve();
    upCurve->setTitle(modelObject->FileName());

    upCurve->setRenderHint(QwtPlotItem::RenderAntialiased,true);//线条光滑化
    QVector<double> xVector, yVector;
    for(int j = 0; j < points.size(); j++)
    {
        Point2D p = points[j];
        xVector.push_back(p.x);
        yVector.push_back(y1);
    }
    upCurve->setSamples(xVector, yVector);
    upCurve->attach( this );
    upCurve->setLegendAttribute(upCurve->LegendShowLine);//显示图例的标志，这里显示线的颜色。
    //-------------------downcurve------------------------//
    if(downCurve)
    {
        delete downCurve;
        downCurve = NULL;
    }
    downCurve = new QwtPlotCurve();
    downCurve->setTitle(modelObject->FileName());
    downCurve->setPen(modelObject->getColor(),penWidth);//设置曲线颜色 粗细
    downCurve->setRenderHint(QwtPlotItem::RenderAntialiased,true);//线条光滑化
    QVector<double> x1Vector, y1Vector;
    for(int j = 0; j < points.size(); j++)
    {
        Point2D p = points[j];
        x1Vector.push_back(p.x);
        y1Vector.push_back(y2);
    }
    downCurve->setSamples(x1Vector, y1Vector);
    downCurve->attach( this );
    downCurve->setLegendAttribute(downCurve->LegendShowLine);//显示图例的标志，这里显示线的颜色。
    if(paint)
    {
        delete paint;
        paint = NULL;
    }
    paint = new PaintDrawRect(xMin,y2,fabs(xMax-xMin),fabs(y2-y1),Qt::blue);
    paint->setRenderHint(QwtPlotItem::RenderAntialiased);
    paint->attach(this);
    if(fabs(y1) < 0.001 && fabs(y2) > 0.001)
    {
        downCurve->show();
        downCurve->setPen(modelObject->getColor(),penWidth);//设置曲线颜色 粗细
        upCurve->hide();
        paint->hide();
    }
    else if(fabs(y2) < 0.001 && fabs(y1) > 0.001)
    {
        upCurve->show();
        upCurve->setPen(modelObject->getColor(),penWidth);//设置曲线颜色 粗细
        downCurve->hide();
        paint->hide();
    }
    else if(fabs(y1) > 0.001 && fabs(y2) > 0.001)
    {
        upCurve->hide();
        downCurve->hide();
        paint->show();
    }
    else
    {
        upCurve->hide();
        downCurve->hide();
        paint->hide();
    }
}

void CurvePlot::drawThresholdDotCruve(std::vector<QPointF> dot,bool v)
{
    if(v == false)
    {
        if(thresholdDotCruve)
        {
            thresholdDotCruve->hide();
            delete thresholdDotCruve;
            thresholdDotCruve = NULL;
        }
        return ;
    }
    flagThresholdDot = true;
    QVector<double> xVector, yVector;
    for (int i = 0;i<dot.size();i++)
    {
        xVector.push_back(dot[i].x());
        yVector.push_back(dot[i].y());
    }
    if(thresholdDotCruve)
    {
        delete thresholdDotCruve;
        thresholdDotCruve = NULL;
    }
    thresholdDotCruve = new QwtPlotCurve;

    thresholdDotCruve->setPen(Qt::green,penWidth,Qt::DotLine);//设置曲线颜色 粗细
    QwtSymbol *symbol = new QwtSymbol(QwtSymbol::Rect,
    QBrush( Qt::yellow ), QPen(thresholdDotCruve->pen().color(), penWidth ), QSize( 50, 20) );
    thresholdDotCruve->setSymbol(symbol);
    thresholdDotCruve->setRenderHint(QwtPlotItem::RenderAntialiased,true);//线条光滑化
    thresholdDotCruve->setSamples(xVector,yVector);
    thresholdDotCruve->attach( this );
    thresholdDotCruve->setLegendAttribute(thresholdDotCruve->LegendShowLine);//显示图例的标志，这里显示线的颜色。
}

void CurvePlot::drawXRiboonCruve(ModelBase *modelObject, double x1, double x2, bool v)
{
    if(v == false)
    {
        if(xPaint)
        {
            xPaint->hide();
            delete xPaint;
            xPaint = NULL;
        }
        return ;
    }
    flagXRibbon = true;
    std::vector<Point2D> points = modelObject->getPoint2D();
    for(int j = 0; j < points.size(); j++)
    {
        Point2D p = points[j];
        double x = p.x, y = p.y;
        double y1 = points[0].y;
        if(xMin > x)
        {
            xMin = x;
        }
        if(xMax < x)
        {
            xMax = x;
        }
        if(yMin > y)
        {
            yMin = y;
        }
        if(yMax < y)
        {
            yMax = y;
        }
    }
    qDebug() << "x1 ==" << x1;
    setAxisScale(QwtPlot::yLeft,yMax, yMin);
    setAxisScale(QwtPlot::xBottom,xMin,xMax);
    setAxisScale(QwtPlot::yRight,yMax, yMin);
    setAxisScale(QwtPlot::xTop,xMin,xMax);
    if(xPaint)
    {
        delete xPaint;
        xPaint = NULL;
    }
    xPaint = new PaintDrawRect(x1,yMin,fabs(x2-x1),fabs(yMax-yMin),Qt::blue);
    xPaint->setRenderHint(QwtPlotItem::RenderAntialiased);
    xPaint->attach(this);
}

void CurvePlot::drawXBackRiboonCruve(ModelBase *modelObject, double x1, double x2, bool v)
{
    if(v == false)
    {
        if(xBackLeftPaint)
        {
            xBackLeftPaint->hide();
            delete xBackLeftPaint;
            xBackLeftPaint = NULL;
        }
        if(xBackRightPaint)
        {
            xBackRightPaint->hide();
            delete xBackRightPaint;
            xBackRightPaint = NULL;
        }
        return ;
    }
    flagXBackRibbon = true;
    std::vector<Point2D> points = modelObject->getPoint2D();
    for(int j = 0; j < points.size(); j++)
    {
        Point2D p = points[j];
        double x = p.x, y = p.y;
        double y1 = points[0].y;
        if(xMin > x)
        {
            xMin = x;
        }
        if(xMax < x)
        {
            xMax = x;
        }
        if(yMin > y)
        {
            yMin = y;
        }
        if(yMax < y)
        {
            yMax = y;
        }
    }
    qDebug() << "x1 ==" << x1;
    setAxisScale(QwtPlot::yLeft,yMax, yMin);
    setAxisScale(QwtPlot::xBottom,xMin,xMax);
    if(xBackLeftPaint)
    {
        xBackLeftPaint->hide();
        delete xBackLeftPaint;
        xBackLeftPaint = NULL;
    }
    if(xBackRightPaint)
    {
        xBackRightPaint->hide();
        delete xBackRightPaint;
        xBackRightPaint = NULL;
    }
    xBackLeftPaint = new PaintDrawRect(xMin,yMin,fabs(x1-xMin),fabs(yMax-yMin),Qt::blue);
    xBackLeftPaint->setRenderHint(QwtPlotItem::RenderAntialiased);
    xBackLeftPaint->attach(this);
    xBackRightPaint = new PaintDrawRect(x2,yMin,fabs(xMax-x2),fabs(yMax-yMin),Qt::blue);
    xBackRightPaint->setRenderHint(QwtPlotItem::RenderAntialiased);
    xBackRightPaint->attach(this);
}

std::vector<QPointF> CurvePlot::mouseMove(QPointF m_point)
{
    std::vector<QPointF> pointTab;
    if(selectCurve)
    {
        selectCurve->hide();
        delete selectCurve;
        selectCurve = NULL;
    }
    if(isSingleSniff)
    { 

        std::vector<Point2D> points;
        for(int i=0;i<modelBases.size();i++)
        {
            // 单曲线选取将所有modelbase添加进去 进行统一比较
            ModelBase* object = modelBases[i];
            std::vector<Point2D> pointi = object->getPoint2D();
            for(int j=0;j<pointi.size();j++)
            {
                points.push_back(pointi[j]);
            }
        }
        QPointF num = findMinDistPoints(points, Point2D(m_point.x(), m_point.y()));
        pointTab.push_back(num);
        QVector<double> xVector, yVector;
        xVector.push_back(pointTab[0].x());
        yVector.push_back(pointTab[0].y());
        selectCurve = new QwtPlotCurve;
        QwtSymbol *symbol = new QwtSymbol(QwtSymbol::Ellipse, QBrush( Qt::yellow ), QPen( Qt::lightGray, 2 ), QSize( 12, 12 ));
        selectCurve->setSymbol(symbol);
        selectCurve->setStyle(QwtPlotCurve::Dots);
        selectCurve->setRenderHint(QwtPlotItem::RenderAntialiased,true);//线条光滑化
        selectCurve->setSamples(xVector,yVector);
        selectCurve->attach( this );
        selectCurve->setLegendAttribute(thresholdDotCruve->LegendShowLine);//显示图例的标志，这里显示线的颜色。
        return pointTab;
    }
    else if(isManySingleSniff)
    {
        QVector<double> xVector, yVector;
        for(int i=0;i<modelBases.size();i++)
        {
            ModelBase* object = modelBases[i];
            std::vector<Point2D> points = object->getPoint2D();
            QPointF num = findMinDistPoints(points, Point2D(m_point.x(), m_point.y()));
            pointTab.push_back(num);
            xVector.push_back(num.x());
            yVector.push_back(num.y());
        }
        selectCurve = new QwtPlotCurve;
        QwtSymbol *symbol = new QwtSymbol(QwtSymbol::Ellipse, QBrush( Qt::yellow ), QPen( Qt::lightGray, 2 ), QSize( 12, 12 ));
        selectCurve->setSymbol(symbol);
        selectCurve->setStyle(QwtPlotCurve::Dots);
        selectCurve->setRenderHint(QwtPlotItem::RenderAntialiased,true);//线条光滑化
        selectCurve->setSamples(xVector,yVector);
        selectCurve->attach( this );
        selectCurve->setLegendAttribute(thresholdDotCruve->LegendShowLine);//显示图例的标志，这里显示线的颜色
        return pointTab;
    }
    else
    {
        pointTab.push_back(m_point);
        return pointTab;
    }
}

QPointF CurvePlot::findMinDistPoints(std::vector<Point2D> &points, Point2D p)
{
    double dist = 1000000;
    QPointF outP(0, 0);
    for(int  i = 0; i < points.size(); i++)
    {
        Point2D& theP = points[i];
        double d = point3Distance(theP, p);
        if(dist > d)
        {
            dist = d;
            outP.setX(theP.x);
            outP.setY(theP.y);
        }
    }
    return outP;
}

void CurvePlot::setAxisX(double xmin, double xmax, double xstep)
{
    if(xmin > xMin && xmax < xMax && xmax > xMin && xmax < xMax)
    {
        setAxisScale(QwtPlot::xBottom,xmin,xmax,xstep);
        setAxisScale(QwtPlot::xTop,xmin,xmax,xstep);
    }
}

void CurvePlot::setAxisY(double ymin, double ymax, double ystep)
{
    if(ymin > yMin && ymax < yMax && ymax > yMin && ymax < yMax)
    {
        setAxisScale(QwtPlot::yLeft,ymax, ymin,ystep);
        setAxisScale(QwtPlot::yRight,ymax, ymin,ystep);
    }
}

