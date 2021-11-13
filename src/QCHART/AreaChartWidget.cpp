    #include "AreaChartWidget.h"
#include "QHBoxLayout"

AreaChartWidget::AreaChartWidget(QWidget *parent, QString className) :
    QWidget(parent),MsigmaBase(className)
{
    chart = new QChart();
    chartView = new ChartView(chart);
    QHBoxLayout* layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->addWidget(chartView);
    this->setLayout(layout);
}

AreaChartWidget::~AreaChartWidget()
{
    delete chart;
    delete chartView;
}

void AreaChartWidget::setModelBases(std::vector<ModelBase *> modelObjects, int index)
{
    clearModelBase();

    //addModelBase(modelObjects[index]);
    for(int i = 0; i < modelObjects.size(); i++)
    {
        addModelBase(modelObjects[i]);
    }
}

void AreaChartWidget::addModelBase(ModelBase *modelObject)
{
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
    chart->setTitle("Area chart");
    QLineSeries *upperSeries = new QLineSeries(chart);
    std::vector<Point2D> points = modelObject->getPoint2D();
    for(int j = 0; j < points.size(); j++)
    {
        Point2D p = points[j];
        upperSeries->append(QPointF(p.x, p.y));
    }
    QLineSeries *lowerSeries = 0;
    if(lines.size() > 0)
    {
        lowerSeries = lines[lines.size() - 1];
    }
    lines.push_back(upperSeries);
    QAreaSeries *area = new QAreaSeries(upperSeries, lowerSeries);
    area->setColor(modelObject->getColor());
    areaSeriess.push_back(area);
//    area->setName(name + QString::number(nameIndex));
    chart->addSeries(area);

    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setRange(xMin, xMax);
    chart->axes(Qt::Vertical).first()->setRange(yMin, yMax);
    // Add space to label to add space between labels and axis
    QValueAxis *axisY = qobject_cast<QValueAxis*>(chart->axes(Qt::Vertical).first());
    Q_ASSERT(axisY);
    axisY->setLabelFormat("%.1f  ");

}

void AreaChartWidget::clearModelBase()
{
    for(int i = 0; i < lines.size(); i++)
    {
        if(lines[i])
        {
            delete lines[i];
        }
    }
    lines.clear();
    for(int i = 0; i < areaSeriess.size(); i++)
    {
        if(areaSeriess[i])
        {
            chart->removeSeries(areaSeriess[i]);
            delete areaSeriess[i];
        }
    }
    areaSeriess.clear();
    modelBases.clear();

}

void AreaChartWidget::showModelBase(int index)
{
    if(areaSeriess.size() > index)
    {
        areaSeriess[index]->setVisible(1);
    }
}

void AreaChartWidget::hideModelBase(int index)
{
    if(areaSeriess.size() > index)
    {
        areaSeriess[index]->setVisible(0);
    }
}

void AreaChartWidget::removeModelBase(int index)
{
    if(areaSeriess.size() > index)
    {

        chart->removeSeries(areaSeriess[index]);
        delete areaSeriess[index];
        areaSeriess.erase(areaSeriess.begin() + index);

        delete lines[index];
        lines.erase(lines.begin() + index);

        modelBases.erase(modelBases.begin() + index);
    }
}

bool AreaChartWidget::isVisible(int index)
{
    if(areaSeriess.size() > index)
    {
        return areaSeriess[index]->isVisible();
    }
    return false;
}
