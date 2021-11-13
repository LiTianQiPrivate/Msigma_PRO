#include "AddThresholdDot.h"
#include "ui_AddThresholdDot.h"
#include <QDoubleValidator>
#include <QMessageBox>
#include "Business.h"
#include "ModelTabWidget.h"
#include "CurveViewForm.h"
AddThresholdDot::AddThresholdDot(int index,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddThresholdDot)
{
    setAttribute(Qt::WA_ShowModal,true);
    currentIndex = index;
    ui->setupUi(this);
    ui->lineEdit->setValidator(new QDoubleValidator);
    ui->lineEdit_2->setValidator(new QDoubleValidator);
}

AddThresholdDot::~AddThresholdDot()
{
    std::vector<QPointF >().swap(xyDot);
    delete ui;
}

void AddThresholdDot::on_pushButton_clicked(bool checked)
{
    if(ui->lineEdit->text() == "" || ui->lineEdit_2->text() == "")
    {
        QMessageBox::warning(NULL,"warning","请输入正确的坐标",QMessageBox::Yes);
        return ;
    }
     //  继续添加下一个点
    double x = ui->lineEdit->text().toDouble();
    double y = ui->lineEdit_2->text().toDouble();
    if(xyDot.size() > 0)
    {
        QPointF endXy = xyDot.at(xyDot.size()-1);
        if((fabs(x-endXy.x())<0.001) && (fabs(y-endXy.y()) < 0.001))
        {
            QMessageBox::warning(NULL,"warning","请不要输入与上个点相同的坐标",QMessageBox::Yes);
            return ;
        }
    }
    xyDot.push_back(QPointF(x,y));
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->pushButton->setText(("坐标")+QString::number(xyDot.size()+1));
}

void AddThresholdDot::on_pushButton_2_clicked(bool checked)
{
    //  确定添加完毕
    if(xyDot.size() < 2)
    {
       QMessageBox:: StandardButton result = QMessageBox::information(NULL,"warning","请输入至少两个门限点\r\n是否继续输入",QMessageBox::Yes|QMessageBox::No);
       switch(result)
       {
        case QMessageBox::Yes:
           break;
       case QMessageBox::No:
           this->close();
           break;
       default:
           break;
       }
       return;
    }
    this->close();
    std::vector<ModelBase *>base = Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(currentIndex)->getModelBase();
    Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(currentIndex)->setThresholdDot(xyDot);
    Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(currentIndex)->updataTableWidgetItem(base);
}
