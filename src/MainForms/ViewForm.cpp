#include "ViewForm.h"
#include "ui_ViewForm.h"
#include "QHBoxLayout"
#include "XYZWidget.h"
#include "QMenu"
#include "CurvePlot.h"
#include "SpectrogramPlotWidget.h"
#include "PolarCoordWidget.h"
#include "AreaChartWidget.h"
#include "HistogramChart.h"
#include "SplashesChart.h"
#include "WaterfallWidget.h"
#include "Curve3DWidget.h"
#include "CandleChartWidget.h"
#include "PolarChart2DWidget.h"
#include "TwoCruvePlot.h"
#include "IsoheightWidget.h"
#include <QDebug>
#include "Business.h"
#include "CurveShowAndSetWidget.h"
#include "SetCruveDialog.h"
#include "KeyText.h"
#include "QwtTwoCruvePlot.h"
#include "QwtBarChart.h"
#include "QwtCandleChart.h"
#include <QMessageBox>
#include <QStylePainter>

ViewForm::ViewForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewForm)
{


    ui->setupUi(this);
    setCurrentQWT(0);

    ui->tableWidget->setColumnCount(tableColumn);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setVisible(false);
//    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->setShowGrid(false);

}

ViewForm::~ViewForm()
{
    delete ui;
    if(msigmaBase)
    {
        delete msigmaBase;
    }
}

void ViewForm::resizeEvent(QResizeEvent *event)
{
    if(msigmaBase)
    {
        QWidget* currentWidget = dynamic_cast<QWidget*> (msigmaBase);
        currentWidget->setGeometry(0, 0, ui->widget->width(), ui->widget->height());
    }
}

void ViewForm::addModelBase(ModelBase *modelBase)
{
    modelBases.push_back(modelBase);
    //msigmaBase->modelBases.push_back(modelBase);
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
    ui->comboBox->setCurrentIndex(0);
    setCurrentQWT(0);
}

void ViewForm::setCurrentQWT(int index)
{
    if(msigmaBase)
    {
        delete msigmaBase;
        msigmaBase = NULL;
    }
    if(index == 0) // 一维曲线图
    {
        msigmaBase = new CurvePlot(ui->widget);
    } else if(index == 1) { // 二维面积图
        msigmaBase = new AreaChartWidget(ui->widget);
    } else if(index == 2) { // 二维柱状图
        msigmaBase = new QwtBarChart(ui->widget);
    } else if(index == 3) { // 二维散点图
        msigmaBase = new SplashesChart(ui->widget);
    } else if(index == 4) { // 蜡烛图
        msigmaBase = new QwtCandleChart(ui->widget);
    } else if(index == 5){ // 二维曲线图
        msigmaBase = new QwtTwoCruvePlot(ui->widget);
    }else if(index == 6){ // 二维极坐标图
        msigmaBase = new PolarChart2DWidget(ui->widget);
    } else if(index == 7){ // 二维色板图
        msigmaBase = new SpectrogramPlotWidget(ui->widget);
    } else if(index == 8){ // 三维极坐标图
        msigmaBase = new PolarCoordWidget(ui->widget);
    }else if(index == 9){ // 三维瀑布图
        msigmaBase = new WaterfallWidget(ui->widget);
    }else if(index == 10){ // 三维曲线图
        msigmaBase = new Curve3DWidget(ui->widget);
    }else if(index == 11){ // 等高线
        msigmaBase = new IsoheightWidget(ui->widget);
    }else {
        return ;
    }
    msigmaBase->setModelBasesFlag(modelBases);
    if(modelBases.size() > 0)
    {
        updataTableWidgetItem(modelBases);
    }
}
/**
 * @brief ViewForm::updataTableWidgetItem
 * tableWidget刷新函数  modelBase为存储所有数据 base为临时存储左侧列表筛选后的数据
 * modelBase为显示的数据未删除  只做单纯的hide  选中后进行show
 * @param base
 */
