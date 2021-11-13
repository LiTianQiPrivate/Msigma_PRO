#include "CurveShowAndSetWidget.h"
#include "ui_CurveShowAndSetWidget.h"
#include "Business.h"
#include "ModelTabWidget.h"
#include "CurveViewForm.h"
#include <set>
#include <qDebug>
#include <QMessageBox>
#include <QDoubleValidator>
#include <QToolBar>

CurveShowAndSetWidget::CurveShowAndSetWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CurveShowAndSetWidget)
{
    ui->setupUi(this);
    m_currentIndex = 0;
    QHBoxLayout* layout1 = new QHBoxLayout;
    QToolBar toolBar;
    QAction action;
    action.setText("ahahahah");
    toolBar.addAction(&action);
    //toolBar.setMinimumSize(30,30);
    layout1->addWidget(&toolBar);
    layout1->addLayout(ui->horizontalLayout_7);
    layout1->setMargin(0);
    layout1->addWidget(this);
    ui->groupBox_4->setLayout(layout1);
    addCheckBox = new AddCheckBox(this);
    QHBoxLayout* layout = ui->horizontalLayout_3;
    layout->setMargin(0);
    layout->addWidget(addCheckBox);
    ui->widget_check->setLayout(layout);
    //ui->radioButton->setEnabled(true);
}

CurveShowAndSetWidget::~CurveShowAndSetWidget()
{
    delete ui;
}

void CurveShowAndSetWidget::on_comboBox_7_currentIndexChanged(int index)
{
    m_currentIndex = ui->comboBox_7->currentIndex();
    setCheckBox(m_modelBases[m_currentIndex],m_currentIndex);
}

void CurveShowAndSetWidget::getModelBase(std::vector<ModelBase *>modelBases, int index)
{
    for (int i = 0;i<modelBases.size();i++)
    {
        m_modelBases[index].push_back(modelBases[i]);
    }
    // 当添加的modelBase与此时显示的comboBox为一个时 进行CheckBox刷新 否则当comboBox改变时在进行刷新
    if(index == m_currentIndex)
    {
        setCheckBox(m_modelBases[index],m_currentIndex);   // 初始化默认
    }
}
void CurveShowAndSetWidget::on_comboBox_9_activated(int index)
{
    Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->setLegendName(index);
}

void CurveShowAndSetWidget::setCheckBox(std::vector<ModelBase *>modelBases, int index)
{
    datas data;
    for(int i=0;i<modelBases.size();i++)
    {
        ModelBase *m_modelBase = modelBases[i];

        QString dataType = m_modelBase->findDataInfo(QString::fromLocal8Bit(DATA_TYPE));
        data.key.insert(1);
        data.value1.insert(dataType);

        QString targeName = m_modelBase->findDataInfo(QString::fromLocal8Bit(TARGET_NAME));
        data.key.insert(2);
        data.value2.insert(targeName);

        QString explain = m_modelBase->findDataInfo(QString::fromLocal8Bit(TARGET_EXPLAIN));
        data.key.insert(3);
        data.value3.insert(explain);

        QString polar = m_modelBase->findDataInfo(QString::fromLocal8Bit(POLARIZATION_COMBINATION));
        data.key.insert(4);
        data.value4.insert(polar);

        QString pitch = m_modelBase->findDataInfo(QString::fromLocal8Bit(TARGET_PITCH_ANGLE));
        data.key.insert(5);
        data.value5.insert(pitch);

        QString roll = m_modelBase->findDataInfo(QString::fromLocal8Bit(TARGET_ROLL_ANGLE));
        data.key.insert(6);
        data.value6.insert(roll);

        QString fps = m_modelBase->findDataInfo(QString::fromLocal8Bit(WORK_FPS));
        data.key.insert(7);
        data.value7.insert(fps);

        QString incid = m_modelBase->findDataInfo(QString::fromLocal8Bit(INCIDENT_ANGLE));
        data.key.insert(8);
        data.value8.insert(incid);
    }
    addCheckBox->addTypeData(data,index);
}
/**
 * @brief CurveShowAndSetWidget::on_pushButton_clicked
 * y 轴填充面积显示
 * @param checked
 */
void CurveShowAndSetWidget::on_pushButton_clicked(bool checked)
{
    double y1 = ui->lineEdit_10->text().toDouble();
    double y2 = ui->lineEdit_11->text().toDouble();
    std::vector<ModelBase *>base = Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->getModelBase();
    Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->setRibbon(true,y1,y2);
    Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->updataTableWidgetItem(base);
}
/**
 * @brief CurveShowAndSetWidget::on_pushButton_2_clicked
 * 取消y轴  填充色带
 * @param checked
 */
