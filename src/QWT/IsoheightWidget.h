#ifndef ISOHEIGHTWIDGET_H
#define ISOHEIGHTWIDGET_H
#include "MsigmaBase.h"
#include <qwt_plot.h>
#include <qwt_plot_spectrogram.h>
#include "MyZoomer.h"
#include <qwt_color_map.h>
#include "qwt_raster_data.h"
#include "ModelBase.h"
#include "qwt_matrix_raster_data.h"
#include <QCheckBox>

/**
 * @brief The IsoheightWidget class
 * 等高线
 */
class IsoheightWidget : public QwtPlot , public MsigmaBase
{
    Q_OBJECT
public:

    IsoheightWidget(QWidget *parent = nullptr, QString className = "IsoheightWidget");
    ~IsoheightWidget();
    void resizeEvent(QResizeEvent *e);
    void setModelBases(std::vector<ModelBase*> modelObjects, int index);
    void addModelBase(ModelBase* modelObject);
    void clearModelBase();
    void showModelBase(int index);
    void hideModelBase(int index);
    bool isVisible(int index);
    void removeModelBase(int index);
    ModelBase* getModelObject(int index);
    void showContour( bool on );
    void showSpectrogram( bool on );
    void on_lineStyleComboBoxActivated(int v,int index){};
private slots:
    void on_checkBoxCorveClick(bool value);
    void on_checkBoxColorClick(bool value);
private:
    QwtPlotSpectrogram *d_spectrogram;
    QwtMatrixRasterData* qwtRasterData; // qwt数据
    int d_mapType;
    int d_alpha;
    QwtPlotZoomer* zoomer;
    QCheckBox* checkBoxCorve; // 显示轮廓线图控件
    QCheckBox* checkBoxColor; // 显示色差图控件
};

#endif // ISOHEIGHTWIDGET_H
