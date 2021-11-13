#include "ViewFormRCS.h"
#include "ui_ViewFormRCS.h"
#include "CurvePlot.h"
#include "XYZWidget.h"
#include "DrawStatisicalCurve.h"

ViewFormRCS::ViewFormRCS(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewFormRCS)
{
    ui->setupUi(this);
    msigmaBase = new DrawStatisicalCurve(ui->widget);
}

ViewFormRCS::~ViewFormRCS()
{
    delete msigmaBase;
    delete ui;
}

void ViewFormRCS::addModelBase(ModelBase *modelBase)
{
    modelBases.push_back(modelBase);
    if(modelBase->getClassName() == "ModelRCSF")
    {
        XYZWidget xyzWidget;
        xyzWidget.setModelRCSF((ModelRCSF*)modelBase);
        xyzWidget.exec();
        if(xyzWidget.getIsOK())
        {
            ModelRCSF* model = (ModelRCSF*)modelBase;
            int xType;
            double value;
            xyzWidget.getReturn(xType, value);
            model->setXStype(xType);
            model->setCurrentValue(value);
        }
    }
    msigmaBase->setModelBases(modelBases,0);
    setLabel2Tetx(modelBase);
    setLabel3Tetx(modelBase);
    setLabel4Tetx(modelBase);
    setLabel5Tetx(modelBase);
    setLabel6Tetx(modelBase);
    setLabel7Tetx(modelBase);
    setLabel8Tetx(modelBase);
    QWidget* currentWidget = dynamic_cast<QWidget*> (msigmaBase);
    currentWidget->setGeometry(0, 0, ui->widget->width(), ui->widget->height());
    currentWidget->show();
}

void ViewFormRCS::resizeEvent(QResizeEvent *event)
{
    if(msigmaBase)
    {
        QWidget* currentWidget = dynamic_cast<QWidget*> (msigmaBase);
        currentWidget->setGeometry(0, 0, ui->widget->width(), ui->widget->height());
    }
}

void ViewFormRCS::setLabel2Tetx(ModelBase *modelBase)
{
    QString str = modelBase->findDataInfo(QString::fromLocal8Bit(TARGET_NAME));
    int number = 0;
    if(nameStr.size() > 0)
    {
        for(int i=0;i<nameStr.size();i++)
        {
            if(str != nameStr[i])
            {
                number++;
            }
            else
            {
                continue;
            }
        }
    }
    else
    {
        nameStr.push_back(str);
    }
    if(number == (nameStr.size()))
    {
        nameStr.push_back(str);
    }
    str = ("目标名称:")+nameStr[0];
    for(int i=1;i<nameStr.size();i++)
    {
        str = str + "," + nameStr[i];
    }
    ui->label_2->setText(str);
}

void ViewFormRCS::setLabel3Tetx(ModelBase *modelBase)
{
    QString str = modelBase->findDataInfo(QString::fromLocal8Bit(TARGET_PITCH_ANGLE));
    int number = 0;
    if(pitchStr.size() > 0)
    {
        for(int i=0;i<pitchStr.size();i++)
        {
            if(str != pitchStr[i])
            {
                number++;
            }
            else
            {
                continue;
            }
        }
    }
    else
    {
        pitchStr.push_back(str);
    }
    if(number == (pitchStr.size()))
    {
        pitchStr.push_back(str);
    }
    str = QString("俯仰角（°）：")+pitchStr[0];
    for(int i=1;i<pitchStr.size();i++)
    {
        str = str + "," + pitchStr[i];
    }
    ui->label_3->setText(str);
}

void ViewFormRCS::setLabel4Tetx(ModelBase *modelBase)
{
    QString str = modelBase->findDataInfo(QString::fromLocal8Bit(TARGET_ROLL_ANGLE));
    int number = 0;
    if(rollStr.size() > 0)
    {
        for(int i=0;i<rollStr.size();i++)
        {
            if(str != rollStr[i])
            {
                number++;
            }
            else
            {
                continue;
            }
        }
    }
    else
    {
        rollStr.push_back(str);
    }
    if(number == (rollStr.size()))
    {
        rollStr.push_back(str);
    }
    str = ("横滚角（°）：")+rollStr[0];
    for(int i=1;i<rollStr.size();i++)
    {
        str = str + "," + rollStr[i];
    }
    ui->label_4->setText(str);
}

