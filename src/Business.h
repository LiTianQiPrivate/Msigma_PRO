#ifndef BUSINESS_H
#define BUSINESS_H

#include <QString>
#include "ModelBase.h"

class ModelTableWidget;
class ModelTabWidget;
class ModelTreeWidget;
class CurveShowAndSetWidget;
class StepWidget;
class ViewForm;
class DateCountTabWidget;
class ViewFormRCS;
class StatisticalAnalysisWidget;
class ViewFromHisgram;
class Business
{
public:
    Business();
    static Business* getBusiness();
    ModelBase *loadModelBase(QString fileName);
    ModelTableWidget *getModelTableWidget();
    void setModelTableWidget(ModelTableWidget *value);

    ModelTabWidget *getModelTabWidget();
    void setModelTabWidget(ModelTabWidget *value);

    ModelTreeWidget *getModelTreeWidget();
    void setModelTreeWidget(ModelTreeWidget *value);

    CurveShowAndSetWidget *getCurveShowAndSetWidget();
    void setCurveShowAndSetWidget(CurveShowAndSetWidget *value);

    StepWidget *getStepWidget();
    void setStepWidget(StepWidget *value);

    ViewForm *getViewForm();
    void setViewForm(ViewForm *value);

    DateCountTabWidget *getDateCountTabWidget();
    void setDateCountTabWidget(DateCountTabWidget *value);

    ViewFormRCS *getViewFormRCS();
    void setViewFormRCS(ViewFormRCS *value);

    StatisticalAnalysisWidget *getStatisticalAnalysisWidget();
    void setStatisticalAnalysisWidget(StatisticalAnalysisWidget *value);

    ViewFromHisgram *getViewFromHisgram();
    void setViewFromHisgram(ViewFromHisgram *value);
private:
    static Business* business;
    std::vector<ModelBase*> modelObjects; // 文件数据
    ModelTableWidget* modelTableWidget = nullptr;
    ModelTabWidget* modelTabWidget = NULL;
    ModelTreeWidget* modelTreeWidget = NULL;
    CurveShowAndSetWidget *curveShowAndSetWidget = nullptr;
    StepWidget *stepWidget = nullptr;
    ViewForm *viewForm = nullptr;
    DateCountTabWidget *dateCountTabWidget = nullptr;
    ViewFormRCS *viewFormRCS = nullptr;
    StatisticalAnalysisWidget *statisticalAnalysisWidget = nullptr;
    ViewFromHisgram *viewFromHisgram = nullptr;
};

#endif // BUSINESS_H
