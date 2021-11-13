#include "spectrogramplot.h"

using namespace std;

class MyZoomer1: public QwtPlotZoomer
{
public:
    MyZoomer1( QWidget *canvas ):
        QwtPlotZoomer( canvas )
    {
        setTrackerMode( AlwaysOn );
    }

    virtual QwtText trackerTextF( const QPointF &pos ) const
    {
        QColor bg( Qt::white );
        bg.setAlpha( 200 );

//        QString str = QwtPlotZoomer::trackerTextF( pos ).text() + " 5 5 ";
//        QwtText text(str);
        QwtText text = QwtPlotZoomer::trackerTextF( pos );

        text.setBackgroundBrush( QBrush( bg ) );
        return text;
    }
};
class ColorMap1 : public QwtLinearColorMap
{
public:
    ColorMap1() : QwtLinearColorMap(Qt::darkBlue, Qt::red)
    {
        int count = 10;
        QColor cc[10];
        cc[0].setRgb(127,127,127);    cc[1].setRgb(192,192,254);   cc[2].setRgb(122,114,238.5);    cc[3].setRgb(1,160,246);
        cc[4].setRgb(0,236,236);   cc[5].setRgb(1,144,0); cc[6].setRgb(255,255,0);  cc[7].setRgb(231,192,0);
        cc[8].setRgb(255,144,0); cc[9].setRgb(255,0,0);

        for(int i = 0;i < count;i++)
        {
            QRgb mRgb = qRgb(cc[i].red(),cc[i].green(),cc[i].blue());
            QColor mColor = QColor(mRgb);
            addColorStop(double(i+1)/double(count), mColor);
        }
    }
};
class ColorMap2 : public QwtLinearColorMap
{
    public:
    ColorMap2() : QwtLinearColorMap()
    {
        int count = 10;
        QColor cc[10];
        cc[0].setRgb(127,127,127);    cc[1].setRgb(192,192,254);   cc[2].setRgb(122,114,238.5);    cc[3].setRgb(1,160,246);
        cc[4].setRgb(0,236,236);   cc[5].setRgb(1,144,0); cc[6].setRgb(255,255,0);  cc[7].setRgb(231,192,0);
        cc[8].setRgb(255,144,0); cc[9].setRgb(255,0,0);

        for(int i = 0;i < count;i++)
        {
            QRgb mRgb = qRgb(cc[i].red(),cc[i].green(),cc[i].blue());
            QColor mColor = QColor(mRgb);
            addColorStop(double(i+1)/double(count), mColor);
        }
    }
};
class ColorMap3 : public QwtLinearColorMap
{
    public:
    ColorMap3() : QwtLinearColorMap()
    {
        int count = 22;
        QColor c[22];
        c[0].setRgb(0,0,152);    c[1].setRgb(0,0,186);   c[2].setRgb(0,0,231);    c[3].setRgb(0,34,234);
        c[4].setRgb(0,77,253);   c[5].setRgb(0,130,243); c[6].setRgb(0,179,255);  c[7].setRgb(0,219,255);
        c[8].setRgb(15,252,240); c[9].setRgb(62,251,191);c[10].setRgb(93,255,137);c[11].setRgb(154,255,94);
        c[12].setRgb(198,250,38);c[13].setRgb(251,254,7);c[14].setRgb(254,200,20);c[15].setRgb(255,156,1);
        c[16].setRgb(252,109,0); c[17].setRgb(230,74,1); c[18].setRgb(240,13,0);  c[19].setRgb(228,4,1);
        c[20].setRgb(182,0,0);   c[21].setRgb(116,2,9);
        for(int i = 0;i < count;i++)
        {
            QRgb mRgb = qRgb(c[i].red(),c[i].green(),c[i].blue());
            QColor mColor = QColor(mRgb);
            addColorStop(double(i+1)/double(count), mColor);
        }
    }
};
class ColorMap4 : public QwtLinearColorMap
{
    public:
    ColorMap4() : QwtLinearColorMap(Qt::darkBlue, Qt::darkRed)
    {
        int count = 22;
        QColor c[22];
        c[0].setRgb(0,0,152),    c[1].setRgb(0,0,186),    c[2].setRgb(0,0,231),    c[3].setRgb(0,34,234),  c[4].setRgb(0,77,253);
        c[5].setRgb(0,130,243),  c[6].setRgb(0,179,255),  c[7].setRgb(0,219,255),  c[8].setRgb(15,252,240),c[9].setRgb(62,251,191);
        c[10].setRgb(93,255,137),c[11].setRgb(154,255,94),c[12].setRgb(198,250,38),c[13].setRgb(251,254,7),c[14].setRgb(254,200,20);
        c[15].setRgb(255,156,1), c[16].setRgb(252,109,0), c[17].setRgb(230,74,1),  c[18].setRgb(240,13,0), c[19].setRgb(228,4,1);
        c[20].setRgb(182,0,0),   c[21].setRgb(116,2,9);
        for(int i = 0;i < count;i++)
        {
            QRgb mRgb = qRgb(c[i].red(),c[i].green(),c[i].blue());
            QColor mColor = QColor(mRgb);
            addColorStop(double(i+1)/double(count), mColor);
        }
    }
};

