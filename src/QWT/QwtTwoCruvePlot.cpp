#include "QwtTwoCruvePlot.h"

QwtTwoCruvePlot::QwtTwoCruvePlot(QWidget *parent, QString className):QwtPlotBase(parent,className)
{

}

QwtTwoCruvePlot::~QwtTwoCruvePlot()
{
    qDeleteAll(intervalCurves);
}

void QwtTwoCruvePlot::setModelBases(std::vector<ModelBase *> modelObjects, int index)
{
    clearModelBase();
    for(int i = 0; i < modelObjects.size(); i++)
    {
        addModelBase(modelObjects[i]);
    }
}

void QwtTwoCruvePlot::addModelBase(ModelBase *modelObject)
{
    this->modelBases.push_back(modelObject);
    std::vector<double> meanValues; // Z均值
    std::vector<double> maxValues; // Z最高值
    std::vector<double> minValues; // Z最低值
    double zMax = -10000000;
    double zMin = 10000000;
    double xMax = -10000000;
    double xMin = 10000000;
    std::vector<std::vector<Point3D>>& lines = modelObject->getPointDatas();
    if(lines.size() <= 1)
    {
        return;
    }
    //
    QVector<QwtIntervalSample> samples(lines.size());
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
        QwtInterval interval(values3,values2);
        samples[i] = QwtIntervalSample(points[0].x,interval);
        meanValues.push_back(points[0].x);
    }

    setAxisTitle(QwtPlot::yLeft,"Y");
    setAxisTitle(QwtPlot::xBottom,"X");
    setAxisScale(QwtPlot::yLeft,zMin, zMax);
    setAxisScale(QwtPlot::xBottom,xMin,xMax);
    QwtPlotIntervalCurve *cruve = new QwtPlotIntervalCurve;
    QBrush brush(modelObject->getColor());
    cruve->setBrush(brush);
    cruve->setData(new QwtIntervalSeriesData(samples));
    cruve->setSamples(samples);
    cruve->setPen(modelObject->getColor(),2);
    cruve->attach(this);
    intervalCurves.push_back(cruve);
    this->replot();
}

void QwtTwoCruvePlot::clearModelBase()
{
    for(int i = 0; i < intervalCurves.size(); i++)
    {
        if(intervalCurves[i])
        {
            QwtPlotIntervalCurve *cruve = intervalCurves[i];
            delete cruve;
        }
    }
    intervalCurves.clear();
    this->modelBases.clear();
}

void QwtTwoCruvePlot::showModelBase(int index)
{
    if(intervalCurves.size() > index)
    {
        QwtPlotIntervalCurve *cruve = intervalCurves[index];
        cruve->show();
    }
}

void QwtTwoCruvePlot::hideModelBase(int index)
{
    if(intervalCurves.size() > index)
    {
        QwtPlotIntervalCurve *cruve = intervalCurves[index];
        cruve->hide();
    }
}

void QwtTwoCruvePlot::removeModelBase(int index)
{
    if(intervalCurves.size() > index)
    {

        QwtPlotIntervalCurve *cruve = intervalCurves[index];
        delete cruve;
        intervalCurves.erase(intervalCurves.begin() + index);
        this->modelBases.erase(this->modelBases.begin() + index);
    }
}

bool QwtTwoCruvePlot::isVisible(int index)
{
    if(intervalCurves.size() > index)
    {
        QwtPlotIntervalCurve *cruve = intervalCurves[index];
        return cruve->isVisible();
    }
    return false;
}
