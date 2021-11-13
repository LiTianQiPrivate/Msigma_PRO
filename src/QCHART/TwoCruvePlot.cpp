#include "TwoCruvePlot.h"


TwoCruvePlot::TwoCruvePlot(QWidget *parent,QString classname) :
    QWidget(parent),MsigmaBase(classname)
{
    chart = new QChart();
    chartView = new ChartView(chart);
    QHBoxLayout* layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->addWidget(chartView);
    this->setLayout(layout);
}

TwoCruvePlot::~TwoCruvePlot()
{
    delete chart;
    delete chartView;
}
void TwoCruvePlot::setModelBases(std::vector<ModelBase*> modelObjects, int index)
{
    clearModelBase();
    for(int i = 0; i < modelObjects.size(); i++)
    {
        addModelBase(modelObjects[i]);
    }
    for(int i = 0; i<areaSeries.size();i++)
    {
        if(i == 0)
        {
            areaSeries[i]->setVisible(1);
        }
        else
        {
            areaSeries[i]->setVisible(0);
        }
    }
}
void TwoCruvePlot::addModelBase(ModelBase* modelObject)
{

    //clearModelBase();
    modelBases.push_back(modelObject);
    std::vector<double> meanValues; // Z均值
    std::vector<double> maxValues; // Z最高值
    std::vector<double> minValues; // Z最低值
    double zMax = -10000000;
    double zMin = 10000000;
    double xMax = -10000000;
    double xMin = 10000000;
    QLineSeries *upperSeries = new QLineSeries(chart);
    QLineSeries *lowSeries = new QLineSeries(chart);
    if(modelObject->className == "ModelRCSF")
    {

    }
    else
    {

    }
    std::vector<std::vector<Point3D>>& lines = modelObject->getPointDatas();
    if(lines.size() <= 1)
    {
        return;
    }
    //
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
        upperSeries->append(QPointF(points[0].x,values2));
        lowSeries->append(QPointF(points[0].x,values3));
    }
    QAreaSeries *area = new QAreaSeries(upperSeries,lowSeries);
    area->setColor(modelObject->getColor());
    //area->setVisible(0);
    areaSeries.push_back(area);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->setRange(QString("%1").arg(xMin),QString("%1").arg(xMax));
    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(zMin,zMax);
    chart->setAxisX(axisX);
    chart->setAxisY(axisY);
    chart->addSeries(area);
    chart->setTitle("TwoCruve chart");
    chart->createDefaultAxes();
    //chart->legend()->setVisible(true);
    //chart->legend()->hide();
    /*chart->setDropShadowEnabled(false);
    chart->legend()->setAlignment(Qt::AlignBottom);//底部对齐
    chart->legend()->setBackgroundVisible(true);//设置背景是否可视
    chart->legend()->setAutoFillBackground(true);//设置背景自动填充
    chart->legend()->setColor(QColor(222,233,251));//设置颜色
    chart->legend()->setLabelColor(QColor(0,100,255));//设置标签颜色
    chart->legend()->setMarkerShape(QLegend::MarkerShapeFromSeries);*/
    chartView->setRenderHint(QPainter::Antialiasing);

}
void TwoCruvePlot::clearModelBase()
{
    for(int i = 0; i < areaSeries.size(); i++)
    {
        if(areaSeries[i])
        {
            chart->removeSeries(areaSeries[i]);
            delete areaSeries[i];
        }
    }
    areaSeries.clear();
    modelBases.clear();
}
void TwoCruvePlot::showModelBase(int index)
{
    if(areaSeries.size() > index)
    {
        areaSeries[index]->setVisible(1);
    }
}
void TwoCruvePlot::hideModelBase(int index)
{
    if(areaSeries.size() > index)
    {
        areaSeries[index]->setVisible(0);
    }
}
void TwoCruvePlot::removeModelBase(int index)
{
    if(areaSeries.size() > index)
    {

        chart->removeSeries(areaSeries[index]);
        delete areaSeries[index];
        areaSeries.erase(areaSeries.begin() + index);
        modelBases.erase(modelBases.begin() + index);
    }
}
bool TwoCruvePlot::isVisible(int index)
{
    if(areaSeries.size() > index)
    {
        return areaSeries[index]->isVisible();
    }
    return false;
}