void CurveShowAndSetWidget::on_pushButton_2_clicked(bool checked)
{
    std::vector<ModelBase *>base = Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->getModelBase();
    Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->setRibbon(false,0.0,0.0);
    Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->updataTableWidgetItem(base);
}
/**
 * @brief CurveShowAndSetWidget::on_pushButton_3_clicked
 * y轴添加曲线显示
 * @param checked
 */
void CurveShowAndSetWidget::on_pushButton_3_clicked(bool checked)
{
    double y1 = ui->lineEdit_10->text().toDouble();
    //double y2 = ui->lineEdit_11->text().toDouble();
    std::vector<ModelBase *>base = Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->getModelBase();
    Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->setRibbon(true,y1,0.0);
    Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->updataTableWidgetItem(base);
}
/**
 * @brief CurveShowAndSetWidget::on_pushButton_5_clicked
 * X轴填充色带
 * @param checked
 */
void CurveShowAndSetWidget::on_pushButton_5_clicked(bool checked)
{
    std::vector<ModelBase *>base = Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->getModelBase();
    double x1 = ui->lineEdit_13->text().toDouble();
    double x2 = ui->lineEdit_14->text().toDouble();
    Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->setXRibbon(true,x1,x2);
    Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->updataTableWidgetItem(base);
}
/**
 * @brief CurveShowAndSetWidget::on_pushButton_6_clicked
 * 取消X轴填充色带
 * @param checked
 */
void CurveShowAndSetWidget::on_pushButton_6_clicked(bool checked)
{
    std::vector<ModelBase *>base = Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->getModelBase();
    Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->setXRibbon(false,0.0,0.0);
    Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->setXBackRibbon(false,0.0,0.0);
    Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->updataTableWidgetItem(base);
}
/**
 * @brief CurveShowAndSetWidget::on_pushButton_7_clicked
 * x轴反向填充
 * @param checked
 */
void CurveShowAndSetWidget::on_pushButton_7_clicked(bool checked)
{
    std::vector<ModelBase *>base = Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->getModelBase();
    double x1 = ui->lineEdit_13->text().toDouble();
    double x2 = ui->lineEdit_14->text().toDouble();
    Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->setXBackRibbon(true,x1,x2);
    Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->updataTableWidgetItem(base);
}
/**
 * @brief CurveShowAndSetWidget::on_pushButton_9_clicked
 *   门限点添加函数
 * @param checked
 */
void CurveShowAndSetWidget::on_pushButton_9_clicked(bool checked)
{
    // new初始化时填入第几个窗口的参数
    dot = new AddThresholdDot(m_currentIndex);
    dot->show();
}
/**
 * @brief CurveShowAndSetWidget::on_pushButton_10_clicked
 * 取消门限点显示
 * @param checked
 */
void CurveShowAndSetWidget::on_pushButton_10_clicked(bool checked)
{
    std::vector<QPointF> point;
    std::vector<ModelBase *>base = Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->getModelBase();
    Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->setThresholdDot(point);
    Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->updataTableWidgetItem(base);
}
/**
 * @brief CurveShowAndSetWidget::on_pushButton_11_clicked
 * 设置X轴范围
 * @param checked
 */
void CurveShowAndSetWidget::on_pushButton_11_clicked(bool checked)
{
    double xMin = ui->lineEdit_4->text().toDouble();
    double xMax = ui->lineEdit_5->text().toDouble();
    double xstep = ui->lineEdit_6->text().toDouble();
    Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->getMsigmaBase()->setAxisX(xMin,xMax,xstep);
}
/**
 * @brief CurveShowAndSetWidget::on_pushButton_12_clicked
 * 设置y轴范围
 * @param checked
 */
void CurveShowAndSetWidget::on_pushButton_12_clicked(bool checked)
{
    double yMin = ui->lineEdit_9->text().toDouble();
    double yMax = ui->lineEdit_7->text().toDouble();
    double ystep = ui->lineEdit_8->text().toDouble();
    Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->getMsigmaBase()->setAxisY(yMin,yMax,ystep);
}
/**
 * @brief CurveShowAndSetWidget::on_pushButton_18_clicked
 * 点可见性
 * @param checked
 */
void CurveShowAndSetWidget::on_pushButton_18_clicked(bool checked)
{
    if(Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->modelBases.empty())
    {
        QMessageBox::warning(NULL,"warning",("请选择需要加载的曲线"),QMessageBox::Yes);
        return ;
    }
    if(ui->pushButton_18->text() == "dots")
    {
        ui->pushButton_18->setText("X");
        Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->getMsigmaBase()->on_checkBoxPointClick(true);
    }
    else
    {
        ui->pushButton_18->setText("dots");
        Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->getMsigmaBase()->on_checkBoxPointClick(false);
    }

}
/**
 * @brief CurveShowAndSetWidget::on_pushButton_13_clicked
 * 极小值
 * @param checked
 */
