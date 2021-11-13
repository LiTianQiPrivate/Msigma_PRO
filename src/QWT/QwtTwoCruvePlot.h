#ifndef QWTTWOCRUVEPLOT_H
#define QWTTWOCRUVEPLOT_H
#include "QwtPlotBase.h"


class QwtTwoCruvePlot : public QwtPlotBase
{
    Q_OBJECT

public:
    explicit QwtTwoCruvePlot(QWidget *parent = nullptr, QString className = "TwoCurvePlot");
    ~QwtTwoCruvePlot();
public:
    void setModelBases(std::vector<ModelBase*> modelObjects,int index);
    void addModelBase(ModelBase *modelObject);
    void clearModelBase();
    void showModelBase(int index);
    void hideModelBase(int index);
    void removeModelBase(int index);
    bool isVisible(int index);
public:
    QVector<QwtPlotIntervalCurve *>intervalCurves;
};

#endif // QWTTWOCRUVEPLOT_H
