#include "ModelTabWidget.h"
#include "ui_ModelTabWidget.h"
#include <QToolButton>
#include "DialogText.h"

ModelTabWidget::ModelTabWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModelTabWidget)
{
    ui->setupUi(this);
    ui->tabWidget->setCornerWidget(&tabButtonForm);
    connect(tabButtonForm.getAddButton(),  SIGNAL(clicked()),  this,  SLOT(on_addToolButton_Cliced()));
    connect(tabButtonForm.getRemoveButton(),  SIGNAL(clicked()),  this,  SLOT(on_removeToolButton_Cliced()));
    connect(tabButtonForm.getChangedButton(),  SIGNAL(clicked()),  this,  SLOT(on_chengedToolButton_Cliced()));
    CurveViewForm* curveViewForm = new CurveViewForm;
    ui->tabWidget->addTab(curveViewForm, QString::fromLocal8Bit("曲线图"));
    curveViewForms.push_back(curveViewForm);
}

ModelTabWidget::~ModelTabWidget()
{
    delete ui;
}
/**
 * @brief ModelTabWidget::getCurrentCurveViewForm
 * 获取当前窗口
 * @return
 */
CurveViewForm *ModelTabWidget::getCurrentCurveViewForm()
{
    return curveViewForms[ui->tabWidget->currentIndex()];
}
/**
 * @brief ModelTabWidget::on_addToolButton_Cliced
 * 添加图标窗口
 */
void ModelTabWidget::on_addToolButton_Cliced()
{
    DialogText dialog;
    dialog.setLabelText(QString::fromLocal8Bit("请输入名字:"));
    dialog.exec();
    if(dialog.getChangedText())
    {
        QString str = dialog.getEditText();
        CurveViewForm* curveViewForm = new CurveViewForm;
        ui->tabWidget->addTab(curveViewForm, str);
        curveViewForms.push_back(curveViewForm);
        ui->tabWidget->setCurrentIndex(curveViewForms.size() - 1);
    }
}
/**
 * @brief ModelTabWidget::on_removeToolButton_Cliced
 * 删除图标  窗口
 */
void ModelTabWidget::on_removeToolButton_Cliced()
{
    if(ui->tabWidget->count() == 1)
    {
        return;
    }
    int currentIndex = ui->tabWidget->currentIndex();
    ui->tabWidget->removeTab(currentIndex);
    CurveViewForm* curveViewForm = curveViewForms[currentIndex];
    delete curveViewForm;
    curveViewForms.erase(curveViewForms.begin() + currentIndex);
}
/**
 * @brief ModelTabWidget::on_chengedToolButton_Cliced
 * 修改图标 窗口名字
 */
void ModelTabWidget::on_chengedToolButton_Cliced()
{
    DialogText dialog;
    dialog.setLabelText(QString::fromLocal8Bit("请输入名字:"));
    dialog.exec();
    if(dialog.getChangedText())
    {
        QString str = dialog.getEditText();
        ui->tabWidget->setTabText(ui->tabWidget->currentIndex(),str);
    }
}

