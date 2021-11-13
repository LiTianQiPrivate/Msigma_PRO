#ifndef DRAWHISTOGRAMCHART_H
#define DRAWHISTOGRAMCHART_H

#include <QWidget>
#include "qwt_plot.h"
#include "qwt_plot_multi_barchart.h"
#include "qwt_plot_canvas.h"
#include "qwt_plot_layout.h"
#include "ModelBase.h"
class DrawHistogramChart : public QwtPlot
{
    Q_OBJECT

public:
    explicit DrawHistogramChart(QWidget *parent = nullptr);
    ~DrawHistogramChart();
public:
    QwtPlotMultiBarChart *cruve = nullptr;
public:
    std::vector<std::vector<double>> values;
    void getValues(QVector<QVector<double> > value, std::vector<QString> strs);
    QwtPlotCanvas *backgroundCurve = nullptr;
    void addModelBases(ModelBase *object);
    std::vector<ModelBase *> modelBases;
    void setOrientation( int orientation );
    void setMode( int mode );
    QColor getRandomColor();
};

#endif // DRAWHISTOGRAMCHART_H
