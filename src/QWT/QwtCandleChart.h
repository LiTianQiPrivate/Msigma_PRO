#ifndef QWTCANDLECHART_H
#define QWTCANDLECHART_H

#include <QWidget>
#include "QwtPlotBase.h"
#include "qwt_plot_tradingcurve.h"

class QwtCandleChart : public QwtPlotBase
{
    Q_OBJECT

public:
    explicit QwtCandleChart(QWidget *parent = nullptr,QString className ="QwtCandleChart");
    ~QwtCandleChart();
public:
    std::vector<QwtPlotTradingCurve *>candleCures;
public:
    void setModelBases(std::vector<ModelBase*> modelObjects,int index);
    void addModelBase(ModelBase *modelObject);
    void clearModelBase();
    void showModelBase(int index);
    void hideModelBase(int index);
    void removeModelBase(int index);
    bool isVisible(int index);
};

#endif // QWTCANDLECHART_H