void ViewForm::updataTableWidgetItem(std::vector<ModelBase *>base)
{
    msigmaBase->updataView();
    int rowCount = ui->tableWidget->rowCount();
    for(int i = 0; i < rowCount; i++)
    {
        ui->tableWidget->removeRow(0);
    }

    ui->tableWidget->setColumnCount(tableColumn);
    ui->tableWidget->insertRow(0);
    if(ribbonXBackFlag && (ui->comboBox->currentIndex() == 0))
    {
        // 同意界面上数据 y轴范围相同 传一组数据即可
        for(int i= 0 ;i<base.size();i++)
        {
            msigmaBase->drawXBackRiboonCruve(base[i],leftBackVertical,rightBackVertical,true);
        }
    }
    else if(ui->comboBox->currentIndex() == 0)
    {
        for(int i= 0 ;i<base.size();i++)
        {
            msigmaBase->drawXBackRiboonCruve(base[i],leftBackVertical,rightBackVertical,false);
        }
    }
    if(ribbonXFlag && (ui->comboBox->currentIndex() == 0))
    {
        // 同意界面上数据 y轴范围相同 传一组数据即可
        for(int i= 0 ;i<base.size();i++)
        {
            msigmaBase->drawXRiboonCruve(base[i],leftVertical,rightVertical,true);
        }
    }
    else if(ui->comboBox->currentIndex() == 0)
    {
        for(int i= 0 ;i<base.size();i++)
        {
            msigmaBase->drawXRiboonCruve(base[i],leftVertical,rightVertical,false);
        }
    }
    if(ribbonFlag && (ui->comboBox->currentIndex() == 0))
    {
        // 同意界面上数据 y轴范围相同 传一组数据即可
        for(int i= 0 ;i<base.size();i++)
        {
            msigmaBase->drawRibbonCruve(base[i],upDouble,downDouble,true);
        }  
    }
    else if(ui->comboBox->currentIndex() == 0)
    {
        for(int i= 0 ;i<base.size();i++)
        {
            msigmaBase->drawRibbonCruve(base[i],upDouble,downDouble,false);
        }

    }
    if(thresholdDotFlag && (ui->comboBox->currentIndex() == 0))
    {
        msigmaBase->drawThresholdDotCruve(dots,true);
        dots.clear();  //  添加完一次之后删除
    }
    else if(ui->comboBox->currentIndex() == 0)
    {
        msigmaBase->drawThresholdDotCruve(dots,false);
    }

    msigmaBase->setModelBases(base,number);
    QWidget* currentWidget = dynamic_cast<QWidget*> (msigmaBase);
    currentWidget->setGeometry(0, 0, ui->widget->width(), ui->widget->height());
    currentWidget->show();
    int row = 0; // 当前行
    int column = 0; // 当前列
    for(int i = 0; i < base.size(); i++)
    {
        ModelBase* modelBase = base[i];
        if(modelBase->getShowHideFlag())
        {
            if(column >= tableColumn)
            {
                column = 0;
                row++;
                ui->tableWidget->insertRow(row);
            }
            QTableWidgetItem* item = new QTableWidgetItem(modelBase->FileName());
            item->setTextColor(modelBase->getColor());
            if(msigmaBase->isVisible(i))
            {
                item->setCheckState(Qt::Checked);
            } else {
                item->setCheckState(Qt::Unchecked);
            }
            ui->tableWidget->setItem(row,column,item);
            column++;
            if(msigmaBase)
            {
                msigmaBase->showModelBase(i);
            }
        }
        else
        {
            if(msigmaBase)
            {
                msigmaBase->hideModelBase(i);
            }
        }
    }
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();
}

void ViewForm::setXBackRibbon(bool v, double x1, double x2)
{
    ribbonXBackFlag = v;
    if(v)
    {
        ribbonXFlag = false;
    }
    leftBackVertical = x1;
    rightBackVertical = x2;
}

void ViewForm::setXRibbon(bool v, double x1, double x2)
{
    ribbonXFlag = v;
    if(v)
    {
        ribbonXBackFlag = false;
    }
    leftVertical = x1;
    rightVertical = x2;
}

void ViewForm::setRibbon(bool v, double y1, double y2)
{
    ribbonFlag = v;
    if(y1 > y2)
    {
        upDouble = y1;
        downDouble = y2;
    }
    else
    {
        upDouble = y2;
        downDouble = y1;
    }
}

bool ViewForm::setThresholdDot(std::vector<QPointF> dot)
{
    if(dot.size() > 0)
    {
        dots = dot;
        return thresholdDotFlag = true;
    }
    return false;
}

