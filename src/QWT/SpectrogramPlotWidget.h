#ifndef SPECTROGRAMPLOTWIDGET_H
#define SPECTROGRAMPLOTWIDGET_H

#include <QWidget>
#include "SpectrogramPlot.h"
#include "ModelBase.h"
#include "MsigmaBase.h"

namespace Ui {
class SpectrogramPlotWidget;
}
/**
 * @brief The SpectrogramPlotWidget class
 * 平面色彩图
 */
class SpectrogramPlotWidget : public QWidget, public MsigmaBase
{
    Q_OBJECT

public:
    explicit SpectrogramPlotWidget(QWidget *parent = nullptr, QString className = "SpectrogramPlotWidget");
    ~SpectrogramPlotWidget();
    void resizeEvent(QResizeEvent *event);
    void setModelBases(std::vector<ModelBase*> modelObjects, int index);
    void addModelBase(ModelBase* modelObject);

    void clearModelBase();



private:
    Ui::SpectrogramPlotWidget *ui;
    SpectrogramPlot* d_SpectrogramPlot;
};

#endif // SPECTROGRAMPLOTWIDGET_H
