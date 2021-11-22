#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ModelTabWidget.h"
#include "ModelTableWidget.h"
#include "ModelTreeWidget.h"
#include "StepWidget.h"
#include "CurveShowAndSetWidget.h"
#include "ViewForm.h"
#include "QStackedWidget"
#include "DateCountTabWidget.h"
#include "ViewFormRCS.h"
#include "StatisticalAnalysisWidget.h"
#include "ViewFromHisgram.h"
#include "DataTranslationAline.h"
#include "DataPrintAndOutput.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_openaction_triggered();

    void on_action_triggered();

    void on_action_2_triggered();

    void on_action_3_triggered();

    void on_action_4_triggered();

    void on_action_6_triggered();

    void on_action_8_triggered();

    void on_action_9_triggered();

    void on_action_10_triggered();

    void on_action_11_triggered();

    void on_action_12_triggered();

    void on_action_13_triggered();

    void on_action_7_triggered();

    void on_action_14_triggered();

    void on_action_15_triggered();
private slots:
    void on_toolBox_currentChanged(int index);
    void on_addaction_triggered();
    void on_action_16_triggered();

private:
    Ui::MainWindow *ui;
    ModelTabWidget modelTabWidget;
    ModelTreeWidget modelTreeWidget;
    ModelTableWidget modelTableWidget;
    CurveShowAndSetWidget curveShowAndSetWidget;
    DataTranslationAline dataTranslationAline;
    DataPrintAndOutput dataPrintAndOutput;
    StepWidget stepWidget;
    ViewFormRCS viewFormRCS;
    ViewFromHisgram viewFromHisgram;
    DateCountTabWidget dateCountTabWidget;
    QStackedWidget stackedWidget;
    QTabWidget tabWidget;
    StatisticalAnalysisWidget statisticalAnalysisWidget;
};
#endif // MAINWINDOW_H
