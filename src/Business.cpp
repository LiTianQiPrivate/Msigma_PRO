#include "Business.h"
#include <QFileInfo>
#include "ModelRAM.h"
#include "ModelRCS.h"
#include "ModelRCSF.h"
#include "ModelTabWidget.h"
#include "ModelTableWidget.h"
#include "ModelTreeWidget.h"

Business* Business::business = NULL;
Business::Business()
{

}

Business *Business::getBusiness()
{
    if(business == NULL)
    {
        business = new Business();
    }
    return business;
}

ModelBase* Business::loadModelBase(QString fileName)
{
    QFileInfo fileinfo = QFileInfo(fileName);
    QString file_suffix = fileinfo.suffix();
    ModelBase* modelBase = NULL;
    if(file_suffix == "ram")
    {
        ModelRAM* modelObject = new ModelRAM;
        modelObject->loadFile(fileName);
        modelBase = modelObject;
    } else if(file_suffix == "rcs") {
        ModelRCS* modelObject = new ModelRCS;
        modelObject->loadFile(fileName);
        modelBase = modelObject;
    } else if(file_suffix == "rcsF" || file_suffix == "rcsf") {
        ModelRCSF* modelObject = new ModelRCSF;
        modelObject->loadFile(fileName);
        modelBase = modelObject;
    }
    if(modelBase)
    {
        modelObjects.push_back(modelBase);
    }
    return modelBase;
}

ModelTableWidget *Business::getModelTableWidget()
{
    return modelTableWidget;
}

void Business::setModelTableWidget(ModelTableWidget *value)
{
    modelTableWidget = value;
}

ModelTabWidget *Business::getModelTabWidget()
{
    return modelTabWidget;
}

void Business::setModelTabWidget(ModelTabWidget *value)
{
    modelTabWidget = value;
}

ModelTreeWidget *Business::getModelTreeWidget()
{
    return modelTreeWidget;
}

void Business::setModelTreeWidget(ModelTreeWidget *value)
{
    modelTreeWidget = value;
}

CurveShowAndSetWidget *Business::getCurveShowAndSetWidget()
{
    return curveShowAndSetWidget;
}

void Business::setCurveShowAndSetWidget(CurveShowAndSetWidget *value)
{
    curveShowAndSetWidget = value;
}

StepWidget *Business::getStepWidget()
{
    return stepWidget;
}

void Business::setStepWidget(StepWidget *value)
{
    stepWidget = value;
}

ViewForm *Business::getViewForm()
{
    return viewForm;
}

void Business::setViewForm(ViewForm *value)
{
    viewForm = value;
}

DateCountTabWidget *Business::getDateCountTabWidget()
{
    return dateCountTabWidget;
}

void Business::setDateCountTabWidget(DateCountTabWidget *value)
{
    dateCountTabWidget = value;
}

ViewFormRCS *Business::getViewFormRCS()
{
    return viewFormRCS;
}

void Business::setViewFormRCS(ViewFormRCS *value)
{
    viewFormRCS = value;
}

StatisticalAnalysisWidget *Business::getStatisticalAnalysisWidget()
{
   return statisticalAnalysisWidget;
}

void Business::setStatisticalAnalysisWidget(StatisticalAnalysisWidget *value)
{
    statisticalAnalysisWidget = value;
}

ViewFromHisgram *Business::getViewFromHisgram()
{
    return viewFromHisgram;
}

void Business::setViewFromHisgram(ViewFromHisgram *value)
{
    viewFromHisgram = value;
}
