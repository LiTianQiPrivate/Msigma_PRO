#include "IsoheightWidget.h"
#include <qnumeric.h>
#include <qwt_color_map.h>
#include <qwt_plot_spectrogram.h>
#include <qwt_scale_widget.h>
#include <qwt_scale_draw.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_renderer.h>
#include "Point3D.h"


IsoheightWidget::IsoheightWidget(QWidget *parent, QString className):QwtPlot(parent),MsigmaBase(className)
{
    d_spectrogram = new QwtPlotSpectrogram();
    d_spectrogram->setRenderThreadCount( 0 ); // use system specific thread count
    d_spectrogram->setCachePolicy( QwtPlotRasterItem::PaintCache );

    qwtRasterData = new QwtMatrixRasterData();
    zoomer = new MyZoomer( canvas() );

    QwtPlotPanner *panner = new QwtPlotPanner( canvas() );
    panner->setAxisEnabled( QwtPlot::yRight, false);
    panner->setMouseButton( Qt::MidButton );


    checkBoxCorve = new QCheckBox(this);
    checkBoxCorve->setText(QString::fromLocal8Bit("Curve"));
    checkBoxCorve->show();
    connect(checkBoxCorve, SIGNAL(clicked(bool)), this, SLOT(on_checkBoxCorveClick(bool)));

    checkBoxColor = new QCheckBox(this);
    checkBoxColor->setText(QString::fromLocal8Bit("Color"));
    checkBoxColor->show();
    connect(checkBoxColor, SIGNAL(clicked(bool)), this, SLOT(on_checkBoxColorClick(bool)));
    checkBoxColor->setChecked(true);

}

IsoheightWidget::~IsoheightWidget()
{
    delete checkBoxCorve;
    delete checkBoxColor;
//    delete qwtRasterData;
    delete d_spectrogram;
//
    delete zoomer;

}

void IsoheightWidget::resizeEvent(QResizeEvent *e)
{
    QwtPlot::resizeEvent(e);
    int thisW = this->width();
    int thisH = this->height();

    checkBoxCorve->move(thisW - checkBoxCorve->width() - 30, 10);
    checkBoxColor->move(thisW - checkBoxColor->width() - 30, 30);
}

void IsoheightWidget::setModelBases(std::vector<ModelBase *> modelObjects, int index)
{
    clearModelBase();
    for(int i = 0; i < modelObjects.size(); i++)
    {
        addModelBase(modelObjects[i]);
    }
}

void IsoheightWidget::addModelBase(ModelBase *modelObject)
{
    modelBases.push_back(modelObject);
    std::vector<std::vector<Point3D>> lines = modelObject->getPointDatas();
    double xmin = 10000000,xmax = -100000000;
    double ymin = 10000000,ymax = -100000000;
    double zmin = 10000000,zmax = -100000000;
    QVector<double> values;
    for(int i = 0; i < lines.size(); i++)
    {
        std::vector<Point3D>& points = lines[i];
        for(int j = 0; j < points.size(); j++)
        {
            Point3D& p = points[j];
            values.push_back(p.z);
            if(xmin > p.x)
            {
                xmin = p.x;
            }
            if(xmax < p.x)
            {
                xmax = p.x;
            }
            if(ymin > p.y)
            {
                ymin = p.y;
            }
            if(ymax < p.y)
            {
                ymax = p.y;
            }
            if(zmin > p.z)
            {
                zmin = p.z;
            }
            if(zmax < p.z)
            {
                zmax = p.z;
            }
        }
    }

    QList<double> contourLevels;
    double stepValue = (zmax - zmin)/10;
    for ( double level = zmin; level < zmax; level += stepValue )
        contourLevels += level;
    d_spectrogram->setContourLevels( contourLevels );
    qwtRasterData->setValueMatrix(values, (int)lines.size());
    qwtRasterData->setInterval( Qt::XAxis,QwtInterval( xmin,xmax) );
    qwtRasterData->setInterval( Qt::YAxis,QwtInterval( ymin,ymax) );
    qwtRasterData->setInterval( Qt::ZAxis,QwtInterval( zmin,zmax) );
    d_spectrogram->setData(qwtRasterData);
    d_spectrogram->attach( this );
    const QwtInterval zInterval = d_spectrogram->data()->interval( Qt::ZAxis );

    QwtScaleWidget *rightAxis = axisWidget( QwtPlot::yRight );
    rightAxis->setColorBarEnabled( true );
    setAxisScale( QwtPlot::yRight, zInterval.minValue(), zInterval.maxValue() );
    enableAxis( QwtPlot::yRight );

    plotLayout()->setAlignCanvasToScales( true );

    QwtLinearColorMap* colorMap1 = new QwtLinearColorMap(Qt::darkCyan, Qt::red, QwtColorMap::RGB);
    colorMap1->addColorStop( 0.1, Qt::cyan );
    colorMap1->addColorStop( 0.6, Qt::green );
    colorMap1->addColorStop( 0.95, Qt::yellow );

    QwtLinearColorMap* colorMap2 = new QwtLinearColorMap(Qt::darkCyan, Qt::red, QwtColorMap::RGB);
    colorMap2->addColorStop( 0.1, Qt::cyan );
    colorMap2->addColorStop( 0.6, Qt::green );
    colorMap2->addColorStop( 0.95, Qt::yellow );

    d_spectrogram->setColorMap(colorMap1);
    rightAxis->setColorMap( zInterval, colorMap2);
/////////
    zoomer->setMousePattern( QwtEventPattern::MouseSelect2,
        Qt::RightButton, Qt::ControlModifier );
    zoomer->setMousePattern( QwtEventPattern::MouseSelect3,
        Qt::RightButton );

    const QFontMetrics fm( axisWidget( QwtPlot::yLeft )->font() );
    QwtScaleDraw *sd = axisScaleDraw( QwtPlot::yLeft );
    sd->setMinimumExtent( fm.width( "100.00" ) );

    const QColor c( Qt::darkBlue );
    zoomer->setRubberBandPen( c );
    zoomer->setTrackerPen( c );

}

void IsoheightWidget::clearModelBase()
{
    modelBases.clear();
}

void IsoheightWidget::showModelBase(int index)
{

}

void IsoheightWidget::hideModelBase(int index)
{

}

bool IsoheightWidget::isVisible(int index)
{
    return false;
}

void IsoheightWidget::removeModelBase(int index)
{

}

ModelBase *IsoheightWidget::getModelObject(int index)
{
    return modelBases[index];
}

void IsoheightWidget::showContour(bool on)
{
    d_spectrogram->setDisplayMode( QwtPlotSpectrogram::ContourMode, on );
    replot();
}

void IsoheightWidget::showSpectrogram(bool on)
{
    d_spectrogram->setDisplayMode( QwtPlotSpectrogram::ImageMode, on );
    d_spectrogram->setDefaultContourPen(
        on ? QPen( Qt::black, 0 ) : QPen( Qt::NoPen ) );

    replot();
}

void IsoheightWidget::on_checkBoxCorveClick(bool value)
{
    showContour(value);
}

void IsoheightWidget::on_checkBoxColorClick(bool value)
{
    showSpectrogram(value);
}
