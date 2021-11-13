#include "CandleChartWidget.h"

CandleChartWidget::CandleChartWidget(QWidget *parent,QString classname) :
    QWidget(parent),MsigmaBase(classname)
{
    chart = new QChart();
    chartView = new ChartView(chart);
    //series = new QCandlestickSeries();
    //candleSet = new QCandlestickSet();
    QHBoxLayout* layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->addWidget(chartView);
    this->setLayout(layout);
}

CandleChartWidget::~CandleChartWidget()
{
    delete chart;
    delete chartView;
}
void CandleChartWidget::setModelBases(std::vector<ModelBase*> modelObjects, int index)
{
    clearModelBase();
    for(int i = 0; i < modelObjects.size(); i++)
    {
        addModelBase(modelObjects[i]);
    }
    for(int i = 0; i<candlSeries.size();i++)
    {
        if(i == 0)
        {
            candlSeries[0]->setVisible(1);
        }
        else
        {
            candlSeries[i]->setVisible(0);
        }
    }
}
void CandleChartWidget::addModelBase(ModelBase* modelObject)
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
    QCandlestickSeries *series = new QCandlestickSeries();
    //QCandlestickSet *candleSet = new QCandlestickSet();
    //series->clear();
    series->setIncreasingColor(QColor(Qt::green));
    series->setDecreasingColor(QColor(Qt::red));
    //series->setVisible(0);
    QStringList categories;
    for(int i = 0; i < lines.size(); i++)
    {
        double values1 = meanValues[i];
        double values2 = maxValues[i];
        double values3 = minValues[i];
        double temp = (values2 - values3)/10;
        std::vector<Point3D>& points = lines[i];
        categories << QString::number(points[0].x);
        QCandlestickSet *set = new QCandlestickSet;
        set->setHigh(values2);
        set->setOpen(values1 + temp);
        set->setClose(values1 - temp);
        set->setLow(values3);
        series->append(set);
    }
//    series->setName("candle");
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->setCategories(categories);
    //axisX->setRange("-180","+180");
//    axisX->setRange(QString::number(xMin),QString::number(xMax));
    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(zMin,zMax);
    chart->addSeries(series);
    chart->addAxis(axisX,Qt::AlignBottom);
    chart->setAxisX(axisX,series);
    //chart->axes(Qt::Horizontal).first()->setRange(xMin, xMax);
    chart->setAxisY(axisY,series);
    //chart->legend()->setVisible(false);

    chartView->setRenderHint(QPainter::Antialiasing);

    candlSeries.push_back(series);
}
void CandleChartWidget::clearModelBase()
{
    //QList<QAbstractSeries *> seriesList = chart->series();
    for(int i = 0; i < candlSeries.size(); i++)
    {
        chart->removeSeries(candlSeries.at(i));
    }
    candlSeries.clear();
    modelBases.clear();
}
void CandleChartWidget::showModelBase(int index)
{
    if(candlSeries.size() > index)
    {
        //candlSeries[index]->setVisible(1);
        QCandlestickSeries* m_series = candlSeries[index];
        m_series->show();
    }
}
void CandleChartWidget::hideModelBase(int index)
{
    if(candlSeries.size() > index)
    {
        candlSeries[index]->setVisible(0);
    }
}
void CandleChartWidget::removeModelBase(int index)
{
    if(candlSeries.size() > index)
    {
        chart->removeSeries(candlSeries[index]);
        delete candlSeries[index];
        candlSeries.erase(candlSeries.begin() + index);
        modelBases.erase(modelBases.begin() + index);
    }
}
bool CandleChartWidget::isVisible(int index)
{
    if(candlSeries.size() > index)
    {
        return candlSeries[index]->isVisible();
    }
    return false;
}
void CandleChartWidget::on_lineStyleComboBoxActivated(int v,int index)
{
    //candlSeries[0]->setPen(QPen(QBrush(Qt::green),2,Qt::DashLine));
}