void CurveShowAndSetWidget::on_pushButton_13_clicked(bool checked)
{
    if(Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->modelBases.empty())
    {
        QMessageBox::warning(NULL,"warning",("请选择需要加载的曲线"),QMessageBox::Yes);
        return ;
    }
    if(ui->pushButton_13->text() == "min")
    {
        ui->pushButton_13->setText("X");
        Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->getMsigmaBase()->on_checkMinBoxPointClick(true);
    }
    else
    {
        ui->pushButton_13->setText("min");
        Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->getMsigmaBase()->on_checkMinBoxPointClick(false);
    }
}
/**
 * @brief CurveShowAndSetWidget::on_pushButton_14_clicked
 * 极大值
 * @param checked
 */
void CurveShowAndSetWidget::on_pushButton_14_clicked(bool checked)
{
    if(Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->modelBases.empty())
    {
        QMessageBox::warning(NULL,"warning",("请选择需要加载的曲线"),QMessageBox::Yes);
        return ;
    }
    if(ui->pushButton_14->text() == "max")
    {
        ui->pushButton_14->setText("X");
        Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->getMsigmaBase()->on_checkMaxBoxPointClick(true);
    }
    else
    {
        ui->pushButton_14->setText("max");
        Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->getMsigmaBase()->on_checkMaxBoxPointClick(false);
    }
}
/**
 * @brief CurveShowAndSetWidget::on_pushButton_15_clicked
 * 曲线翻转
 * @param checked
 */
void CurveShowAndSetWidget::on_pushButton_15_clicked(bool checked)
{
    if(Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->modelBases.empty())
    {
        QMessageBox::warning(NULL,"warning",("请选择需要加载的曲线"),QMessageBox::Yes);
        return ;
    }
    if(ui->pushButton_15->text() == "turn")
    {
        ui->pushButton_15->setText("X");
        Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->getMsigmaBase()->on_checkTurnBoxPointClick(true);
    }
    else
    {
        ui->pushButton_15->setText("turn");
        Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->getMsigmaBase()->on_checkTurnBoxPointClick(false);
    }
}
/**
 * @brief CurveShowAndSetWidget::on_pushButton_16_clicked
 * 单曲线选取
 * @param checked
 */
void CurveShowAndSetWidget::on_pushButton_16_clicked(bool checked)
{
    if(Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->modelBases.empty())
    {
        QMessageBox::warning(NULL,"warning",QString::fromLocal8Bit("请选择需要加载的曲线"),QMessageBox::Yes);
        return ;
    }
    if(ui->pushButton_16->text() == "one")
    {
        ui->pushButton_16->setText("X");
        Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->getMsigmaBase()->on_checkCurveSelectClick(true);
    }
    else
    {
        ui->pushButton_16->setText("one");
        Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->getMsigmaBase()->on_checkCurveSelectClick(false);
    }
}
/**
 * @brief CurveShowAndSetWidget::on_pushButton_17_clicked
 * 多曲线选取
 * @param checked
 */
void CurveShowAndSetWidget::on_pushButton_17_clicked(bool checked)
{
    if(Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->modelBases.empty())
    {
        QMessageBox::warning(NULL,"warning",("请选择需要加载的曲线"),QMessageBox::Yes);
        return ;
    }
    if(ui->pushButton_17->text() == "many")
    {
        ui->pushButton_17->setText("X");
        Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->getMsigmaBase()->on_checkManyCurveSelectClick(true);
    }
    else
    {
        ui->pushButton_17->setText("many");
        Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->getMsigmaBase()->on_checkManyCurveSelectClick(false);
    }
}
/**
 * @brief CurveShowAndSetWidget::on_comboBox_8_activated
 * 曲线线宽设置
 * @param index
 */
void CurveShowAndSetWidget::on_comboBox_8_activated(int index)
{
    Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->getMsigmaBase()->setPenWidth(index+1);
    Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->updataTableWidgetItem(m_modelBases[m_currentIndex]);
}
/**
 * @brief CurveShowAndSetWidget::on_radioButton_clicked
 * 背景的显示与隐藏
 * @param checked
 */
void CurveShowAndSetWidget::on_radioButton_clicked(bool checked)
{
    Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->getMsigmaBase()->setGridState(checked);
}

void CurveShowAndSetWidget::on_comboBox_6_activated(int index)
{
    Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(m_currentIndex)->getMsigmaBase()->setBackGroupLightDark(index);

}
