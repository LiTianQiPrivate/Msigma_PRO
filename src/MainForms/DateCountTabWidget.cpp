#include "DateCountTabWidget.h"
#include "ui_datecounttabwidget.h"
#include "KeyText.h"
#include "ModelBase.h"
#include <QMenu>
#include "qdebug.h"
#include <QString>
#include "Business.h"
#include "ViewFormRCS.h"
#include "ViewFromHisgram.h"
DateCountTabWidget::DateCountTabWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DateCountTabWidget)
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

    ui->tableWidget_2->setColumnCount(8);
    ui->tableWidget_2->verticalHeader()->setVisible(false);
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    header.clear();
    header << QString::fromLocal8Bit(NUMBER_NAME) << QString::fromLocal8Bit(DATA_TYPE) << QString::fromLocal8Bit(TARGET_NAME) << QString::fromLocal8Bit(QUALITY_GRADE)
           << QString::fromLocal8Bit(TARGET_PITCH_ANGLE)<< QString::fromLocal8Bit(TARGET_ROLL_ANGLE)
           << QString::fromLocal8Bit(WORK_FPS) << QString::fromLocal8Bit(POLARIZATION_COMBINATION);
    ui->tableWidget_2->setHorizontalHeaderLabels(header);
    ui->tableWidget_2->setSelectionBehavior(QAbstractItemView::SelectRows); // 整行选取
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_2->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
//    ui->tableWidget->setDragDropMode(QAbstractItemView::DragDrop);
    ui->tableWidget_2->setDragEnabled(true);
}

DateCountTabWidget::~DateCountTabWidget()
{
    delete ui;
}

void DateCountTabWidget::addModelObject(ModelBase *object)
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

    rows = ui->tableWidget_2->rowCount();
    ui->tableWidget_2->insertRow(rows);
    ui->tableWidget_2->setItem(rows,0,new QTableWidgetItem(QString::number(rows+1)));
    ui->tableWidget_2->setItem(rows,1,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(DATA_TYPE))));
    ui->tableWidget_2->setItem(rows,2,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(TARGET_NAME))));
    ui->tableWidget_2->setItem(rows,3,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(QUALITY_GRADE))));
    ui->tableWidget_2->setItem(rows,4,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(TARGET_PITCH_ANGLE))));
    ui->tableWidget_2->setItem(rows,5,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(TARGET_ROLL_ANGLE))));
    ui->tableWidget_2->setItem(rows,6,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(WORK_FPS))));
    ui->tableWidget_2->setItem(rows,7,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(POLARIZATION_COMBINATION))));

}

QAction *DateCountTabWidget::getActionState()
{
    return ui->action;
}

int DateCountTabWidget::getCount()
{
    return ui->tableWidget->rowCount();
}

QTableWidget *DateCountTabWidget::getTableWidget()
{
    return ui->tableWidget;
}

void DateCountTabWidget::addColumnTab(QTableWidget *table)
{
    strs.clear();
    int index = table->rowCount();
    int number = 0;
    double xMin = Business::getBusiness()->getViewFormRCS()->getXMin();
    double xMax = Business::getBusiness()->getViewFormRCS()->getXMax();

    for(int i = 0;i<table->rowCount();i++)
    {
        QTableWidgetItem *item1 = table->item(i,1);
        QTableWidgetItem *item2 = table->item(i,2);
        if(item1 == 0 || item2 == 0)
        {
            break;
        }
        else
        {
            QString str ;
            number++;
            if(fabs(item1->text().toDouble()-xMin) < fabs((item1->text().toDouble() - item2->text().toDouble()))
                    && fabs(item2->text().toDouble()-xMax) < fabs((item1->text().toDouble() - item2->text().toDouble())))
            {
                str = "(" + QString::number(xMin) + "-" + item1->text() + ")" + "-"
                        + "(" + item2->text() + "-" + QString::number(xMax) + ")";
            }
            else if(fabs(item2->text().toDouble()-xMin) < fabs((item1->text().toDouble() - item2->text().toDouble()))
                   && fabs(item1->text().toDouble()-xMax) < fabs((item1->text().toDouble() - item2->text().toDouble())))
            {
                str = "(" + QString::number(xMin) + "-" + item2->text() + ")" + "-"
                       + "(" + item1->text() + "-" + QString::number(xMax) + ")";
            }
            else
            {
                if(item1->text().contains(","))
                {
                    index = item1->text().indexOf(",");
                    str = "(" + item1->text().left(index) +"-" + item1->text().right(item1->text().size()-index-1)+")";
                }
                else
                {
                    str = item1->text();
                }

                if(item2->text().contains(","))
                {
                    index = item2->text().indexOf(",");
                    str = str + "-" + "(" + item2->text().left(index) + "-" + item2->text().right(item2->text().size()-index-1)+")";
                }
                else
                {
                    str = str +"-" + item2->text();
                }
            }
            strs.push_back(str);
        }
    }
    QStringList header;
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setColumnCount(8+number);
    ui->tableWidget_2->verticalHeader()->setVisible(false);
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    header << QString::fromLocal8Bit(NUMBER_NAME) << QString::fromLocal8Bit(DATA_TYPE) << QString::fromLocal8Bit(TARGET_NAME) << QString::fromLocal8Bit(QUALITY_GRADE)
           << QString::fromLocal8Bit(TARGET_PITCH_ANGLE)<< QString::fromLocal8Bit(TARGET_ROLL_ANGLE)
           << QString::fromLocal8Bit(WORK_FPS) << QString::fromLocal8Bit(POLARIZATION_COMBINATION);
    for(int i=0;i<number;i++)
    {
        header.push_back(strs[i]);
    }
    ui->tableWidget_2->setHorizontalHeaderLabels(header);
    ui->tableWidget_2->setSelectionBehavior(QAbstractItemView::SelectRows); // 整行选取
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_2->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
    ui->tableWidget_2->setDragEnabled(true);
    //  根据button添加 默认均值
    tableCount = number;
    on_pushButton_3_clicked(true);
}

