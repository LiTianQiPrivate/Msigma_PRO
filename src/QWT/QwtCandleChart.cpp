#include "QwtCandleChart.h"


QwtCandleChart::QwtCandleChart(QWidget *parent,QString className) :
    QwtPlotBase(parent,className)
{

}

QwtCandleChart::~QwtCandleChart()
{
    qDeleteAll(candleCures);
}

void QwtCandleChart::setModelBases(std::vector<ModelBase *> modelObjects, int index)
{
    clearModelBase();
    for(int i = 0; i < modelObjects.size(); i++)
    {
        addModelBase(modelObjects[i]);
    }
    for(int i = 0; i<candleCures.size();i++)
    {
        if(i == 0)
        {
            candleCures[0]->show();
        }
        else
        {
            candleCures[i]->hide();
        }
    }
}

void QwtCandleChart::addModelBase(ModelBase *modelObject)
{
    modelBases.push_back(modelObject);
    std::vector<std::vector<Point3D>>& lines = modelObject->getPointDatas();
    if(lines.size() <= 1)
    {
        return;
    }
    //
    std::vector<double> meanValues; // Z均值
    std::vector<double> maxValues; // Z最高值
    std::vector<double> minValues; // Z最低值
    double zMax = -10000000;
    double zMin = 10000000;
    double xMax = -10000000;
    double xMin = 10000000;
    for(int i = 0; i < lines.size(); i++)
    {
        double values1 = 0;
        double values2 = -1000000;
        double values3 = 10000000;

        std::vector<Point3D>& points = lines[i];
        for(int j = 0; j < points.size(); j++)
        {
            Point3D& p = points[j];
            if(values2 < p.z)
            {
                values2 = p.z;
            }
            if(values3 > p.z)
            {
                values3 = p.z;
            }
            values1 += p.z;
            if(zMax < p.z)
            {
                zMax = p.z;
            }
            if(zMin > p.z)
            {
                zMin = p.z;
            }
            if(xMax < p.x)
            {
                xMax = p.x;
            }
            if(xMin > p.x)
            {
                xMin = p.x;
            }
        }
        values1 = values1/points.size();
        meanValues.push_back(values1);
        maxValues.push_back(values2);
        minValues.push_back(values3);
    }
    setAxisScale(QwtPlot::yLeft,zMin, zMax);
    setAxisScale(QwtPlot::xBottom,xMin,xMax);
    QwtPlotTradingCurve *cruve = new QwtPlotTradingCurve;
    cruve->setSymbolStyle(QwtPlotTradingCurve::CandleStick);
    QVector<QwtOHLCSample > samples;
    for(int i = 0; i < lines.size(); i++)
    {
        double values1 = meanValues[i];
        double values2 = maxValues[i];
        double values3 = minValues[i];
        double temp = (values2 - values3)/10;
        std::vector<Point3D>& points = lines[i];
        QwtOHLCSample sample(points[0].x,values1+temp,values2,values3,values1-temp);
        samples.push_back(sample);
    }
    cruve->setSymbolPen(modelObject->getColor());
    cruve->setSamples(samples);
    cruve->attach(this);
    this->replot();
    candleCures.push_back(cruve);
}

void QwtCandleChart::clearModelBase()
{
    for(int i = 0; i < candleCures.size(); i++)
    {
        if(candleCures[i])
        {
            QwtPlotTradingCurve *cruve = candleCures[i];
            delete cruve;
        }
    }
    candleCures.clear();
    modelBases.clear();
}

void QwtCandleChart::showModelBase(int index)
{
    if(candleCures.size() > index)
    {
        QwtPlotTradingCurve *cruve = candleCures[index];
        cruve->show();
    }
}

void QwtCandleChart::hideModelBase(int index)
{
    if(candleCures.size() > index)
    {
        QwtPlotTradingCurve *cruve = candleCures[index];
        cruve->hide();
    }
}

void QwtCandleChart::removeModelBase(int index)
{
    if(candleCures.size() > index)
    {
        QwtPlotTradingCurve *cruve = candleCures[index];
        delete cruve;
        candleCures.erase(candleCures.begin() + index);
        modelBases.erase(modelBases.begin() + index);
    }
}

bool QwtCandleChart::isVisible(int index)
{
    if(candleCures.size() > index)
    {
        QwtPlotTradingCurve *cruve = candleCures[index];
        return cruve->isVisible();
    }
    return false;
}
