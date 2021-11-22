#include "SetCruveDialog.h"
#include "ui_SetCruveDialog.h"
#include <QDebug>
#include <QMessageBox>
#include <QTimer>

SetCruveDialog::SetCruveDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetCruveDialog)
{
    ui->setupUi(this);
    setButtonState();
    Qt::WindowFlags windowFlag = Qt::Dialog;
    //windowFlag |= Qt::WindowMinimizeButtonHint;
    windowFlag |= Qt::WindowMaximizeButtonHint;
    windowFlag |= Qt::WindowCloseButtonHint;
    this->setWindowFlags(windowFlag);
    setWindowModality(Qt::ApplicationModal);
    setAttribute(Qt::WA_ShowModal,true);
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    QDoubleValidator *m_double =new QDoubleValidator;
    ui->lineEdit_10->setValidator(m_double);   //  设置lineEdit只允许输入double
    ui->lineEdit_10->setEnabled(false);
    ui->lineEdit_11->setValidator(m_double);
    ui->lineEdit_11->setEnabled(false);
    ui->doubleSpinBox->setEnabled(false);
    ui->doubleSpinBox->setValue(8.00);
    ui->doubleSpinBox_2->setEnabled(false);
    ui->doubleSpinBox_2->setValue(-180.00);
    chart = new QChart();
    chartView = new ChartView(chart);
    QHBoxLayout* layout = new QHBoxLayout;
    layout->setMargin(0);
    //layout->addWidget(ui->tempWidget);
    layout->addWidget(chartView);
    this->ui->tempWidget->setLayout(layout);
    // 创建定时器连接
    time_Fps = new QTimer();
    connect(time_Fps,SIGNAL(timeout()),this,SLOT(upDataFps()));
    time_Angle = new QTimer();
    connect(time_Angle,SIGNAL(timeout()),this,SLOT(upDataAngle()));
}

SetCruveDialog::~SetCruveDialog()
{
    delete chart;
    delete chartView;
    delete ui;
}

void SetCruveDialog::setButtonState()
{
    for(int i = 0;i<4;i++)
    {
        doubleData[i] = 0.0;
        buttonState[i] = false;
    }
}

void SetCruveDialog::setTempModelBase(std::vector<ModelBase *> base)
{
    tempModelBase = base;
}

void SetCruveDialog::on_radioButton_clicked(bool checked)
{
    if(checked == true)
    {
        ui->pushButton->setEnabled(true);
        ui->lineEdit_10->setEnabled(true);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(false);
        ui->lineEdit_11->setEnabled(false);
        ui->doubleSpinBox->setEnabled(false);
        ui->doubleSpinBox_2->setEnabled(false);
    }
}

void SetCruveDialog::on_radioButton_2_clicked(bool checked)
{
    if(checked == true)
    {
        ui->pushButton->setEnabled(false);
        ui->lineEdit_10->setEnabled(false);
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(false);
        ui->lineEdit_11->setEnabled(false);
        ui->doubleSpinBox->setEnabled(true);
        ui->doubleSpinBox_2->setEnabled(false);
    }
}

void SetCruveDialog::on_radioButton_3_clicked(bool checked)
{
    if(checked == true)
    {
        ui->pushButton->setEnabled(false);
        ui->lineEdit_10->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(true);
        ui->pushButton_4->setEnabled(false);
        ui->lineEdit_11->setEnabled(true);
        ui->doubleSpinBox->setEnabled(false);
        ui->doubleSpinBox_2->setEnabled(false);
    }
}

void SetCruveDialog::on_radioButton_4_clicked(bool checked)
{
    if(checked == true)
    {
        ui->pushButton->setEnabled(false);
        ui->lineEdit_10->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(true);
        ui->lineEdit_11->setEnabled(false);
        ui->doubleSpinBox->setEnabled(false);
        ui->doubleSpinBox_2->setEnabled(true);
    }
}

void SetCruveDialog::on_pushButton_clicked(bool checked)
{

    setButtonState();
    QString str = ui->lineEdit_10->text();

    if(str == "")
    {
        QMessageBox::warning(NULL,"warning","请输入正确的频率",QMessageBox::Yes);
    }
    else
    {
        buttonState[0] = true;
        doubleData[0] = str.toDouble();
        for (int i=0;i<tempModelBase.size();i++)
        {
            updataModelBaseShow(1,0,tempModelBase[i]);
        }
    }
}

