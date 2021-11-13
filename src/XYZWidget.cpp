#include "XYZWidget.h"
#include "ui_XYZWidget.h"

XYZWidget::XYZWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::XYZWidget)
{
    ui->setupUi(this);
}

XYZWidget::~XYZWidget()
{
    delete ui;
}

void XYZWidget::setModelRCSF(ModelRCSF *modelRcsf)
{
    this->modelRCSF = modelRcsf;
    ui->xcomboBox->setCurrentIndex(0); // 频率
    double startAngle = modelRCSF->findDataInfo(QString::fromLocal8Bit(START_TARGET_ANGLE)).toDouble();
    double endAngle = modelRCSF->findDataInfo(QString::fromLocal8Bit(END_TARGET_ANGLE)).toDouble();
    double stepAngle = modelRCSF->findDataInfo(QString::fromLocal8Bit(TARGET_NORMAL_ANGLE)).toDouble();
    ui->doubleSpinBox->setRange(startAngle, endAngle);
    ui->doubleSpinBox->setSingleStep(stepAngle);
    ui->doubleSpinBox->setValue(startAngle);
}

void XYZWidget::getReturn(int &xType, double &value)
{
    xType = ui->xcomboBox->currentIndex();
    value = ui->doubleSpinBox->value();
}

bool XYZWidget::getIsOK()
{
    return isOK;
}


void XYZWidget::on_xcomboBox_currentIndexChanged(int index)
{
    if(this->modelRCSF == NULL)
    {
        return;
    }
    if(index == 0)
    {
        double startAngle = modelRCSF->findDataInfo(QString::fromLocal8Bit(START_TARGET_ANGLE)).toDouble();
        double endAngle = modelRCSF->findDataInfo(QString::fromLocal8Bit(END_TARGET_ANGLE)).toDouble();
        double stepAngle = modelRCSF->findDataInfo(QString::fromLocal8Bit(TARGET_NORMAL_ANGLE)).toDouble();
        ui->doubleSpinBox->setRange(startAngle, endAngle);
        ui->doubleSpinBox->setSingleStep(stepAngle);
    } else {
        double startFo = modelRCSF->findDataInfo(QString::fromLocal8Bit(START_FPS)).toDouble();
        double endFo = modelRCSF->findDataInfo(QString::fromLocal8Bit(END_FPS)).toDouble();
        double stepFo = modelRCSF->findDataInfo(QString::fromLocal8Bit(FPS_STEP)).toDouble();
        ui->doubleSpinBox->setRange(startFo, endFo);
        ui->doubleSpinBox->setSingleStep(stepFo);
    }
}

void XYZWidget::on_okpushButton_clicked()
{
    isOK = true;
    this->close();
}

void XYZWidget::on_cancelpushButton_clicked()
{
    this->close();
}
