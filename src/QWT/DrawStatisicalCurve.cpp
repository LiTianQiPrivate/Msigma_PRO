#include "DrawStatisicalCurve.h"
#include "Point2D.h"
#include "PaintDrawRect.h"
#include "Business.h"
#include "DateCountTabWidget.h"

DrawStatisicalCurve::DrawStatisicalCurve(QWidget *parent,QString className) :
    QwtPlot(parent),MsigmaBase(className)
{
    setAutoFillBackground(true);
    //---------设置画布---------//
    backgroundCurve=new QwtPlotCanvas();
    backgroundCurve->setPalette(Qt::white);
    backgroundCurve->setBorderRadius(10);
    setCanvas( backgroundCurve );
    plotLayout()->setAlignCanvasToScales( true );

    setAxisTitle(QwtPlot::yLeft, "RCS(dBsm)" );
    QString ss = QString::fromLocal8Bit("方位角(°)");
    setAxisTitle(QwtPlot::xBottom, ss);
    //----------------设置栅格线-------------------//
    grid = new QwtPlotGrid;
    grid->enableX( true );//设置网格线
    grid->enableY( true );
    grid->setMajorPen( Qt::black, 0, Qt::DotLine );
    grid->attach( this );
//    magnifier = new QwtPlotMagnifier( canvas() );
//    magnifier->setAxisEnabled( QwtPlot::yRight, false );
    setAutoReplot( true );
}
DrawStatisicalCurve::~DrawStatisicalCurve()
{
    delete panner;
    delete magnifier;
    delete zoomer;
    delete grid;
    delete backgroundCurve;
}

void DrawStatisicalCurve::resizeEvent(QResizeEvent *e)
{
    QwtPlot::resizeEvent(e);
    int thisW = this->width();
    int thisH = this->height();
}

void DrawStatisicalCurve::setModelBases(std::vector<ModelBase *> modelObjects, int index)
{
    clearModelBase();
    for(int i = 0; i < modelObjects.size(); i++)
    {
        addModelBase(modelObjects[i]);
    }
}

void DrawStatisicalCurve::addModelBase(ModelBase *modelObject)
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
    setAxisScale(QwtPlot::yLeft,yMin, yMax);
    setAxisScale(QwtPlot::xBottom,xMin,xMax);
    QwtPlotCurve *curve = new QwtPlotCurve("curve");
    curve->setTitle(modelObject->FileName());
    curve->setPen(modelObject->getColor());//设置曲线颜色 粗细
    curve->setRenderHint(QwtPlotItem::RenderAntialiased,true);//线条光滑化
    QVector<double> xVector, yVector;
    std::vector<Point2D> points = modelObject->getPoint2D();
    for(int j = 0; j < points.size(); j++)
    {
        Point2D p = points[j];
        xVector.push_back(p.x);
        yVector.push_back(p.y);
    }
    curve->setSamples(xVector, yVector);
    curve->attach( this );
    curve->setLegendAttribute(curve->LegendShowLine);//显示图例的标志，这里显示线的颜色。
    curves.push_back(curve);
    this->replot();
    setAutoReplot( true );//设置自动重画，相当于更新
}

void DrawStatisicalCurve::clearModelBase()
{
    modelBases.clear();
    for(int i = 0; i < curves.size(); i++)
    {
        delete curves[i];
    }
    curves.clear();
}