void ViewForm::setLegendName(int index)
{
    for(int i = 0; i< modelBases.size();i++)
    {
        ModelBase *m_modelBase = modelBases[i];
        if(m_modelBase->getShowHideFlag())
        {
            QString dataType = "";
            switch(index)
            {
            case 0:
                dataType = m_modelBase->findDataInfo(QString::fromLocal8Bit(DATA_TYPE));
                break;
            case 1:
                dataType = m_modelBase->findDataInfo(QString::fromLocal8Bit(TARGET_NAME));
                break;
            case 2:
                dataType = m_modelBase->findDataInfo(QString::fromLocal8Bit(TARGET_EXPLAIN));
                break;
            case 3:
                dataType = m_modelBase->findDataInfo(QString::fromLocal8Bit(POLARIZATION_COMBINATION));
                break;
            case 4:
                dataType = m_modelBase->findDataInfo(QString::fromLocal8Bit(TARGET_PITCH_ANGLE));
                break;
            case 5:
                dataType = m_modelBase->findDataInfo(QString::fromLocal8Bit(TARGET_ROLL_ANGLE));
                break;
            case 6:
                dataType = m_modelBase->findDataInfo(QString::fromLocal8Bit(WORK_FPS));
                break;
            case 7:
                dataType = m_modelBase->findDataInfo(QString::fromLocal8Bit(INCIDENT_ANGLE));
                break;
            default:
                break;
            }
            if(dataType != "")
            {
                m_modelBase->setFileName(dataType);
            }
            else
            {
                m_modelBase->setFileName(m_modelBase->oriFileName);
            }
        }
    }
    updataTableWidgetItem(modelBases);
}

void ViewForm::setComboxHide()
{
    ui->comboBox->hide();
}

void ViewForm::on_deleteaction_triggered()
{
    if(msigmaBase == NULL)
    {
        return;
    }
    int row = ui->tableWidget->currentRow();
    int column = ui->tableWidget->currentColumn();
    QTableWidgetItem* item = ui->tableWidget->item(row, column);
    if(item)
    {
        int number1 = row*tableColumn + column;
        modelBases.erase(modelBases.begin() + number1);
        msigmaBase->removeModelBase(number1);
        updataTableWidgetItem(modelBases);
    }
}

void ViewForm::on_tableWidget_customContextMenuRequested(const QPoint &pos)
{
    if(ui->tableWidget->item(0,0) == 0)
    {
        return ;
    }
    int row = ui->tableWidget->currentRow();
    int column = ui->tableWidget->currentColumn();
    QTableWidgetItem *item = ui->tableWidget->item(row,column);
    if(!item)    //  防止当 点击空的位置时  鼠标右键槽函数无法响应  会异常崩溃问题
    {
        return ;
    }
    QString str = modelBases[row*tableColumn+column]->getClassName();
    if(str == "ModelRCSF")
    {
        QMenu menu;
        menu.addAction(ui->deleteaction);
        menu.addSeparator();
        QMenu menu1 ;
        menu1.setTitle(QStringLiteral("曲线显示"));
        menu1.addAction(ui->curve);
        menu1.addAction(ui->dashed);
        menu1.addAction(ui->pillar);
        menu1.addAction(ui->ladder);
        menu1.addAction(ui->hideaction);
        //menu1.setToolTipsVisible(true);
        menu.addMenu(&menu1);
        menu.addSeparator();
        menu.addAction(ui->setaction);
        menu.exec(QCursor::pos());
    }
    else
    {
        QMenu menu;
        menu.addAction(ui->deleteaction);
        menu.addAction(ui->curve);
        menu.addAction(ui->dashed);
        menu.addAction(ui->pillar);
        menu.addAction(ui->ladder);
        menu.addAction(ui->hideaction);
        menu.exec(QCursor::pos());
    }
}

