#include "CurveViewForm.h"
#include "ui_CurveViewForm.h"
#include "QHBoxLayout"
#include "QVBoxLayout"

CurveViewForm::CurveViewForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CurveViewForm)
{
    ui->setupUi(this);
    for(int i = 0; i < 4; i++)
    {
        ViewForm* viewForm = new ViewForm;
        viewForms.push_back(viewForm);
    }
    initUpdataLayout();
    this->setMouseTracking(true);   // 监听鼠标
}

CurveViewForm::~CurveViewForm()
{
    delete ui;
}

void CurveViewForm::resizeEvent(QResizeEvent *event)
{
    initUpdataLayout();
}

void CurveViewForm::initUpdataLayout()
{
    std::vector<ViewForm*> showViewForms;
    if(ui->checkBox1->isChecked())
    {
        showViewForms.push_back(viewForms[0]);
    }
    if(ui->checkBox2->isChecked())
    {
        showViewForms.push_back(viewForms[1]);
    }
    if(ui->checkBox_3->isChecked())
    {
        showViewForms.push_back(viewForms[2]);
    }
    if(ui->checkBox_4->isChecked())
    {
        showViewForms.push_back(viewForms[3]);
    }
    if(showViewForms.size() == 0)
    {
        for(int i = 0; i < viewForms.size(); i++)
        {
            viewForms[i]->hide();
        }
        return;
    }
    if(layoutType == 0) // 网格布局
    {
        if(showViewForms.size() == 1)
        {
            showViewForms[0]->setParent(ui->widget);
            showViewForms[0]->setGeometry(0, 0, ui->widget->width(), ui->widget->height());
            showViewForms[0]->show();
        } else if(showViewForms.size() == 2){
            showViewForms[0]->setParent(ui->widget);
            showViewForms[0]->setGeometry(0, 0 ,ui->widget->width()/2, ui->widget->height());
            showViewForms[0]->show();
            showViewForms[1]->setParent(ui->widget);
            showViewForms[1]->setGeometry(ui->widget->width()/2, 0,ui->widget->width()/2, ui->widget->height());
            showViewForms[1]->show();
        } else if(showViewForms.size() == 3) {
            showViewForms[0]->setParent(ui->widget);
            showViewForms[0]->setGeometry(0, 0 ,ui->widget->width()/2, ui->widget->height()/2);
            showViewForms[0]->show();
            showViewForms[1]->setParent(ui->widget);
            showViewForms[1]->setGeometry(ui->widget->width()/2, 0,ui->widget->width()/2, ui->widget->height()/2);
            showViewForms[1]->show();
            showViewForms[2]->setParent(ui->widget);
            showViewForms[2]->setGeometry(0, ui->widget->height()/2,ui->widget->width(), ui->widget->height()/2);
            showViewForms[2]->show();
        } else if(viewForms.size() == 4){
            showViewForms[0]->setParent(ui->widget);
            showViewForms[0]->setGeometry(0, 0 ,ui->widget->width()/2, ui->widget->height()/2);
            showViewForms[0]->show();
            showViewForms[1]->setParent(ui->widget);
            showViewForms[1]->setGeometry(ui->widget->width()/2, 0,ui->widget->width()/2, ui->widget->height()/2);
            showViewForms[1]->show();
            showViewForms[2]->setParent(ui->widget);
            showViewForms[2]->setGeometry(0, ui->widget->height()/2,ui->widget->width()/2, ui->widget->height()/2);
            showViewForms[2]->show();
            showViewForms[3]->setParent(ui->widget);
            showViewForms[3]->setGeometry(ui->widget->width()/2, ui->widget->height()/2,ui->widget->width()/2, ui->widget->height()/2);
            showViewForms[3]->show();
        }
    } else if(layoutType == 1){ // 横向布局
        if(showViewForms.size() == 1)
        {
            showViewForms[0]->setParent(ui->widget);
            showViewForms[0]->setGeometry(0, 0, ui->widget->width(), ui->widget->height());
            showViewForms[0]->show();
        } else if(showViewForms.size() == 2){
            showViewForms[0]->setParent(ui->widget);
            showViewForms[0]->setGeometry(0, 0 ,ui->widget->width()/2, ui->widget->height());
            showViewForms[0]->show();
            showViewForms[1]->setParent(ui->widget);
            showViewForms[1]->setGeometry(ui->widget->width()/2, 0,ui->widget->width(), ui->widget->height());
            showViewForms[1]->show();
        } else if(showViewForms.size() == 3) {
            showViewForms[0]->setParent(ui->widget);
            showViewForms[0]->setGeometry(0, 0 ,ui->widget->width()/3, ui->widget->height());
            showViewForms[0]->show();
            showViewForms[1]->setParent(ui->widget);
            showViewForms[1]->setGeometry(ui->widget->width()/3, 0,ui->widget->width()/3, ui->widget->height());
            showViewForms[1]->show();
            showViewForms[2]->setParent(ui->widget);
            showViewForms[2]->setGeometry(ui->widget->width()/3*2,0,ui->widget->width()/3, ui->widget->height());
            showViewForms[2]->show();
        } else if(viewForms.size() == 4){
            showViewForms[0]->setParent(ui->widget);
            showViewForms[0]->setGeometry(0, 0 ,ui->widget->width()/4, ui->widget->height());
            showViewForms[0]->show();
            showViewForms[1]->setParent(ui->widget);
            showViewForms[1]->setGeometry(ui->widget->width()/4, 0,ui->widget->width()/4, ui->widget->height());
            showViewForms[1]->show();
            showViewForms[2]->setParent(ui->widget);
            showViewForms[2]->setGeometry(ui->widget->width()/2, 0,ui->widget->width()/4, ui->widget->height());
            showViewForms[2]->show();
            showViewForms[3]->setParent(ui->widget);
            showViewForms[3]->setGeometry(ui->widget->width()/4*3, 0,ui->widget->width()/4, ui->widget->height());
            showViewForms[3]->show();
        }
    } else if(layoutType == 2){ // 纵向布局
        if(showViewForms.size() == 1)
        {
            showViewForms[0]->setParent(ui->widget);
            showViewForms[0]->setGeometry(0, 0, ui->widget->width(), ui->widget->height());
            showViewForms[0]->show();
        } else if(showViewForms.size() == 2){
            showViewForms[0]->setParent(ui->widget);
            showViewForms[0]->setGeometry(0, 0 ,ui->widget->width(), ui->widget->height()/2);
            showViewForms[0]->show();
            showViewForms[1]->setParent(ui->widget);
            showViewForms[1]->setGeometry(0, ui->widget->height()/2,ui->widget->width(), ui->widget->height()/2);
            showViewForms[1]->show();
        } else if(showViewForms.size() == 3) {
            showViewForms[0]->setParent(ui->widget);
            showViewForms[0]->setGeometry(0, 0 ,ui->widget->width(), ui->widget->height()/3);
            showViewForms[0]->show();
            showViewForms[1]->setParent(ui->widget);
            showViewForms[1]->setGeometry(0, ui->widget->height()/3,ui->widget->width(), ui->widget->height()/3);
            showViewForms[1]->show();
            showViewForms[2]->setParent(ui->widget);
            showViewForms[2]->setGeometry(0,ui->widget->height()/3*2,ui->widget->width(), ui->widget->height()/3);
            showViewForms[2]->show();
        } else if(viewForms.size() == 4){
            showViewForms[0]->setParent(ui->widget);
            showViewForms[0]->setGeometry(0, 0 ,ui->widget->width(), ui->widget->height()/4);
            showViewForms[0]->show();
            showViewForms[1]->setParent(ui->widget);
            showViewForms[1]->setGeometry( 0,ui->widget->height()/4,ui->widget->width(), ui->widget->height()/4);
            showViewForms[1]->show();
            showViewForms[2]->setParent(ui->widget);
            showViewForms[2]->setGeometry( 0,ui->widget->height()/2,ui->widget->width(), ui->widget->height()/4);
            showViewForms[2]->show();
            showViewForms[3]->setParent(ui->widget);
            showViewForms[3]->setGeometry( 0,ui->widget->height()/4*3,ui->widget->width(), ui->widget->height()/4);
            showViewForms[3]->show();
        }
    }
}

