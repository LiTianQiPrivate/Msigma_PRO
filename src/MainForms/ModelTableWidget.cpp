#include "ModelTableWidget.h"
#include "ui_ModelTableWidget.h"
#include "QTableWidgetItem"
#include "QHeaderView"
#include "QTableWidget"
#include "Business.h"
#include "ModelTabWidget.h"
#include "ModelTreeWidget.h"
#include "StepWidget.h"
#include "CurveShowAndSetWidget.h"

ModelTableWidget::ModelTableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModelTableWidget)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(9);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QStringList header;
    header << QString::fromLocal8Bit(NUMBER_NAME) << QString::fromLocal8Bit(EXPERIMENT_NAME) << QString::fromLocal8Bit(DATA_TYPE) << QString::fromLocal8Bit(TARGET_NAME)
           << QString::fromLocal8Bit(POLARIZATION_COMBINATION)<< QString::fromLocal8Bit(TARGET_PITCH_ANGLE)
           << QString::fromLocal8Bit(TARGET_ROLL_ANGLE) << QString::fromLocal8Bit(START_FPS) << QString::fromLocal8Bit(END_FPS);
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows); // 整行选取
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
//    ui->tableWidget->setDragDropMode(QAbstractItemView::DragDrop);
    ui->tableWidget->setDragEnabled(true);
    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    //QObject::connect(ui->tableWidget, SIGNAL(customContextMenuRequested(const QPoint)), this, SLOT(on_tableWidget_customContextMenuRequested(const QPoint)));
}

ModelTableWidget::~ModelTableWidget()
{
    delete ui;
}

void ModelTableWidget::addModelObject(ModelBase *object)
{
    modelBases.push_back(object);
    int rows = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(rows);
    ui->tableWidget->setItem(rows,0,new QTableWidgetItem(QString::number(rows+1)));
    ui->tableWidget->setItem(rows,1,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(EXPERIMENT_NAME))));
    ui->tableWidget->setItem(rows,2,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(DATA_TYPE))));
    ui->tableWidget->setItem(rows,3,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(TARGET_NAME))));
    ui->tableWidget->setItem(rows,4,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(POLARIZATION_COMBINATION))));
    ui->tableWidget->setItem(rows,5,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(TARGET_PITCH_ANGLE))));
    ui->tableWidget->setItem(rows,6,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(TARGET_ROLL_ANGLE))));
    ui->tableWidget->setItem(rows,7,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(START_FPS))));
    ui->tableWidget->setItem(rows,8,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(END_FPS))));
}

void ModelTableWidget::on_tableWidget_customContextMenuRequested(const QPoint &pos)
{
    if(ui->tableWidget->rowCount() == 0)
    {
        return;
    }

    QMenu menu;
    int viewCount = Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFormCount();
    if(viewCount == 1)
    {
        menu.addAction(ui->add1Action);
    } else if(viewCount == 2){
        menu.addAction(ui->add1Action);
        menu.addAction(ui->add2action);
    } else if(viewCount == 3) {
        menu.addAction(ui->add1Action);
        menu.addAction(ui->add2action);
        menu.addAction(ui->add3action);
    } else if(viewCount == 4) {
        menu.addAction(ui->add1Action);
        menu.addAction(ui->add2action);
        menu.addAction(ui->add3action);
        menu.addAction(ui->add4action);
    }
    menu.exec(QCursor::pos());
}

void ModelTableWidget::on_add1Action_triggered()
{
    std::vector<ModelBase*> modelBase;
    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        QTableWidgetItem* item = ui->tableWidget->item(i, 1);
        if( ui->tableWidget->isItemSelected(item))
        {
            Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->addModelBase(modelBases[i], 0);
            modelBase.push_back(modelBases[i]);
        }
    }
    Business::getBusiness()->getCurveShowAndSetWidget()->getModelBase(modelBase,0);
}

void ModelTableWidget::on_add2action_triggered()
{
    std::vector<ModelBase*> modelBase;
    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        QTableWidgetItem* item = ui->tableWidget->item(i, 1);
        if( ui->tableWidget->isItemSelected(item))
        {
            Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->addModelBase(modelBases[i], 1);
            modelBase.push_back(modelBases[i]);
        }
    }
    Business::getBusiness()->getCurveShowAndSetWidget()->getModelBase(modelBase,1);
}

void ModelTableWidget::on_add3action_triggered()
{
    std::vector<ModelBase*> modelBase;
    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        QTableWidgetItem* item = ui->tableWidget->item(i, 1);
        if( ui->tableWidget->isItemSelected(item))
        {
            Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->addModelBase(modelBases[i], 2);
            modelBase.push_back(modelBases[i]);
        }
    }
    Business::getBusiness()->getCurveShowAndSetWidget()->getModelBase(modelBase,2);
}

void ModelTableWidget::on_add4action_triggered()
{
    std::vector<ModelBase*> modelBase;
    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        QTableWidgetItem* item = ui->tableWidget->item(i, 1);
        if( ui->tableWidget->isItemSelected(item))
        {
            Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->addModelBase(modelBases[i], 3);
            modelBase.push_back(modelBases[i]);
        }
    }
    Business::getBusiness()->getCurveShowAndSetWidget()->getModelBase(modelBase,3);
}
// 单击item
void ModelTableWidget::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
    Business::getBusiness()->getModelTreeWidget()->closeItem();
    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        QTableWidgetItem* item = ui->tableWidget->item(i, 1);
        if( ui->tableWidget->isItemSelected(item))
        {
            Business::getBusiness()->getModelTreeWidget()->showItem(i);
        }
    }
}
