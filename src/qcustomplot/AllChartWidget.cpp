#include "AllChartWidget.h"

AllChartWidget::AllChartWidget(QWidget *parent,QString className) :
    QCustomPlot(parent),MsigmaBase(className)
{

}

AllChartWidget::~AllChartWidget()
{

}

void AllChartWidget::addModelBase(ModelBase *modelObject){}

void AllChartWidget::setModelBases(std::vector<ModelBase *> modelObjects, int index){}

void AllChartWidget::clearModelBase(){}

void AllChartWidget::showModelBase(int index){}

void AllChartWidget::hideModelBase(int index){}

void AllChartWidget::removeModelBase(int index){}