void DateCountTabWidget::setTableWidgetValue(std::vector<std::vector<double> > values)
{
    tableValues = values;
}

void DateCountTabWidget::on_tableWidget_customContextMenuRequested(const QPoint &pos)
{
    if(ui->tableWidget->rowCount() == 0)
    {
        return;
    }
    QMenu menu;
    menu.addAction(ui->action);
    menu.exec(QCursor::pos());
}
/**
 * @brief DateCountTabWidget::on_pushButton_3_clicked
 * 均值
 * @param checked
 */
void DateCountTabWidget::on_pushButton_3_clicked(bool checked)
{
    for(int i = 0 ; i<modelBases.size();i++)
    {
        ModelBase *object = modelBases[i];
        ui->tableWidget_2->setItem(i,0,new QTableWidgetItem(QString::number(i+1)));
        ui->tableWidget_2->setItem(i,1,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(DATA_TYPE))));
        ui->tableWidget_2->setItem(i,2,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(TARGET_NAME))));
        ui->tableWidget_2->setItem(i,3,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(QUALITY_GRADE))));
        ui->tableWidget_2->setItem(i,4,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(TARGET_PITCH_ANGLE))));
        ui->tableWidget_2->setItem(i,5,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(TARGET_ROLL_ANGLE))));
        ui->tableWidget_2->setItem(i,6,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(WORK_FPS))));
        ui->tableWidget_2->setItem(i,7,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(POLARIZATION_COMBINATION))));
        for(int j = 0;j<tableCount;j++)
        {
            std::vector<double> value = tableValues[0];
            if(value.size() > 0)
            {
                ui->tableWidget_2->setItem(i,8+j,new QTableWidgetItem(QString::number(value[j*modelBases.size()+i],'f',2)));
            }
        }
    }
    std::vector<std::vector<double>> zValues;
    for(int i = 0;i<modelBases.size();i++)
    {
        std::vector<double> yValue;
        for(int j = 0;j<tableCount;j++)
        {
            yValue.push_back(tableValues[0][j*modelBases.size()+i]);
        }
        zValues.push_back(yValue);
        yValue.clear();
    }
    Business::getBusiness()->getViewFromHisgram()->getValues(zValues,strs,1);
}
/**
 * @brief DateCountTabWidget::on_pushButton_4_clicked
 * 最大值
 * @param checked
 */