void SetCruveDialog::on_pushButton_2_clicked(bool checked)
{
    setButtonState();
    if(ui->pushButton_2->text() == QString::fromLocal8Bit("播放"))
    {
            qDebug()<<"aaaaaaa";
        ui->pushButton_2->setText(QString::fromLocal8Bit("暂停"));
        QString str = ui->doubleSpinBox->text();
        if(str == "")
        {
            QMessageBox::warning(NULL,"warning","请输入正确的频率",QMessageBox::Yes);
        }
        else
        {
            buttonState[1] = true;
            doubleData[1] = str.toDouble();
            time_Fps->start(1000);
        }
    }
    else if(ui->pushButton_2->text() == QString::fromLocal8Bit("暂停"))
    {
        ui->pushButton_2->setText(QString::fromLocal8Bit("播放"));
        time_Fps->stop();
        doubleData[1] = ui->doubleSpinBox->text().toDouble();
        updataModelBaseShow(1,1,tempModelBase[0]);
    }
}

void SetCruveDialog::on_pushButton_3_clicked(bool checked)
{
    setButtonState();
    QString str = ui->lineEdit_11->text();
    if(str == "")
    {
        QMessageBox::warning(NULL,"warning","请输入正确的方位",QMessageBox::Yes);
    }
    else
    {
        buttonState[2] = true;
        doubleData[2] = str.toDouble();
        for (int i=0;i<tempModelBase.size();i++)
        {
            updataModelBaseShow(0,2,tempModelBase[i]);
        }
    }
}

void SetCruveDialog::on_pushButton_4_clicked(bool checked)
{
    setButtonState();
    if(ui->pushButton_4->text() == QString::fromLocal8Bit("播放"))
    {
        ui->pushButton_4->setText(QString::fromLocal8Bit("暂停"));
        QString str = ui->doubleSpinBox_2->text();
        if(str == "")
        {
            QMessageBox::warning(NULL,"warning","请输入正确的方位",QMessageBox::Yes);
        }
        else
        {
            buttonState[3] = true;
            doubleData[3] = str.toDouble();
            time_Angle->start(1000);
        }
    }
    else if(ui->pushButton_4->text() == QString::fromLocal8Bit("暂停"))
    {
        ui->pushButton_4->setText(QString::fromLocal8Bit("播放"));
        time_Angle->stop();
        doubleData[3] = ui->doubleSpinBox_2->text().toDouble();
        updataModelBaseShow(0,3,tempModelBase[0]);
    }
}

void SetCruveDialog::upDataFps()
{
    doubleData[1]+=0.01;
    ui->doubleSpinBox->setValue(doubleData[1]);
    updataModelBaseShow(1,1,tempModelBase[0]);
}

void SetCruveDialog::upDataAngle()
{
    doubleData[3]+=0.2;
    ui->doubleSpinBox_2->setValue(doubleData[3]);
    updataModelBaseShow(0,3,tempModelBase[0]);
}

void SetCruveDialog::updataModelBaseShow(int xStep,int index, ModelBase *modelBase)
{
    chart->removeAllSeries();
    double xMin = 10000000, xMax = -10000000;
    double yMin = 10000000, yMax = -10000000;
    ModelRCSF *recf;
    recf = (ModelRCSF *)modelBase;
    recf->setCurrentValue(doubleData[index]);
    recf->setXStype(xStep);
    std::vector<Point2D> points = recf->getPoint2D();
    for(int j = 0; j < points.size(); j++)
    {
        Point2D p = points[j];
        double x = p.x, y = p.y;

        if(xMin > x)
        {
            xMin = x;
        }
        if(xMax < x)
        {
            xMax = x;
        }
        if(yMin > y)
        {
            yMin = y;
        }
        if(yMax < y)
        {
            yMax = y;
        }
    }
    QLineSeries *upperSeries = new QLineSeries(chart);
    for(int j = 0; j < points.size(); j++)
    {
        Point2D p = points[j];
        upperSeries->append(QPointF(p.x, p.y));
    }
    chart->addSeries(upperSeries);
    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setRange(xMin, xMax);
    chart->axes(Qt::Vertical).first()->setRange(yMin, yMax);
    // Add space to label to add space between labels and axis
    QValueAxis *axisY = qobject_cast<QValueAxis*>(chart->axes(Qt::Vertical).first());
    Q_ASSERT(axisY);
    axisY->setLabelFormat("%.1f  ");
}