void ViewForm::on_tableWidget_cellClicked(int row, int column)
{
    int number = 3*(column+1)+row;
    if(number > modelBases.size())
    {
        return ;
    }
    int index = ui->comboBox->currentIndex();
    if(index == 4 || index == 5 || index == 6 || index == 7
            || index == 8 || index == 9 || index == 10 || index == 11) // 这几种图形不支持多条显示
    {
        for(int i = 0; i < ui->tableWidget->columnCount(); i++)
        {
            for(int j = 0; j < ui->tableWidget->rowCount(); j++)
            {
                QTableWidgetItem* item = ui->tableWidget->item(j, i);
                if(!item)
                {
                    continue;
                }
                if(j == row && i == column)
                {
                    item->setCheckState(Qt::Checked);
                }
                else
                {
                    item->setCheckState(Qt::Unchecked);
                }
            }
        }
    }
    for(int i = 0; i < ui->tableWidget->columnCount(); i++)
    {
        for(int j = 0; j < ui->tableWidget->rowCount(); j++)
        {
            QTableWidgetItem* item = ui->tableWidget->item(j, i);
            if(!item)
            {
                continue;
            }
            if(item->checkState() == Qt::Checked)
            {
                msigmaBase->showModelBase(j*tableColumn + i);
                number = row*tableColumn + column;
            } else {
                msigmaBase->hideModelBase(j*tableColumn + i);
            }
        }
    }
}

void ViewForm::on_comboBox_activated(int index)
{
    setCurrentQWT(index);
}

void ViewForm::on_curve_triggered()
{
    int row = ui->tableWidget->currentRow();
    int column = ui->tableWidget->currentColumn();
    number = row*tableColumn+column;
    msigmaBase->on_lineStyleComboBoxActivated(0,number);
}

void ViewForm::on_dashed_triggered()
{
    int row = ui->tableWidget->currentRow();
    int column = ui->tableWidget->currentColumn();
    number = row*tableColumn+column;
    msigmaBase->on_lineStyleComboBoxActivated(1,number);
}

void ViewForm::on_pillar_triggered()
{
    int row = ui->tableWidget->currentRow();
    int column = ui->tableWidget->currentColumn();
    number = row*tableColumn+column;
    msigmaBase->on_lineStyleComboBoxActivated(2,number);
}

void ViewForm::on_ladder_triggered()
{
    int row = ui->tableWidget->currentRow();
    int column = ui->tableWidget->currentColumn();
    number = row*tableColumn+column;
    msigmaBase->on_lineStyleComboBoxActivated(3,number);
}

void ViewForm::on_hideaction_triggered()
{
    int row = ui->tableWidget->currentRow();
    int column = ui->tableWidget->currentColumn();
    number = row*tableColumn+column;
    msigmaBase->on_lineStyleComboBoxActivated(4,number);
}
std::vector<ModelBase *>ViewForm::getModelBase()
{
    return modelBases;
}
/**
 * @brief ViewForm::on_setaction_triggered
 * 二维曲线设置响应函数
 */
void ViewForm::on_setaction_triggered()
{
    int index = 0; // 用来记载所选中的数据
    SetCruveDialog *dialog = new SetCruveDialog;
    // 先确定所选中的某条数据
    int row = ui->tableWidget->currentRow();
    int column = ui->tableWidget->currentColumn();
    index = row*tableColumn+column;
    tempBase.push_back(modelBases[index]);
    dialog->setTempModelBase(tempBase);
    dialog->show();
  // 只添加一条modelBase数据
    // 确定选中后添加数据
    // 在确定所选中的为某项功能
}
/**
 * @brief ViewForm::paintEvent
 * 画边框
 * @param event
 */
void ViewForm::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter p(this);
    p.setPen(Qt::SolidLine);
    p.setBrush(Qt::black);
    //p.drawLine(QPointF(0,0),QPointF(0,(this->width())));

    p.drawLine(QPointF(0,0),QPointF(0,this->height()));
    p.drawLine(QPointF(0,0),QPointF(this->width(),0));
    p.drawLine(QPointF(0,this->height()-1),QPointF(this->width()-1,this->height()));
    p.drawLine(QPointF(this->width()-1,0),QPointF(this->width()-1,this->height()));

    QStylePainter painter(this);
    //用style画背景 (会使用setstylesheet中的内容)
    QStyleOption opt;
    opt.initFrom(this);
    opt.rect=rect();
    painter.drawPrimitive(QStyle::PE_Widget, opt);

    QWidget::paintEvent(event);
}