void DateCountTabWidget::on_pushButton_4_clicked(bool checked)
{
    for(int i = 0 ; i<modelBases.size();i++)
    {
        ModelBase *object = modelBases[i];
        ui->tableWidget_2->setItem(i,0,new QTableWidgetItem(QString::number(i+1)));
        ui->tableWidget_2->setItem(i,1,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(DATA_TYPE))));
        ui->tableWidget_2->setItem(i,2,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(TARGET_NAME))));
        ui->tableWidget_2->setItem(i,3,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(QUALITY_GRADE))));
        ui->tableWidget_2->setItem(i,4,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(TARGET_PITCH_ANGLE))));
        ui->tableWidget_2->setItem(i,5,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(TARGET_ROLL_ANGLE))));
        ui->tableWidget_2->setItem(i,6,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(WORK_FPS))));
        ui->tableWidget_2->setItem(i,7,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(POLARIZATION_COMBINATION))));
        for(int j = 0;j<tableCount;j++)
        {
            std::vector<double> value = tableValues[1];
            if(value.size() > 0)
            {
                ui->tableWidget_2->setItem(i,8+j,new QTableWidgetItem(QString::number(value[j*modelBases.size()+i],'f',2)));
            }
        }
    }
    std::vector<std::vector<double>> zValues;
    for(int i = 0;i<modelBases.size();i++)
    {
        std::vector<double> yValue;
        for(int j = 0;j<tableCount;j++)
        {
            yValue.push_back(tableValues[1][j*modelBases.size()+i]);
        }
        zValues.push_back(yValue);
        yValue.clear();
    }
    Business::getBusiness()->getViewFromHisgram()->getValues(zValues,strs,2);
}
/**
 * @brief DateCountTabWidget::on_pushButton_5_clicked
 * 最小值
 * @param checked
 */
void DateCountTabWidget::on_pushButton_5_clicked(bool checked)
{
    for(int i = 0 ; i<modelBases.size();i++)
    {
        ModelBase *object = modelBases[i];
        ui->tableWidget_2->setItem(i,0,new QTableWidgetItem(QString::number(i+1)));
        ui->tableWidget_2->setItem(i,1,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(DATA_TYPE))));
        ui->tableWidget_2->setItem(i,2,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(TARGET_NAME))));
        ui->tableWidget_2->setItem(i,3,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(QUALITY_GRADE))));
        ui->tableWidget_2->setItem(i,4,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(TARGET_PITCH_ANGLE))));
        ui->tableWidget_2->setItem(i,5,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(TARGET_ROLL_ANGLE))));
        ui->tableWidget_2->setItem(i,6,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(WORK_FPS))));
        ui->tableWidget_2->setItem(i,7,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(POLARIZATION_COMBINATION))));
        for(int j = 0;j<tableCount;j++)
        {
            std::vector<double> value = tableValues[2];
            if(value.size() > 0)
            {
                ui->tableWidget_2->setItem(i,8+j,new QTableWidgetItem(QString::number(value[j*modelBases.size()+i],'f',2)));
            }
        }
    }
    std::vector<std::vector<double>> zValues;
    for(int i = 0;i<modelBases.size();i++)
    {
        std::vector<double> yValue;
        for(int j = 0;j<tableCount;j++)
        {
            yValue.push_back(tableValues[2][j*modelBases.size()+i]);
        }
        zValues.push_back(yValue);
        yValue.clear();
    }
    Business::getBusiness()->getViewFromHisgram()->getValues(zValues,strs,3);
}
/**
 * @brief DateCountTabWidget::on_pushButton_6_clicked
 *  中值
 * @param checked
 */
void DateCountTabWidget::on_pushButton_6_clicked(bool checked)
{
    for(int i = 0 ; i<modelBases.size();i++)
    {
        ModelBase *object = modelBases[i];
        ui->tableWidget_2->setItem(i,0,new QTableWidgetItem(QString::number(i+1)));
        ui->tableWidget_2->setItem(i,1,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(DATA_TYPE))));
        ui->tableWidget_2->setItem(i,2,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(TARGET_NAME))));
        ui->tableWidget_2->setItem(i,3,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(QUALITY_GRADE))));
        ui->tableWidget_2->setItem(i,4,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(TARGET_PITCH_ANGLE))));
        ui->tableWidget_2->setItem(i,5,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(TARGET_ROLL_ANGLE))));
        ui->tableWidget_2->setItem(i,6,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(WORK_FPS))));
        ui->tableWidget_2->setItem(i,7,new QTableWidgetItem(object->findDataInfo(QString::fromLocal8Bit(POLARIZATION_COMBINATION))));
        for(int j = 0;j<tableCount;j++)
        {
            std::vector<double> value = tableValues[3];
            if(value.size() > 0)
            {
                ui->tableWidget_2->setItem(i,8+j,new QTableWidgetItem(QString::number(value[j*modelBases.size()+i],'f',2)));
            }
        }
    }
    std::vector<std::vector<double>> zValues;
    for(int i = 0;i<modelBases.size();i++)
    {
        std::vector<double> yValue;
        for(int j = 0;j<tableCount;j++)
        {
            yValue.push_back(tableValues[3][j*modelBases.size()+i]);
        }
        zValues.push_back(yValue);
        yValue.clear();
    }
    Business::getBusiness()->getViewFromHisgram()->getValues(zValues,strs,4);
}
