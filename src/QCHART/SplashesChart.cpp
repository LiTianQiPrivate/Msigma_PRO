#include "SplashesChart.h"


SplashesChart::SplashesChart(QWidget *parent,QString classname) :
    QWidget(parent),MsigmaBase(classname)
{
    chart = new QChart();
    chartView = new ChartView(chart);
    //series = new QScatterSeries();
    QHBoxLayout* layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->addWidget(chartView);
    this->setLayout(layout);
}

SplashesChart::~SplashesChart()
{
    delete chart;
    delete chartView;
    //delete series;
}
void SplashesChart::setModelBases(std::vector<ModelBase*> modelObjects, int index)
{
    clearModelBase();
    for(int i = 0; i < modelObjects.size(); i++)
    {
        addModelBase(modelObjects[i]);
    }
    //addModelBase(modelObjects[index]);
}
void SplashesChart::addModelBase(ModelBase* modelObject)
{
    //clearModelBase();
    modelBases.push_back(modelObject);
    //-----------设置x，y坐标和范围--------------//
    double xMin = 10000000, xMax = -10000000;
    double yMin = 10000000, yMax = -10000000;
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
    QScatterSeries *series = new QScatterSeries();
    std::vector<Point2D> points = modelObject->getPoint2D();
    for(int j = 0; j < points.size(); j++)
    {
        Point2D p = points[j];
        series->append(p.x,p.y);
    }
    //series->setName("splashes1");
    series->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series->setMarkerSize(10.0);
    series->setColor(modelObject->getColor());
    // 创建x轴和y轴
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->setRange(QString("%1").arg(xMin),QString("%1").arg(xMax));
    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(yMin,yMax);
    chart->addSeries(series);
    chart->setAxisX(axisX);
    chart->setAxisY(axisY);
    chart->setTitle("splashes chart");
    chart->createDefaultAxes();
    /*chart->setDropShadowEnabled(false);
    chart->legend()->setVisible(false);
    chart->legend()->setAlignment(Qt::AlignBottom);//底部对齐
    chart->legend()->setBackgroundVisible(true);//设置背景是否可视
    chart->legend()->setAutoFillBackground(true);//设置背景自动填充
    chart->legend()->setColor(QColor(222,233,251));//设置颜色
    chart->legend()->setLabelColor(QColor(0,100,255));//设置标签颜色*/
    //chart->legend()->setMarkerShape(QLegend::MarkerShapeFromSeries);
    chartView->setRenderHint(QPainter::Antialiasing);
    scatterSeries.push_back(series);
}
void SplashesChart::clearModelBase()
{
    //QList<QAbstractSeries *> seriesList = chart->series();
    for(int i = 0; i < scatterSeries.size(); i++)
    {
        chart->removeSeries(scatterSeries.at(i));
    }
    scatterSeries.clear();
    modelBases.clear();
}
void SplashesChart::showModelBase(int index)
{
    if(scatterSeries.size() > index)
    {
        scatterSeries[index]->setVisible(1);
    }
}
void SplashesChart::hideModelBase(int index)
{
    if(scatterSeries.size() > index)
    {
        scatterSeries[index]->setVisible(0);
    }
}
bool SplashesChart::isVisible(int index)
{
    if(scatterSeries.size() > index)
    {
        return scatterSeries[index]->isVisible();
    }
    return false;
}
void SplashesChart::removeModelBase(int index)
{
    if(scatterSeries.size() > index)
    {
        chart->removeSeries(scatterSeries[index]);
        delete scatterSeries[index];
        scatterSeries.erase(scatterSeries.begin() + index);
        modelBases.erase(modelBases.begin() + index);
    }
}
