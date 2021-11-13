#include "PolarChart2DWidget.h"
#include "QHBoxLayout"


PolarChart2DWidget::PolarChart2DWidget(QWidget *parent, QString className) :
    QWidget(parent),MsigmaBase(className)
{
    mPolarChart = new QPolarChart();
    mChartView = new ChartView(mPolarChart);


    //坐标轴
    QValueAxis* mThetaAxis = new QValueAxis();
    mThetaAxis->setTickCount(36);
    mThetaAxis->setLabelFormat("%d");
    mThetaAxis->setRange(0, 360);
    mPolarChart->addAxis(mThetaAxis, QPolarChart::PolarOrientationAngular);

    QValueAxis* mRadiusAxis = new QValueAxis();
    mRadiusAxis->setTickCount(30);
    mRadiusAxis->setLabelFormat("%ddB");
    mRadiusAxis->setRange(0, 100);
    mPolarChart->addAxis(mRadiusAxis, QPolarChart::PolarOrientationRadial);


    QHBoxLayout* layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->addWidget(mChartView);
    this->setLayout(layout);
}

PolarChart2DWidget::~PolarChart2DWidget()
{
//    delete mCurveData;
    delete mPolarChart;
    delete mChartView;
}
void PolarChart2DWidget::setModelBases(std::vector<ModelBase *> modelObjects, int index)
{
    clearModelBase();
    for(int i = 0; i < modelObjects.size(); i++)
    {
        addModelBase(modelObjects[i]);
    }
}

void PolarChart2DWidget::addModelBase(ModelBase *modelObject)
{
    modelBases.push_back(modelObject);
    //-----------设置x，y坐标和范围--------------//
    double xMin = 10000000, xMax = -10000000;
    double yMin = 10000000, yMax = -10000000;

    for(int i = 0; i < modelBases.size(); i++)
    {
        ModelBase* object = modelBases[i];
        std::vector<Point2D> points = modelObject->getPoint2D();
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
    std::vector<Point2D> points = modelObject->getPoint2D();


    QLineSeries* mCurveData  = new QLineSeries(mPolarChart);
    for (int i = 0; i < points.size(); i++)
    {
        Point2D p = points[i];
        mCurveData->append(p.x, p.y);
    }


    mPolarChart->addSeries(mCurveData);
    mPolarChart->legend()->hide();
    mPolarChart->setTheme(QChart::ChartThemeQt);

    QList<QAbstractAxis*> axisList = mPolarChart->axes(QPolarChart::PolarOrientationAngular);

    //坐标轴
    QValueAxis* mThetaAxis = (QValueAxis*)axisList[0];
    mThetaAxis->setTickCount(36);
    mThetaAxis->setLabelFormat("%d");
    mThetaAxis->setRange(xMin, xMin+360);
    mPolarChart->addAxis(mThetaAxis, QPolarChart::PolarOrientationAngular);

    axisList = mPolarChart->axes(QPolarChart::PolarOrientationRadial);
    QValueAxis* mRadiusAxis = (QValueAxis*)axisList[0];
    mRadiusAxis->setTickCount(30);
    mRadiusAxis->setLabelFormat("%ddB");
    mRadiusAxis->setRange(yMin, yMax*2);
    mPolarChart->addAxis(mRadiusAxis, QPolarChart::PolarOrientationRadial);

    mCurveData->setColor(modelObject->getColor());
    mChartView->setFont(QFont("Consolas", 16));
    mChartView->setRenderHint(QPainter::Antialiasing);

}

void PolarChart2DWidget::clearModelBase()
{
    QList<QAbstractSeries *> seriesList = mPolarChart->series();
    for(int i = 0; i < seriesList.size(); i++)
    {
        mPolarChart->removeSeries(seriesList.at(i));
    }
    modelBases.clear();

}

void PolarChart2DWidget::showModelBase(int index)
{
    QList<QAbstractSeries *> seriesList = mPolarChart->series();
    seriesList.at(index)->show();
}

void PolarChart2DWidget::hideModelBase(int index)
{
    QList<QAbstractSeries *> seriesList = mPolarChart->series();
    seriesList.at(index)->hide();
}

void PolarChart2DWidget::removeModelBase(int index)
{
    QList<QAbstractSeries *> seriesList = mPolarChart->series();
    mPolarChart->removeSeries(seriesList.at(index));
    modelBases.erase(modelBases.begin() + index);
}

bool PolarChart2DWidget::isVisible(int index)
{
    QList<QAbstractSeries *> seriesList = mPolarChart->series();
    return seriesList.at(index)->isVisible();
}