void DrawStatisicalCurve::drawStatisicalAnalysis(double x1, double x2, double x3, double x4)
{
    if(rect1)
    {
        delete rect1;
        rect1 = NULL;
    }
    if(rect2)
    {
        delete rect2;
        rect2 = NULL;
    }

    int number = 0;
    double yMean = 0.0;
    double maxY = -999;
    double minY = 999;
    double centreY = 0.0;
    //  此条件下需比较两个区别的数据
    if(fabs(x3) > 0.000001 && fabs(x4) > 0.00001)
    {
        rect1 = new PaintDrawRect(x1,yMin,x3-x1,yMax-yMin,Qt::blue);
        rect2 = new PaintDrawRect(x2,yMin,x4-x2,yMax-yMin,Qt::green);
        rect1->setRenderHint(QwtPlotItem::RenderAntialiased);
        rect1->attach(this);
        rect2->setRenderHint(QwtPlotItem::RenderAntialiased);
        rect2->attach(this);
        for(int i =0;i<modelBases.size();i++)
        {
            ModelBase* object = modelBases[i];
            std::vector<Point2D> points = object->getPoint2D();
            for(int j=0;j<points.size();j++)
            {
                Point2D p = points[j];
                if( p.x > x1 && p.x < x3)
                {
                    number++;
                    yMean = yMean+p.y;
                    if(p.y < minY)
                    {
                        minY = p.y;
                    }
                    if(p.y > maxY)
                    {
                        maxY = p.y;
                    }
                }
                if( p.x > x2 && p.x < x4)
                {
                    number++;
                    yMean = yMean+p.y;
                    if(p.y < minY)
                    {
                        minY = p.y;
                    }
                    if(p.y > maxY)
                    {
                        maxY = p.y;
                    }
                }
                if(fabs(p.x-(x3+x1)/2) < 0.001)
                {
                    centreY = centreY + p.y;
                }
                if(fabs(p.x-(x4+x2)/2) < 0.001)
                {
                    centreY = centreY + p.y;
                }
            }
            minPoints.push_back(minY);
            maxPoints.push_back(maxY);
            meanPoints.push_back(yMean/number);
            centrePoints.push_back(centreY/2);
            yMean = 0.0;
            maxY = -999;
            minY = 999;
            centreY = 0.0;
            number = 0;
        }
    }
    else if(fabs(x3) > 0.000001)
    {
        rect1 = new PaintDrawRect(x1,yMin,x3-x1,yMax-yMin,Qt::blue);
        rect1->setRenderHint(QwtPlotItem::RenderAntialiased);
        rect1->attach(this);
        for(int i =0;i<modelBases.size();i++)
        {
            ModelBase* object = modelBases[i];
            std::vector<Point2D> points = object->getPoint2D();
            for(int j=0;j<points.size();j++)
            {
                Point2D p = points[j];
                if( p.x > x1 && p.x < x3)
                {
                    number++;
                    yMean = yMean+p.y;
                    if(p.y < minY)
                    {
                        minY = p.y;
                    }
                    if(p.y > maxY)
                    {
                        maxY = p.y;
                    }
                }
                if(fabs(p.x-(x3+x1)/2) < 0.001)
                {
                    centreY = p.y;
                }
            }
            minPoints.push_back(minY);
            maxPoints.push_back(maxY);
            meanPoints.push_back(yMean/number);
            centrePoints.push_back(centreY);
            yMean = 0.0;
            maxY = -999;
            minY = 999;
            centreY = 0.0;
            number = 0;
        }
    }
    else if(fabs(x4) > 0.000001)
    {
        rect2 = new PaintDrawRect(x2,yMin,x4-x2,yMax-yMin,Qt::green);
        rect2->setRenderHint(QwtPlotItem::RenderAntialiased);
        rect2->attach(this);
        for(int i =0;i<modelBases.size();i++)
        {
            ModelBase* object = modelBases[i];
            std::vector<Point2D> points = object->getPoint2D();
            for(int j=0;j<points.size();j++)
            {
                Point2D p = points[j];
                if( p.x > x2 && p.x < x4)
                {
                    number++;
                    yMean = yMean+p.y;
                    if(p.y < minY)
                    {
                        minY = p.y;
                    }
                    if(p.y > maxY)
                    {
                        maxY = p.y;
                    }
                }
                if(fabs(p.x-(x4+x2)/2) < 0.001)
                {
                    centreY = p.y;
                }
            }
            minPoints.push_back(minY);
            maxPoints.push_back(maxY);
            meanPoints.push_back(yMean/number);
            centrePoints.push_back(centreY);
            yMean = 0.0;
            maxY = -999;
            minY = 999;
            centreY = 0.0;
            number = 0;
        }
    }
    else
    {
        if(fabs(x1) > 0.000001 && fabs(x2) > 0.00001)
        {
            if((x1-xMin) < (x2-x1) && (xMax-x2) < (x2-x1))
            {
                rect1 = new PaintDrawRect(xMin,yMin,x1-xMin,yMax-yMin,Qt::blue);
                rect1->setRenderHint(QwtPlotItem::RenderAntialiased);
                rect1->attach(this);
                rect2 = new PaintDrawRect(x2,yMin,xMax-x2,yMax-yMin,Qt::green);
                rect2->setRenderHint(QwtPlotItem::RenderAntialiased);
                rect2->attach(this);
                for(int i =0;i<modelBases.size();i++)
                {
                    ModelBase* object = modelBases[i];
                    std::vector<Point2D> points = object->getPoint2D();
                    for(int j=0;j<points.size();j++)
                    {
                        Point2D p = points[j];
                        if( p.x > xMin && p.x < x1)
                        {
                            number++;
                            yMean = yMean+p.y;
                            if(p.y < minY)
                            {
                                minY = p.y;
                            }
                            if(p.y > maxY)
                            {
                                maxY = p.y;
                            }
                        }
                        if( p.x > x2 && p.x < xMax)
                        {
                            number++;
                            yMean = yMean+p.y;
                            if(p.y < minY)
                            {
                                minY = p.y;
                            }
                            if(p.y > maxY)
                            {
                                maxY = p.y;
                            }
                        }
                        if(fabs(p.x-(xMin+x1)/2) < 0.001)
                        {
                            centreY = centreY + p.y;
                        }
                        if(fabs(p.x-(xMax+x2)/2) < 0.001)
                        {
                            centreY = centreY + p.y;
                        }
                    }
                    minPoints.push_back(minY);
                    maxPoints.push_back(maxY);
                    meanPoints.push_back(yMean/number);
                    centrePoints.push_back(centreY/2);
                    yMean = 0.0;
                    maxY = -999;
                    minY = 999;
                    centreY = 0.0;
                    number = 0;
                }
            }
            else if((x2-xMin) < (x1-x2) && (xMax-x1) < (x1-x2))
            {
                rect1 = new PaintDrawRect(xMin,yMin,x2-xMin,yMax-yMin,Qt::blue);
                rect1->setRenderHint(QwtPlotItem::RenderAntialiased);
                rect1->attach(this);
                rect2 = new PaintDrawRect(x1,yMin,xMax-x1,yMax-yMin,Qt::green);
                rect2->setRenderHint(QwtPlotItem::RenderAntialiased);
                rect2->attach(this);
                for(int i =0;i<modelBases.size();i++)
                {
                    ModelBase* object = modelBases[i];
                    std::vector<Point2D> points = object->getPoint2D();
                    for(int j=0;j<points.size();j++)
                    {
                        Point2D p = points[j];
                        if( p.x > x2 && p.x < xMin)
                        {
                            number++;
                            yMean = yMean+p.y;
                            if(p.y < minY)
                            {
                                minY = p.y;
                            }
                            if(p.y > maxY)
                            {
                                maxY = p.y;
                            }
                        }
                        if( p.x > x1 && p.x < xMax)
                        {
                            number++;
                            yMean = yMean+p.y;
                            if(p.y < minY)
                            {
                                minY = p.y;
                            }
                            if(p.y > maxY)
                            {
                                maxY = p.y;
                            }
                        }
                        if(fabs(p.x-(x2+xMin)/2) < 0.001)
                        {
                            centreY = centreY + p.y;
                        }
                        if(fabs(p.x-(xMax+x1)/2) < 0.001)
                        {
                            centreY = centreY + p.y;
                        }
                    }
                    minPoints.push_back(minY);
                    maxPoints.push_back(maxY);
                    meanPoints.push_back(yMean/number);
                    centrePoints.push_back(centreY/2);
                    yMean = 0.0;
                    maxY = -999;
                    minY = 999;
                    centreY = 0.0;
                    number = 0;
                }
            }
            else
            {
                rect1 = new PaintDrawRect(x1,yMin,x2-x1,yMax-yMin,Qt::blue);
                rect1->setRenderHint(QwtPlotItem::RenderAntialiased);
                rect1->attach(this);
                for(int i =0;i<modelBases.size();i++)
                {
                    ModelBase* object = modelBases[i];
                    std::vector<Point2D> points = object->getPoint2D();
                    for(int j=0;j<points.size();j++)
                    {
                        Point2D p = points[j];
                        if( p.x > x1 && p.x < x2)
                        {
                            number++;
                            yMean = yMean+p.y;
                            if(p.y < minY)
                            {
                                minY = p.y;
                            }
                            if(p.y > maxY)
                            {
                                maxY = p.y;
                            }
                        }
                        if(fabs(p.x-(x2+x1)/2) < 0.001)
                        {
                            centreY = p.y;
                        }
                    }
                    minPoints.push_back(minY);
                    maxPoints.push_back(maxY);
                    meanPoints.push_back(yMean/number);
                    centrePoints.push_back(centreY);
                    yMean = 0.0;
                    maxY = -999;
                    minY = 999;
                    centreY = 0.0;
                    number = 0;
                }
            }
        }
        else if(fabs(x1) > 0.000001 && fabs(x2) <0.0001)
        {
            rect1 = new PaintDrawRect(x1,yMin,0,yMax-yMin,Qt::blue);
            rect1->setRenderHint(QwtPlotItem::RenderAntialiased);
            rect1->attach(this);
        }
        else if(fabs(x2) > 0.000001 && fabs(x1) <0.0001)
        {
            rect1 = new PaintDrawRect(x2,yMin,0,yMax-yMin,Qt::blue);
            rect1->setRenderHint(QwtPlotItem::RenderAntialiased);
            rect1->attach(this);
        }
    }
    std::vector<std::vector<double>>values;
    values.push_back(meanPoints);
    values.push_back(maxPoints);
    values.push_back(minPoints);
    values.push_back(centrePoints);
    Business::getBusiness()->getDateCountTabWidget()->setTableWidgetValue(values);


    this->replot();
}

void DrawStatisicalCurve::clearDateVluess()
{
    minPoints.clear();
    maxPoints.clear();
    centrePoints.clear();
    meanPoints.clear();
}

void DrawStatisicalCurve::clearRect()
{
    if(rect1)
    {
        delete rect1;
        rect1 = NULL;
    }
    if(rect2)
    {
        delete rect2;
        rect2 = NULL;
    }
    this->replot();
}
