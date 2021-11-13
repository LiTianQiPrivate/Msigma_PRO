#include "AddCheckBox.h"
#include "ui_AddCheckBox.h"
#include<QDebug>
#include "Business.h"
#include "ModelTabWidget.h"
#include "ViewBase.h"
#include "CurveViewForm.h"
AddCheckBox::AddCheckBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddCheckBox)
{
    ui->setupUi(this);
}

AddCheckBox::~AddCheckBox()
{
    delete ui;
}

void AddCheckBox::addTypeData(datas data,int index)
{
    std::set<QString>::iterator iter;
    std::set<int>::iterator it = data.key.begin();
    int number = 0;
    m_currentIndex = index;
    for(int i = 0;i<checkBoxs1.size();i++)
    {
        delete checkBoxs1[i];
    }
    if(checkBoxs1.size()>0)
    {
        checkBoxs1.clear();
    }
    for(int i = 0;i<checkBoxs2.size();i++)
    {
        delete checkBoxs2[i];
    }
    if(checkBoxs2.size()>0)
    {
        checkBoxs2.clear();
    }
    for(int i = 0;i<checkBoxs3.size();i++)
    {
        delete checkBoxs3[i];
    }
    if(checkBoxs3.size()>0)
    {
        checkBoxs3.clear();
    }
    for(int i = 0;i<checkBoxs4.size();i++)
    {
        delete checkBoxs4[i];
    }
    if(checkBoxs4.size()>0)
    {
        checkBoxs4.clear();
    }
    for(int i = 0;i<checkBoxs5.size();i++)
    {
        delete checkBoxs5[i];
    }
    if(checkBoxs5.size()>0)
    {
        checkBoxs5.clear();
    }
    for(int i = 0;i<checkBoxs6.size();i++)
    {
        delete checkBoxs6[i];
    }
    if(checkBoxs6.size()>0)
    {
        checkBoxs6.clear();
    }
    for(int i = 0;i<checkBoxs7.size();i++)
    {
        delete checkBoxs7[i];
    }
    if(checkBoxs7.size()>0)
    {
        checkBoxs7.clear();
    }
    for(int i = 0;i<checkBoxs8.size();i++)
    {
        delete checkBoxs8[i];
    }
    if(checkBoxs8.size()>0)
    {
        checkBoxs8.clear();
    }
    if(data.key.size() > 0 )
    {
        for (it = data.key.begin();it != data.key.end();it++)
        {
            switch(*it)
            {
            case 1:  // 添加曲线类型checkBox
                number = 0;
                for (iter = data.value1.begin();iter != data.value1.end();iter++)
                {
                    if(*iter != "")
                    {
                        QCheckBox *checkBox = new QCheckBox(*iter,this);
                        QHBoxLayout* layout = ui->horizontalLayout;
                        checkBox->setCheckState(Qt::Checked);
                        layout->setMargin(0);
                        layout->insertWidget(number, checkBox);
                        ui->widget->setLayout(layout);
                        checkBoxs1.push_back(checkBox);
                        number++;
                        connect(checkBox,SIGNAL(clicked(bool)),this,SLOT(on_chickCheckBox(bool)));
                    }
                }
                break;
            case 2:  // 添加目标名称checkBox
                number = 0;
                for (iter = data.value2.begin();iter != data.value2.end();iter++)
                {
                    if(*iter != "")
                    {
                        QCheckBox *checkBox = new QCheckBox(*iter,this);
                        QHBoxLayout* layout = ui->horizontalLayout_2;
                        checkBox->setCheckState(Qt::Checked);
                        layout->setMargin(0);
                        layout->insertWidget(number, checkBox);
                        ui->widget_2->setLayout(layout);
                        checkBoxs2.push_back(checkBox);
                        number++;
                        connect(checkBox,SIGNAL(clicked(bool)),this,SLOT(on_chickCheckBox(bool)));
                    }
                }
                break;
            case 3:  // 添加目标说明checkBox
                number = 0;
                for (iter = data.value3.begin();iter != data.value3.end();iter++)
                {
                    if(*iter != "")
                    {
                        QCheckBox *checkBox = new QCheckBox(*iter,this);
                        QHBoxLayout* layout = ui->horizontalLayout_3;
                        checkBox->setCheckState(Qt::Checked);
                        layout->setMargin(0);
                        layout->insertWidget(number, checkBox);
                        ui->widget_3->setLayout(layout);
                        checkBoxs3.push_back(checkBox);
                        number++;
                        connect(checkBox,SIGNAL(clicked(bool)),this,SLOT(on_chickCheckBox(bool)));
                    }
                }
                break;
            case 4:  // 添加极化方式checkBox
                number = 0;
                for (iter = data.value4.begin();iter != data.value4.end();iter++)
                {
                    if(*iter != "")
                    {
                        QCheckBox *checkBox = new QCheckBox(*iter,this);
                        QHBoxLayout* layout = ui->horizontalLayout_4;
                        checkBox->setCheckState(Qt::Checked);
                        layout->setMargin(0);
                        layout->insertWidget(number, checkBox);
                        ui->widget_4->setLayout(layout);
                        checkBoxs4.push_back(checkBox);
                        number++;
                        connect(checkBox,SIGNAL(clicked(bool)),this,SLOT(on_chickCheckBox(bool)));
                    }
                }
                break;
            case 5:  // 添加俯仰角checkBox
                number = 0;
                for (iter = data.value5.begin();iter != data.value5.end();iter++)
                {
                    if(*iter != "")
                    {
                        QCheckBox *checkBox = new QCheckBox(*iter,this);
                        QHBoxLayout* layout = ui->horizontalLayout_5;
                        checkBox->setCheckState(Qt::Checked);
                        layout->setMargin(0);
                        layout->insertWidget(number, checkBox);
                        ui->widget_5->setLayout(layout);
                        checkBoxs5.push_back(checkBox);
                        number++;
                        connect(checkBox,SIGNAL(clicked(bool)),this,SLOT(on_chickCheckBox(bool)));
                    }
                }
                break;
            case 6:  // 添加横滚角checkBox
                number = 0;
                for (iter = data.value6.begin();iter != data.value6.end();iter++)
                {
                    if(*iter != "")
                    {
                        QCheckBox *checkBox = new QCheckBox(*iter,this);
                        QHBoxLayout* layout = ui->horizontalLayout_6;
                        checkBox->setCheckState(Qt::Checked);
                        layout->setMargin(0);
                        layout->insertWidget(number, checkBox);
                        checkBoxs6.push_back(checkBox);
                        number++;
                        connect(checkBox,SIGNAL(clicked(bool)),this,SLOT(on_chickCheckBox(bool)));
                    }
                }
                break;
            case 7:  // 添加频率checkbox
                number = 0;
                for (iter = data.value7.begin();iter != data.value7.end();iter++)
                {
                    if(*iter != "")
                    {
                        QCheckBox *checkBox = new QCheckBox(*iter,this);
                        QHBoxLayout* layout = ui->horizontalLayout_7;
                        checkBox->setCheckState(Qt::Checked);
                        layout->setMargin(0);
                        layout->insertWidget(number, checkBox);
                        checkBoxs7.push_back(checkBox);
                        number++;
                        connect(checkBox,SIGNAL(clicked(bool)),this,SLOT(on_chickCheckBox(bool)));
                    }
                }
                break;
            case 8:  // 添加方位checkBox
                number = 0;
                for (iter = data.value8.begin();iter != data.value8.end();iter++)
                {
                    if(*iter != "")
                    {
                        QCheckBox *checkBox = new QCheckBox(*iter,this);
                        QHBoxLayout* layout = ui->horizontalLayout_8;
                        checkBox->setCheckState(Qt::Checked);
                        layout->setMargin(0);
                        layout->insertWidget(number, checkBox);
                        checkBoxs8.push_back(checkBox);
                        number++;
                        connect(checkBox,SIGNAL(clicked(bool)),this,SLOT(on_chickCheckBox(bool)));
                    }
                }
                break;
            default:
                break;
            }
        }
    }
}
std::set<QString> AddCheckBox::getClickButton()
{
    for(int i = 0; i < checkBoxs1.size(); i++)
    {

    }
    return values;
}

