#ifndef SPECTROGRAMPLOT_H
#define SPECTROGRAMPLOT_H

#include <qwt_plot.h>
#include <qwt_plot_spectrogram.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_marker.h>
#include <qwt_color_map.h>
#include <qwt_plot_spectrogram.h>
#include <qwt_plot_layout.h>
#include <qwt_matrix_raster_data.h>
#include <qwt_scale_widget.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_renderer.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_canvas.h>
#include <qwt_scale_engine.h>
#include <fstream>
#include "Object/ModelRCSF.h"

////
/// \brief The SpectrogramPlot class
/// 光谱图
/// 二维像图像
/// 包含角度、频率、rcs
/// 格式：.rcsF
///
class MyZoomer1;
class SpectrogramPlot: public QwtPlot
{
public:
    SpectrogramPlot(QWidget * parent = NULL, QWidget *colorScaleParent = nullptr);
    ~SpectrogramPlot();
    void initData(ModelBase *modelObject);
    void setH_MarkerPos(double x, double y); // 设置横向标记线位置
    void setV_MarkerPos(double x, double y); // 设置横向标记线位置

    void setSpectrogramMode( int mode);//设置光谱图显示类型0or1
    void setColorMap( int type );//设置色板类型
    void setColorRange(double colorMin,double colorMax);//设置色板对应数值的范围
    void showContour(bool on);//是否显示等高线
    void setContour(double min,double max,double step);//设置等高线
    void setColorScaleGeometry(int x, int y, int w, int h);
    void clearData();

private:
    QwtMatrixRasterData* qwtMatrixRasterData; // qwt数据
    QwtPlotMarker *h_marker,*v_marker;  // 横纵标记线
//    QwtLinearColorMap* colorMap1;
//    QwtLinearColorMap* colorMap2;
//    QwtLinearColorMap* colorMap3;
//    QwtLinearColorMap* colorMap4;
    QwtPlotSpectrogram *d_spectrogram;
    QwtScaleWidget *d_colorScale;
    MyZoomer1* zoomer;
    QwtPlotMagnifier *magnifier;

    double xmin,xmax,ymin,ymax,zmin,zmax;
    QVector<double> values;
    double color_min,color_max;
};

#endif // SPECTROGRAMPLOT_H
