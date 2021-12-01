#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QSplitter>
#include "QHBoxLayout"
#include "Business.h"
#include "QStringList"
#include "QFileDialog"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString qss;
    QFile qssFile("E:/Msigma-Pro/Msigma_DAR/src/QSS/myQss.qss");
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen())
    {
        qss = QLatin1String(qssFile.readAll());
        qApp->setStyleSheet(qss);
        qssFile.close();
    }
    // 0.数据基本信息 1.曲线显示与设置 2.数据平滑与对齐 3.数据统计与分析 4.数据打印与输出
    stepWidget.setWidget(0, &modelTreeWidget);
    stepWidget.setWidget(1, &curveShowAndSetWidget);
    stepWidget.setWidget(2, &dataTranslationAline);
    stepWidget.setWidget(3, &statisticalAnalysisWidget);
    stepWidget.setWidget(4, &dataPrintAndOutput);
    Business::getBusiness()->setStepWidget(&stepWidget);
    QSplitter* splitter_v = new QSplitter(this);
    splitter_v->setOrientation(Qt::Vertical);
    splitter_v->addWidget(&modelTabWidget);
    splitter_v->addWidget(&modelTableWidget);
    splitter_v->setStretchFactor(5, 1);
    tabWidget.addTab(&viewFormRCS,QString::fromLocal8Bit("RCS曲线图"));
    tabWidget.addTab(&viewFromHisgram,QString::fromLocal8Bit("统计图表"));
    QWidget *rightWidget = new QWidget;
    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(&tabWidget);
    vLayout->addWidget(&dateCountTabWidget);
    vLayout->setStretchFactor(&tabWidget,2);
    vLayout->setStretchFactor(&dateCountTabWidget,1);
    rightWidget->setLayout(vLayout);
    connect(&tabWidget,SIGNAL(currentChanged(int)),this,SLOT(on_tabWidget_currentChanged(int)));
    stackedWidget.addWidget(splitter_v);
    stackedWidget.addWidget(rightWidget);
    stackedWidget.setCurrentIndex(0);
    QHBoxLayout* hlayout = new QHBoxLayout;
    hlayout->addWidget(Business::getBusiness()->getStepWidget());
    hlayout->addWidget(&stackedWidget);
    hlayout->setStretchFactor(Business::getBusiness()->getStepWidget(),2);
    hlayout->setStretchFactor(&stackedWidget,9);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addLayout(hlayout);
    layout->setMargin(0);
    ui->centralwidget->setLayout(layout);


    Business::getBusiness()->setModelTabWidget(&modelTabWidget);
    Business::getBusiness()->setModelTreeWidget(&modelTreeWidget);
    Business::getBusiness()->setModelTableWidget(&modelTableWidget);
    Business::getBusiness()->setCurveShowAndSetWidget(&curveShowAndSetWidget);
    Business::getBusiness()->setDataTranslationAline(&dataTranslationAline);
    Business::getBusiness()->setDataPrintAndOutput(&dataPrintAndOutput);
    Business::getBusiness()->setStatisticalAnalysisWidget(&statisticalAnalysisWidget);
    Business::getBusiness()->setDateCountTabWidget(&dateCountTabWidget);
    Business::getBusiness()->setViewFormRCS(&viewFormRCS);
    Business::getBusiness()->setViewFromHisgram(&viewFromHisgram);
    QString titleName = QString::fromLocal8Bit("数据分析与查看");
    this->setWindowTitle(titleName);
    connect(Business::getBusiness()->getStepWidget()->getStepWidgetQtoolBox(),SIGNAL(currentChanged(int)),this,SLOT(on_toolBox_currentChanged(int)));
    connect(Business::getBusiness()->getDateCountTabWidget()->getActionState(),SIGNAL(triggered()),this,SLOT(on_addaction_triggered()));
    QFile file("./fileList.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << file.errorString();
    }
    else
    {
        QTextStream inputFile(&file);
        QString line = inputFile.readLine();
        QVector<QString> inputList;
        while(!line.isNull())
        {
            inputList.push_back(line);
            line = inputFile.readLine();
        }
        // 减5是为了去掉.mpro的后缀
        QString fileNames = inputList[0].left(inputList[0].length()-5) + "/data";
        qDebug() << "fileNames == " << fileNames;
        for(int i=1;i<inputList.size();i++)
        {
            // inputList[0] 为工程名字  后续的为文件名字
            QDir dir(fileNames);
            dir.setFilter(QDir::Files);  //  设置过滤器  只加载文件
            QStringList list = dir.entryList(QDir::Files);
            for(int j=0;j<list.size();j++)
            {
                QFileInfo file = list[j];
                if(file.suffix() == "ram" || file.suffix() == "rcs" || file.suffix() == "rcsf" || file.suffix() == "rcsF" || file.suffix() == "rcs2f")
                {
                    if(file.fileName() == inputList[i])
                    {
                        ModelBase* modelObject = Business::getBusiness()->loadModelBase(list[j],fileNames);
                        modelTreeWidget.addModelObject(modelObject);
                        dateCountTabWidget.addModelObject(modelObject);
                        modelTableWidget.addModelObject(modelObject);
//                        if(stackedWidget.currentIndex() == 1)
//                        {
//                            dateCountTabWidget.addModelObject(modelObject);
//                        }
//                        else
//                        {
//                            modelTableWidget.addModelObject(modelObject);
//                        }
                    }
                }
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_toolBox_currentChanged(int index)
{
    //stackedWidget.show();
    if(index == 3)
    {
        stackedWidget.setCurrentIndex(1);
    }
    else
    {
        stackedWidget.setCurrentIndex(0);
    }
}

void MainWindow::on_addaction_triggered()
{
    std::vector<ModelBase *> bases = Business::getBusiness()->getDateCountTabWidget()->getModelBase();
    int count = Business::getBusiness()->getDateCountTabWidget()->getCount();
    QTableWidget *table = Business::getBusiness()->getDateCountTabWidget()->getTableWidget();
    for(int i=0;i<count;i++)
    {
        QTableWidgetItem *item = table->item(i,1);
        if(table->isItemSelected(item))
        {
            viewFormRCS.addModelBase(bases[i]);
            viewFromHisgram.setDrawHistogramChart()->addModelBases(bases[i]);
        }
    }
}
// 加载数据文件
void MainWindow::on_openaction_triggered()
{
    QStringList fileList = QFileDialog::getOpenFileNames(this, tr("file names"), "./", "*.ram *.rcs *.rcsf");
    for(int i = 0; i < fileList.size(); i++)
    {
        ModelBase* modelObject = Business::getBusiness()->loadModelBase(fileList[i].toUtf8());
        modelTreeWidget.addModelObject(modelObject);
        if(stackedWidget.currentIndex() == 1)
        {
            dateCountTabWidget.addModelObject(modelObject);
        }
        else
        {
            modelTableWidget.addModelObject(modelObject);
        }
    }

}
/**
 * @brief MainWindow::on_action_triggered
 * 画单箭头标注
 */
void MainWindow::on_action_triggered()
{
    for(int i = 0;i<4;i++)
    {
        if(Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(i)->getMsigmaBase())
        {
            Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(i)->getMsigmaBase()->getStandIndex(0);
        }
    }
}
/**
 * @brief MainWindow::on_action_2_triggered
 * 画圆圈型备注 和  椭圆标注
 */
void MainWindow::on_action_2_triggered()
{
    for(int i = 0;i<4;i++)
    {
        Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(i)->getMsigmaBase()->getStandIndex(1);
    }
}
/**
 * @brief MainWindow::on_action_3_triggered
 * 画方括号标注
 */
void MainWindow::on_action_3_triggered()
{
    for(int i = 0;i<4;i++)
    {
        Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(i)->getMsigmaBase()->getStandIndex(2);
    }
}
/**
 * @brief MainWindow::on_action_4_triggered
 * 黑色小旗备注
 */
void MainWindow::on_action_4_triggered()
{
    for(int i = 0;i<4;i++)
    {
        Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(i)->getMsigmaBase()->getStandIndex(3);
    }
}
/**
 * @brief MainWindow::on_action_6_triggered
 * 撤销
 */
void MainWindow::on_action_6_triggered()
{

    for(int i = 0;i<4;i++)
    {
        Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(i)->getMsigmaBase()->getStandIndex(8);
    }
}
/**
 * @brief MainWindow::on_action_8_triggered
 * 删除所有标注
 */
void MainWindow::on_action_8_triggered()
{
    for(int i = 0;i<4;i++)
    {
        Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(i)->getMsigmaBase()->getStandIndex(9);
    }
}
/**
 * @brief MainWindow::on_action_9_triggered
 * 椭圆带箭头标注
 */
void MainWindow::on_action_9_triggered()
{
    for(int i = 0;i<4;i++)
    {
        Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(i)->getMsigmaBase()->getStandIndex(4);
    }
}
/**
 * @brief MainWindow::on_action_10_triggered
 * 双箭头标注
 */
void MainWindow::on_action_10_triggered()
{
    for(int i = 0;i<4;i++)
    {
        Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(i)->getMsigmaBase()->getStandIndex(5);
    }
}
/**
 * @brief MainWindow::on_action_11_triggered
 * 幅值差异标注
 */
void MainWindow::on_action_11_triggered()
{
    for(int i = 0;i<4;i++)
    {
        Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(i)->getMsigmaBase()->getStandIndex(6);
    }
}
/**
 * @brief MainWindow::on_action_12_triggered
 * 关键节点标注
 */
void MainWindow::on_action_12_triggered()
{
    for(int i = 0;i<4;i++)
    {
        Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(i)->getMsigmaBase()->getStandIndex(7);
    }
}
/**
 * @brief MainWindow::on_action_13_triggered
 * 逐点标注
 */
void MainWindow::on_action_13_triggered()
{
    for(int i = 0;i<4;i++)
    {
        Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(i)->getMsigmaBase()->getStandIndex(10);
    }
}
/**
 * @brief MainWindow::on_action_7_triggered
 * 退出标注模式
 */
void MainWindow::on_action_7_triggered()
{
    for(int i = 0;i<4;i++)
    {
        Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(i)->getMsigmaBase()->getStandIndex(11);
    }
}
/**
 * @brief MainWindow::on_action_14_triggered
 * 文本标注
 */
void MainWindow::on_action_14_triggered()
{
    for(int i = 0;i<4;i++)
    {
        Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(i)->getMsigmaBase()->getStandIndex(12);
    }
}

void MainWindow::on_action_15_triggered()
{
    for(int i = 0;i<4;i++)
    {
        Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(i)->getMsigmaBase()->getStandIndex(13);
    }
}


void MainWindow::on_action_16_triggered()
{
    for(int i = 0;i<4;i++)
    {
        Business::getBusiness()->getModelTabWidget()->getCurrentCurveViewForm()->getViewFromWidget(i)->getMsigmaBase()->getStandIndex(14);
    }
}