SpectrogramPlot::SpectrogramPlot( QWidget *parent, QWidget* colorScaleParent):
    QwtPlot( parent )
{
    xmin = xmax = ymin = ymax = zmin = zmax =-9999;
//    m_parent = parent;

    qwtMatrixRasterData = new QwtMatrixRasterData;
    h_marker = new QwtPlotMarker;
    h_marker->setLineStyle( QwtPlotMarker::HLine );
    h_marker->setLinePen(QColor(Qt::yellow), 3, Qt::DashDotLine );
    h_marker->setVisible( true );
    h_marker->setItemAttribute( QwtPlotItem::Legend, true );
    h_marker->attach( this );

    v_marker = new QwtPlotMarker;
    v_marker->setLineStyle( QwtPlotMarker::VLine );
    v_marker->setLinePen(QColor(Qt::green), 3, Qt::DashLine );
    v_marker->setVisible( true );
    v_marker->setItemAttribute( QwtPlotItem::Legend, true );
    v_marker->attach( this );

    d_spectrogram = new QwtPlotSpectrogram();
    d_colorScale = new QwtScaleWidget(colorScaleParent); // 颜色条
    d_colorScale->show();

    zoomer = new MyZoomer1( canvas() );
    zoomer->setMousePattern( QwtEventPattern::MouseSelect2,
        Qt::RightButton, Qt::ControlModifier );
    zoomer->setMousePattern( QwtEventPattern::MouseSelect3,
        Qt::RightButton );
    zoomer->setRubberBandPen( QColor( Qt::green ) ); //勾选扩大区域边界颜色
    magnifier = new QwtPlotMagnifier( canvas() );
    magnifier->setAxisEnabled( QwtPlot::yRight, false );
}

SpectrogramPlot::~SpectrogramPlot()
{
    delete d_spectrogram;
    delete h_marker;
    delete v_marker;
//    delete qwtMatrixRasterData;
//    delete colorMap1;
//    delete colorMap2;
//    delete colorMap3;
//    delete colorMap4;
    delete zoomer;
    delete magnifier;
}