void AddCheckBox::on_chickCheckBox(bool v)
{
    std::vector<ModelBase *>base = Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->getModelBase();
    for(int i = 0;i < base.size(); i++)
    {
        base[i]->setShowHideFlag(true);
    }
    for(int i=0;i<checkBoxs1.size();i++)
    {
        if(checkBoxs1[i]->checkState() == Qt::Unchecked)
        {
            for (int j = 0;j<base.size();j++)
            {
                 if(base[j]->findDataInfo(QString::fromLocal8Bit(DATA_TYPE)) == checkBoxs1[i]->text())
                {
                    base[j]->setShowHideFlag(false);
                 }
            }
        }
    }
    for(int i=0;i<checkBoxs2.size();i++)
    {
        if(checkBoxs2[i]->checkState() == Qt::Unchecked)
        {
            for (int j = 0;j<base.size();j++)
            {
                 if(base[j]->findDataInfo(QString::fromLocal8Bit(TARGET_NAME)) == checkBoxs2[i]->text())
                {
                    base[j]->setShowHideFlag(false);
                 }
            }
        }
    }
    for(int i=0;i<checkBoxs3.size();i++)
    {
        if(checkBoxs3[i]->checkState() == Qt::Unchecked)
        {
            for (int j = 0;j<base.size();j++)
            {
                 if(base[j]->findDataInfo(QString::fromLocal8Bit(TARGET_EXPLAIN)) == checkBoxs3[i]->text())
                {
                    base[j]->setShowHideFlag(false);
                 }
            }
        }
    }
    for(int i=0;i<checkBoxs4.size();i++)
    {
        if(checkBoxs4[i]->checkState() == Qt::Unchecked)
        {
            for (int j = 0;j<base.size();j++)
            {
                 if(base[j]->findDataInfo(QString::fromLocal8Bit(POLARIZATION_COMBINATION)) == checkBoxs4[i]->text())
                {
                    base[j]->setShowHideFlag(false);
                 }
            }
        }
    }
    for(int i=0;i<checkBoxs5.size();i++)
    {
        if(checkBoxs5[i]->checkState() == Qt::Unchecked)
        {
            for (int j = 0;j<base.size();j++)
            {
                 if(base[j]->findDataInfo(QString::fromLocal8Bit(TARGET_PITCH_ANGLE)) == checkBoxs5[i]->text())
                {
                    base[j]->setShowHideFlag(false);
                 }
            }
        }
    }
    for(int i=0;i<checkBoxs6.size();i++)
    {
        if(checkBoxs6[i]->checkState() == Qt::Unchecked)
        {
            for (int j = 0;j<base.size();j++)
            {
                 if(base[j]->findDataInfo(QString::fromLocal8Bit(TARGET_ROLL_ANGLE)) == checkBoxs6[i]->text())
                {
                    base[j]->setShowHideFlag(false);
                 }
            }
        }
    }
    for(int i=0;i<checkBoxs7.size();i++)
    {
        if(checkBoxs7[i]->checkState() == Qt::Unchecked)
        {
            for (int j = 0;j<base.size();j++)
            {
                 if(base[j]->findDataInfo(QString::fromLocal8Bit(WORK_FPS)) == checkBoxs7[i]->text())
                {
                    base[j]->setShowHideFlag(false);
                 }
            }
        }
    }
    for(int i=0;i<checkBoxs8.size();i++)
    {
        if(checkBoxs8[i]->checkState() == Qt::Unchecked)
        {
            for (int j = 0;j<base.size();j++)
            {
                 if(base[j]->findDataInfo(QString::fromLocal8Bit(INCIDENT_ANGLE)) == checkBoxs8[i]->text())
                {
                    base[j]->setShowHideFlag(false);
                 }
            }
        }
    }
    Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->updataTableWidgetItem(base);
}
