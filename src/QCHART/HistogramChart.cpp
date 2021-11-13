#include "HistogramChart.h"

HistogramChart::HistogramChart(QWidget *parent, QString classname) :
    MsigmaBase(classname),QWidget(parent)
{
    chart = new QChart();
    chartView = new ChartView(chart);
    //set = new QBarSet(" ");
//    series = new QBarSeries();
    QHBoxLayout* layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->addWidget(chartView);
    this->setLayout(layout);
}
HistogramChart::~HistogramChart()
{
    delete chart;
    delete chartView;
//    delete set;
//    delete series;
}

void HistogramChart::setModelBases(std::vector<ModelBase *> modelObjects, int index)
{
    clearModelBase();
    for(int i = 0; i < modelObjects.size(); i++)
    {
        addModelBase(modelObjects[i]);
    }

}
void HistogramChart::addModelBase(ModelBase* modelObject)
{
//    clearModelBase();
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
    chart->setTitle("histogram chart");
    QBarSet *set = new QBarSet(" ");
    QBarSeries *barSeries = new QBarSeries(chart);
    std::vector<Point2D> points = modelObject->getPoint2D();
    int i = (points.size())/11;
    int k = (points.size())%11;
    if(k == 0)
    {
        for(int j=0;j<12;j++)
        {
            Point2D point = points[j*i];
            set->append(point.y);
        }
    }
    else
    {
        for(int j=0;j<11;j++)
        {
            Point2D point = points[j*i];
            set->append(point.y);
        }
        Point2D point = points[points.size()];
        set->append(point.y);
    }
    barseries.push_back(barSeries);
    //set->setLabelColor(QColor(0,0,255));
    set->setColor(modelObject->getColor());
    barSeries->append(set);
    barSeries->setVisible();
    barSeries->setLabelsVisible(false);
    chart->setTheme(QChart::ChartThemeLight); // 设置白色主题
    chart->setDropShadowEnabled();  // 背面阴影
    chart->addSeries(barSeries);
    // 创建x轴和y轴
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append("-150");
    axisX->append("-120");
    axisX->append("-90");
    axisX->append("-60");
    axisX->append("-30");
    axisX->append("0");
    axisX->append("30");
    axisX->append("60");
    axisX->append("90");
    axisX->append("120");
    axisX->append("150");
    axisX->setLabelsColor(QColor(7,28,96));
    axisX->setRange(QString::number(xMin),QString::number(xMax));

    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(yMin,yMax);
    /*axisY->setTitleText("频率");
    axisY->setLabelFormat("%dHz");*/
    chart->createDefaultAxes();
    chart->setAxisX(axisX);
    chart->setAxisY(axisY);
    //修改说明样式
    chart->legend()->setVisible(false);
    /*chart->legend()->setAlignment(Qt::AlignBottom);//底部对齐
    chart->legend()->setBackgroundVisible(true);//设置背景是否可视
    chart->legend()->setAutoFillBackground(true);//设置背景自动填充
    chart->legend()->setColor(QColor(222,233,251));//设置颜色
    chart->legend()->setLabelColor(QColor(0,100,255));//设置标签颜色*/
    //chart->legend()->setMaximumHeight(fabs((xMax-xMin))/11);
    chartView->setRenderHint(QPainter::Antialiasing);
}
void HistogramChart::clearModelBase()
{
    for(int i = 0; i < barseries.size(); i++)
    {
        chart->removeSeries(barseries.at(i));
    }
    barseries.clear();
    modelBases.clear();
}
void HistogramChart::showModelBase(int index)
{
    if(barseries.size() > index)
    {
        barseries[index]->setVisible(1);
    }
}
void HistogramChart::hideModelBase(int index)
{
    if(barseries.size() > index)
    {
        barseries[index]->setVisible(0);
    }
}

bool HistogramChart::isVisible(int index)
{
    if(barseries.size() > index)
    {
        return barseries[index]->isVisible();
    }
    return false;
}
void HistogramChart::removeModelBase(int index)
{
    if(barseries.size() > index)
    {
        chart->removeSeries(barseries[index]);
        delete barseries[index];
        barseries.erase(barseries.begin() + index);
        modelBases.erase(modelBases.begin() + index);
    }
}
