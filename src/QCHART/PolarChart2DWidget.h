#ifndef POLARCHART2DWIDGET_H
#define POLARCHART2DWIDGET_H
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
#include <QtCharts/QPolarChart>
#include "ModelBase.h"
#include "MsigmaBase.h"
#include "ChartView.h"
QT_CHARTS_BEGIN_NAMESPACE
class QChartView;
class QChart;
QT_CHARTS_END_NAMESPACE
QT_CHARTS_USE_NAMESPACE
/**
 * @brief The PolarChart2DWidget class
 * 2D极坐标图
 */
class PolarChart2DWidget : public QWidget,public MsigmaBase
{
public:
    PolarChart2DWidget(QWidget *parent = nullptr, QString className = "PolarChart2DWidget");
    ~PolarChart2DWidget();
    void setModelBases(std::vector<ModelBase*> modelObjects,int index);
    void addModelBase(ModelBase* modelObject);
    void clearModelBase();
    void showModelBase(int index);
    void hideModelBase(int index);
    void removeModelBase(int index);
    bool isVisible(int index);
private:
//    QLineSeries* mCurveData = nullptr;
    QPolarChart *mPolarChart = nullptr;
    QChartView *mChartView = nullptr;
//    std::vector<QLineSeries *> lines;
};

#endif // POLARCHART2DWIDGET_H
