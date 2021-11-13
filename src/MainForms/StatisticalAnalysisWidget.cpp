#include "StatisticalAnalysisWidget.h"
#include "ui_StatisticalAnalysisWidget.h"
#include <QDebug>
#include "Business.h"
#include "DateCountTabWidget.h"
#include "ViewFormRCS.h"

StatisticalAnalysisWidget::StatisticalAnalysisWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatisticalAnalysisWidget)
{
    ui->setupUi(this);
}

StatisticalAnalysisWidget::~StatisticalAnalysisWidget()
{
    delete ui;
}

void StatisticalAnalysisWidget::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    double x1 = 0.0,x2 = 0.0,x3 = 0.0, x4 = 0.0;
    QTableWidgetItem *item1 = ui->tableWidget->item(item->row(),1);
    QTableWidgetItem *item2 = ui->tableWidget->item(item->row(),2);
    if(item1 != 0)    // 为了当=0时 异常崩溃  在所有todouble()后增加0.00001
    {
        if(item1->text().contains(","))
        {
            int index = item1->text().indexOf(",");
            x1 = item1->text().left(index).toDouble()+0.00001;
            x3 = item1->text().right(item1->text().size()-index-1).toDouble()+0.00001;
        }
        else
        {
            x1 = item1->text().toDouble()+0.00001;
        }
    }
    if(item2 != 0)
    {
        if(item2->text().contains(","))
        {
            int index = item2->text().indexOf(",");
            x2 = item2->text().left(index).toDouble()+0.00001;
            x4 = item2->text().right(item2->text().size()-index-1).toDouble()+0.00001;
        }
        else
        {
            x2 = item2->text().toDouble()+0.00001;
        }
    }
    if(fabs(x3) > 0.00001 && fabs(x4) > 0.00001)
    {
        double x5 = x3;
        // 此判断是为了保证x3 >x1  x4>x2
        if(x3 < x1)
        {
            x3 = x1;
            x1 = x5;
        }
        x5 = x4;
        if(x4 < x2)
        {
            x4 = x2;
            x2 = x5;
        }
        Business::getBusiness()->getViewFormRCS()->setTableWidgetStatistical(x1,x2,x3,x4);
    }
    else
    {
        double x5 = x2;
        // 此判断是为了让x1>x2 之后数据处理就不用在考虑x1和x2大小的问题
        if(x2 < x1)
        {
            x2 = x1;
            x1 = x5;
        }
        Business::getBusiness()->getViewFormRCS()->setTableWidgetStatistical(x1,x2,x3,x4);
    }
}

void StatisticalAnalysisWidget::on_pushButton_clicked(bool checked)
{
    ui->tableWidget->clearContents();
    Business::getBusiness()->getDateCountTabWidget()->addColumnTab(ui->tableWidget);
    Business::getBusiness()->getViewFormRCS()->clearDataValue();
}

void StatisticalAnalysisWidget::on_pushButton_2_clicked(bool checked)
{
   Business::getBusiness()->getDateCountTabWidget()->addColumnTab(ui->tableWidget);
   Business::getBusiness()->getViewFormRCS()->clearFillRect();
}

void StatisticalAnalysisWidget::on_pushButton_3_clicked(bool checked)
{
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->verticalHeader()->setVisible(false);
}
