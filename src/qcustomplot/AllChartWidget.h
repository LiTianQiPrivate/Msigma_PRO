#ifndef ALLCHARTWIDGET_H
#define ALLCHARTWIDGET_H

#include <QWidget>
#include <qcustomplot.h>
#include "MsigmaBase.h"
namespace Ui {
class AllChartWidget;
}
class QCustomPlot;
class AllChartWidget : public QCustomPlot, public MsigmaBase
{
    Q_OBJECT

public:
    explicit AllChartWidget(QWidget *parent = nullptr,QString className = "AllChartWidget");
    ~AllChartWidget();
    virtual void setModelBases(std::vector<ModelBase*> modelObjects,int index);
    virtual void addModelBase(ModelBase* modelObject);
    virtual void clearModelBase();
    virtual void showModelBase(int index);
    virtual void hideModelBase(int index);
    virtual bool isVisible(int index){return true;}
    virtual void removeModelBase(int index);
private:
    Ui::AllChartWidget *ui;
};




#endif // ALLCHARTWIDGET_H
