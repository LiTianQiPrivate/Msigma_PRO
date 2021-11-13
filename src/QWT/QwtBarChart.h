#ifndef QWTBARCHART_H
#define QWTBARCHART_H

#include "QwtPlotBase.h"
#include "qwt_plot_multi_barchart.h"
#include "qwt_plot_barchart.h"
class QwtBarChart : public QwtPlotBase
{
    Q_OBJECT

public:
    explicit QwtBarChart(QWidget *parent = nullptr,QString className = "QwtBarChart");
    ~QwtBarChart();
public:
    QwtPlotMultiBarChart *cruve = nullptr;
public:
    void setModelBases(std::vector<ModelBase*> modelObjects,int index);
    void addModelBase(ModelBase *modelObject);
    void clearModelBase();
    void showModelBase(int index);
    void hideModelBase(int index);
    void removeModelBase(int index);
    bool isVisible(int index);
public:
    void getStandIndex(int index);
};

#endif // QWTBARCHART_H