void ViewFormRCS::setLabel5Tetx(ModelBase *modelBase)
{
    QString str = modelBase->findDataInfo(QString::fromLocal8Bit(POLARIZATION_COMBINATION));
    int number = 0;
    if(polarStr.size() > 0)
    {
        for(int i=0;i<polarStr.size();i++)
        {
            if(str != polarStr[i])
            {
                number++;
            }
            else
            {
                continue;
            }
        }
    }
    else
    {
        polarStr.push_back(str);
    }
    if(number == (polarStr.size()))
    {
        polarStr.push_back(str);
    }
    str = ("极化:")+polarStr[0];
    for(int i=1;i<polarStr.size();i++)
    {
        str = str + "," + polarStr[i];
    }
    ui->label_5->setText(str);
}

void ViewFormRCS::setLabel6Tetx(ModelBase *modelBase)
{
    QString str = modelBase->findDataInfo(QString::fromLocal8Bit(WORK_FPS));
    int number = 0;
    if(fpsStr.size() > 0)
    {
        for(int i=0;i<fpsStr.size();i++)
        {
            if(str != fpsStr[i])
            {
                number++;
            }
            else
            {
                continue;
            }
        }
    }
    else
    {
        fpsStr.push_back(str);
    }
    if(number == (fpsStr.size()))
    {
        fpsStr.push_back(str);
    }
    str = ("工作频率(GHz):")+fpsStr[0];
    for(int i=1;i<fpsStr.size();i++)
    {
        str = str + "," + fpsStr[i];
    }
    ui->label_6->setText(str);
}

void ViewFormRCS::setLabel7Tetx(ModelBase *modelBase)
{
    QString str = modelBase->findDataInfo(QString::fromLocal8Bit(MEASUREMENT_DATE));
    int number = 0;
    if( dataStr.size() > 0)
    {
        for(int i=0;i<dataStr.size();i++)
        {
            if(str != dataStr[i])
            {
                number++;
            }
            else
            {
                continue;
            }
        }
    }
    else
    {
        dataStr.push_back(str);
    }
    if(number == (dataStr.size()))
    {
        dataStr.push_back(str);
    }
    str = ("测量日期:")+dataStr[0];
    for(int i=1;i<dataStr.size();i++)
    {
        str = str + "," + dataStr[i];
    }
    ui->label_7->setText(str);
}

void ViewFormRCS::setLabel8Tetx(ModelBase *modelBase)
{
    QString str = modelBase->findDataInfo(QString::fromLocal8Bit(MEASURING));
    int number = 0;
    if(timeStr.size() > 0)
    {
        for(int i=0;i<timeStr.size();i++)
        {
            if(str != timeStr[i])
            {
                number++;
            }
            else
            {
                continue;
            }
        }
    }
    else
    {
        timeStr.push_back(str);
    }
    if(number == (timeStr.size()))
    {
        timeStr.push_back(str);
    }
    str = ("测试时间:")+timeStr[0];
    for(int i=1;i<timeStr.size();i++)
    {
        str = str + "," + timeStr[i];
    }
    ui->label_8->setText(str);
}

void ViewFormRCS::setTableWidgetStatistical(double x1, double x2, double x3, double x4)
{
    msigmaBase->drawStatisicalAnalysis(x1,x2,x3,x4);
}

void ViewFormRCS::clearDataValue()
{
    msigmaBase->clearDateVluess();
}

void ViewFormRCS::clearFillRect()
{
    msigmaBase->clearRect();
}

double ViewFormRCS::getXMin()
{
    return msigmaBase->getXMinValue();
}

double ViewFormRCS::getXMax()
{
    return msigmaBase->getXMaxValue();
}