void SpectrogramPlot::initData(ModelBase *modelObject)
{
    ////////////////加载数据///////////////////
    std::vector<std::vector<Point3D>> lines = modelObject->getPointDatas();
    xmin = 10000000,xmax = -100000000;
    ymin = 10000000,ymax = -100000000;
    zmin = 10000000,zmax = -100000000;
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

    qwtMatrixRasterData->setValueMatrix(values, (int)lines.size());
    qwtMatrixRasterData->setInterval( Qt::XAxis,QwtInterval( xmin,xmax, QwtInterval::ExcludeMaximum ) );
    qwtMatrixRasterData->setInterval( Qt::YAxis,QwtInterval( ymin,ymax, QwtInterval::ExcludeMaximum ) );
    qwtMatrixRasterData->setInterval( Qt::ZAxis,QwtInterval( zmin,zmax, QwtInterval::ExcludeMaximum ) );

    d_spectrogram->setRenderThreadCount( 0 ); // use system specific thread count
    d_spectrogram->setColorMap(new ColorMap1());
    d_spectrogram->setData(qwtMatrixRasterData);
    d_spectrogram->attach( this );
    /////////////////////////设置颜色条///////////////////////////
    const QwtInterval zInterval = d_spectrogram->data()->interval( Qt::ZAxis );
    d_colorScale->setColorBarEnabled( true );
    d_colorScale->setColorBarWidth( 40 );
    d_colorScale->setColorMap( zInterval, new ColorMap1());
    QwtLinearScaleEngine scaleEngine;
    d_colorScale->setScaleDiv(scaleEngine.divideScale( zInterval.minValue(), zInterval.maxValue(), 8, 5 ) );
    int startDist, endDist;
    d_colorScale->getBorderDistHint( startDist, endDist );
    d_colorScale->setBorderDist( startDist, endDist );
    ///////////////////////////////////////////////////////


//    QwtPlotPanner *panner = new QwtPlotPanner( canvas() );
//    panner->setAxisEnabled( QwtPlot::yRight, false );
//    panner->setMouseButton( Qt::MidButton );

    //等高线
//    QList<double> contourLevels;
//    for ( double level = -5; level < 30.0; level += 1.0 )
//        contourLevels += level;
//    d_spectrogram->setContourLevels( contourLevels );

    //标记线
    setH_MarkerPos((xmax + xmin)/2, (ymax + ymin)/2);
    setV_MarkerPos((xmax + xmin)/2, (ymax + ymin)/2);
}

void SpectrogramPlot::setH_MarkerPos(double x, double y)
{
    h_marker->setValue(x, y);
    replot();
}

void SpectrogramPlot::setV_MarkerPos(double x, double y)
{
    v_marker->setValue(x, y);
    replot();
}

void SpectrogramPlot::setSpectrogramMode(int mode)
{
    qwtMatrixRasterData->setResampleMode(static_cast<QwtMatrixRasterData::ResampleMode>( mode ));
    replot();
}

void SpectrogramPlot::setColorMap(int type)
{
    const QwtInterval zInterval = d_spectrogram->data()->interval( Qt::ZAxis );

    switch( type )
    {
    case 0:
    {
        d_spectrogram->setColorMap(new ColorMap1());
        d_colorScale->setColorMap( zInterval, new ColorMap1());
        break;
    }

    case 1:
    {
        d_spectrogram->setColorMap(new ColorMap2());
        d_colorScale->setColorMap( zInterval, new ColorMap2());
        break;
    }

    case 2:
    {
        d_spectrogram->setColorMap(new ColorMap3());
        d_colorScale->setColorMap( zInterval, new ColorMap3());
        break;
    }

    case 3:
    {
        d_spectrogram->setColorMap(new ColorMap4());
        d_colorScale->setColorMap( zInterval, new ColorMap4());
        break;
    }
    }
    replot();
}


void SpectrogramPlot::setColorRange(double colorMin, double colorMax)
{

    QwtLinearScaleEngine scaleEngine;
    d_colorScale->setScaleDiv(scaleEngine.divideScale( colorMin, colorMax, 8, 5 ) );

    setColorMap(0);

    color_min = colorMin;
    color_max = colorMax;

    replot();
}

void SpectrogramPlot::showContour(bool on)
{
    d_spectrogram->setDisplayMode( QwtPlotSpectrogram::ContourMode, on );
    replot();
}

void SpectrogramPlot::setContour(double min, double max, double step)
{
    QList<double> contourLevels;
    for ( double level = min; level < max; level += step )
        contourLevels += level;
    d_spectrogram->setContourLevels( contourLevels );
    replot();
}

void SpectrogramPlot::setColorScaleGeometry(int x, int y, int w, int h)
{
    d_colorScale->setGeometry(x, y, w, h);
}

void SpectrogramPlot::clearData()
{

}
