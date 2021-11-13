#ifndef SETCRUVEDIALOG_H
#define SETCRUVEDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QtCharts/QChartGlobal>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QCandlestickSet>
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
#include "ModelRCSF.h"
#include "ChartView.h"
QT_CHARTS_BEGIN_NAMESPACE
class QChartView;
class QChart;
QT_CHARTS_END_NAMESPACE
QT_CHARTS_USE_NAMESPACE
namespace Ui {
class SetCruveDialog;
}

class SetCruveDialog : public QWidget
{
    Q_OBJECT

public:
    explicit SetCruveDialog(QWidget *parent = nullptr);
    ~SetCruveDialog();
    void setButtonState();
    bool buttonState[4];   // 用来记载四个button的状态
    double doubleData[4];  // 用来记载四个text数据
    void setTempModelBase(std::vector<ModelBase *>base);
private slots:
    void on_radioButton_clicked(bool checked);

    void on_radioButton_2_clicked(bool checked);

    void on_radioButton_3_clicked(bool checked);

    void on_radioButton_4_clicked(bool checked);

    void on_pushButton_clicked(bool checked);

    void on_pushButton_2_clicked(bool checked);

    void on_pushButton_3_clicked(bool checked);

    void on_pushButton_4_clicked(bool checked);
private slots:
    void upDataFps();
    void upDataAngle();
private:
    QTimer *time_Fps;
    QTimer *time_Angle;
    Ui::SetCruveDialog *ui;
    std::vector<ModelBase *>tempModelBase;
    void updataModelBaseShow(int xStep,int index,ModelBase *modelBase);
    QChart *chart = nullptr;
    QChartView *chartView = nullptr;
};

#endif // SETCRUVEDIALOG_H
