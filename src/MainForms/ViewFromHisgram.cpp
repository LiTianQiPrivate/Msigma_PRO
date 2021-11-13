#include "ViewFromHisgram.h"
#include "ui_ViewFromHisgram.h"

ViewFromHisgram::ViewFromHisgram(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewFromHisgram)
{
    ui->setupUi(this);
    msigmaBase = new DrawHistogramChart(ui->widget);
}

ViewFromHisgram::~ViewFromHisgram()
{
    delete ui;
}

void ViewFromHisgram::resizeEvent(QResizeEvent *event)
{
    if(msigmaBase)
    {
        QWidget* currentWidget = dynamic_cast<QWidget*> (msigmaBase);
        currentWidget->setGeometry(0, 0, ui->widget->width(), ui->widget->height());
    }
}

void ViewFromHisgram::on_comboBox_2_activated(int index)
{
    if(index == 0)  // x->y
    {
        msigmaBase->setOrientation(0);
    }
    else if(index == 1) // y->x
    {
        msigmaBase->setOrientation(1);
    }
    else
    {
        return;
    }
}

void ViewFromHisgram::on_comboBox_3_activated(int index)
{
    if(index == 0)  // 柱
    {
        msigmaBase->setMode(0);
    }
    else if(index == 1) // 堆
    {
        msigmaBase->setMode(1);
    }
    else
    {
        return;
    }
}

void ViewFromHisgram::getValues(std::vector<std::vector<double> > values, std::vector<QString> strs, int index)
{
    QVector<QVector<double>> qValues;
    QVector<double> qValue;
    for(int i = 0;i<values.size();i++)
    {
        std::vector<double> value1 = values[i];
        for(int j=0;j<value1.size();j++)
        {
            double v = value1[j];
            qValue.push_back(v);
        }
        qValues.push_back(qValue);
        qValue.clear();
    }
    msigmaBase->getValues(qValues,strs);
    switch(index)
    {
        case 1:
            ui->label->setText(QString::fromLocal8Bit("各波段RCS均值"));
            break;
        case 2:
            ui->label->setText(QString::fromLocal8Bit("各波段RCS最大值"));
            break;
        case 3:
            ui->label->setText(QString::fromLocal8Bit("各波段RCS最小值"));
            break;
        case 4:
            ui->label->setText(QString::fromLocal8Bit("各波段RCS中值"));
            break;
    }
}