int CurveViewForm::getViewFormCount()
{
    return viewForms.size();
}
ViewForm *CurveViewForm::getViewFromWidget(int index)
{
    if(index < viewForms.size() && index >= 0)
    {
        return viewForms[index];
    }
}
void CurveViewForm::addModelBase(ModelBase *modelBase, int viewID)
{
    viewForms[viewID]->addModelBase(modelBase);
}

void CurveViewForm::on_grodtoolButton_clicked()
{
    layoutType = 0;
    initUpdataLayout();
}

void CurveViewForm::on_hortoolButton_clicked()
{
    layoutType = 1;
    initUpdataLayout();
}

void CurveViewForm::on_vertoolButton_clicked()
{
    layoutType = 2;
    initUpdataLayout();
}

void CurveViewForm::on_checkBox1_clicked(bool checked)
{
    if(checked)
    {
        viewForms[0]->show();
        initUpdataLayout();
    } else {
        viewForms[0]->hide();
        initUpdataLayout();
    }
}

void CurveViewForm::on_checkBox2_clicked(bool checked)
{
    if(checked)
    {
        viewForms[1]->show();
        initUpdataLayout();
    } else {
        viewForms[1]->hide();
        initUpdataLayout();
    }
}

void CurveViewForm::on_checkBox_3_clicked(bool checked)
{
    if(checked)
    {
        viewForms[2]->show();
        initUpdataLayout();
    } else {
        viewForms[2]->hide();
        initUpdataLayout();
    }
}

void CurveViewForm::on_checkBox_4_clicked(bool checked)
{
    if(checked)
    {
        viewForms[3]->show();
        initUpdataLayout();
    } else {
        viewForms[3]->hide();
        initUpdataLayout();
    }
}
void CurveViewForm::mouseMoveEvent(QMouseEvent *event)           // 移动
{
    switch(event->button())
    {
    case Qt::LeftButton:
        qDebug("111");
        break;
    case Qt::RightButton:
        break;
    }
}
