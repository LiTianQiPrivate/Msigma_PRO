#ifndef SPLASHESCHART_H
#define SPLASHESCHART_H

#include <QWidget>
#include <QtCharts/QChartGlobal>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QPercentBarSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QLegend>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtCore/QRandomGenerator>
#include <QtCharts/QBarCategoryAxis>
#include <QtWidgets/QApplication>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLegendMarker>
#include <QtGui/QImage>
#include <QtGui/QPainter>
#include <QtCore/QtMath>
#include "ModelBase.h"
#include "MsigmaBase.h"
#include "ChartView.h"
QT_CHARTS_BEGIN_NAMESPACE
class QChartView;
class QChart;
QT_CHARTS_END_NAMESPACE
QT_CHARTS_USE_NAMESPACE
/**
 * @brief The SplashesChart class
 * 散点图
 */
class SplashesChart : public QWidget,public MsigmaBase
{
    Q_OBJECT

public:
    explicit SplashesChart(QWidget *parent = nullptr,QString className = "SplashesChart");
    ~SplashesChart();
    void setModelBases(std::vector<ModelBase*> modelObjects,int index);
    void addModelBase(ModelBase* modelObject);
    void clearModelBase();
    void showModelBase(int index);
    void hideModelBase(int index);
    bool isVisible(int index);
    void removeModelBase(int index);
    void on_lineStyleComboBoxActivated(int v,int index){};
private:
    QChart *chart = nullptr;
    QChartView *chartView = nullptr;
    //QScatterSeries *series = nullptr;
    std::vector<QScatterSeries *>scatterSeries;
};

#endif // SPLASHESCHART_H
