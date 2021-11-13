#include "SpectrogramPlotWidget.h"
#include "ui_SpectrogramPlotWidget.h"

SpectrogramPlotWidget::SpectrogramPlotWidget(QWidget *parent, QString className) :
    QWidget(parent),
    ui(new Ui::SpectrogramPlotWidget),MsigmaBase(className)
{
    ui->setupUi(this);
    d_SpectrogramPlot = new SpectrogramPlot(ui->frame_1, ui->frame_1_colorScale);

}

SpectrogramPlotWidget::~SpectrogramPlotWidget()
{
    delete ui;
    delete d_SpectrogramPlot;
}

void SpectrogramPlotWidget::resizeEvent(QResizeEvent *event)
{
    d_SpectrogramPlot->resize(ui->frame_1->width(), ui->frame_1->height());
    d_SpectrogramPlot->setColorScaleGeometry(0, 0, ui->frame_1_colorScale->width(), ui->frame_1_colorScale->height());
}

void SpectrogramPlotWidget::setModelBases(std::vector<ModelBase *> modelObjects, int index)
{
    clearModelBase();
    if(modelObjects.size() > 0)
    {
        addModelBase(modelObjects[modelObjects.size() - 1]);
    }
}

void SpectrogramPlotWidget::addModelBase(ModelBase *modelObject)
{
    if(modelObject->getClassName() == "ModelRCSF")
    {
//        ModelRCSF* model = (ModelRCSF*)modelObject;
        d_SpectrogramPlot->initData(modelObject);
        d_SpectrogramPlot->setSpectrogramMode(0);//光谱显示模式
        d_SpectrogramPlot->setColorMap(1);//设置色板类型
    }
}

void SpectrogramPlotWidget::clearModelBase()
{
    delete d_SpectrogramPlot;
    d_SpectrogramPlot = new SpectrogramPlot(ui->frame_1, ui->frame_1_colorScale);
    d_SpectrogramPlot->resize(ui->frame_1->width(), ui->frame_1->height());
    d_SpectrogramPlot->setColorScaleGeometry(0, 0, ui->frame_1_colorScale->width(), ui->frame_1_colorScale->height());
    d_SpectrogramPlot->show();
}


