#include "DrawHistogramChart.h"
#include "qwt_column_symbol.h"
#include "qwt_legend.h"
#include "qwt_scale_draw.h"
#include "DistScaleDraw.h"

DrawHistogramChart::DrawHistogramChart(QWidget *parent) :
    QwtPlot(parent)
{
    setAutoFillBackground( true );
    //设置背景自动填充
    setPalette( Qt::white );
    //设置调色板
    canvas()->setPalette( QColor( "LemonChiffon" ) );
    //为画布设置调色板
    //setTitle( "Bar Chart" );
    cruve = new QwtPlotMultiBarChart( "Bar Chart " );
    //新建一个QwtPlotMultiBarChart，用来存储柱状图数据
    cruve->setLayoutPolicy( QwtPlotMultiBarChart::FixedSampleSize );
    cruve->setLayoutHint(150);
    //设置柱状图布局策略
    cruve->setSpacing( 20 );
    //设置空格
    cruve->setMargin( 3 );
    //设置边缘留白
    cruve->attach( this );
    //将柱状图数据添加到画板上
    insertLegend( new QwtLegend(),QwtPlot::BottomLegend );
     //插入图例
    setAutoReplot( true );
    //设置自动刷新
}

DrawHistogramChart::~DrawHistogramChart()
{
    delete backgroundCurve;
}

void DrawHistogramChart::getValues(QVector<QVector<double> > value,std::vector<QString> strs)
{
    double y1 = 999;
    double y2 = -999;
    for(int i = 0;i<value.size();i++)
    {
        for(int j = 0;j<value[i].size();j++)
        {
            if(value[i][j] > y2)
            {
                y2 = value[i][j];
            }
            if(value[i][j] < y1)
            {
                y1 = value[i][j];
            }
        }
    }
    //setAxisScale(QwtPlot::yLeft,int(y1), int(y2+0.5));
    QList<QwtText> titles;
    for ( int i = 0; i < strs.size(); i++ )
    {
       QString title = strs[i];
       titles.push_back(title);
    }
    cruve->setBarTitles( titles );
    cruve->setLegendIconSize( QSize( 10,12 ) );
    cruve->setSamples(value);
    for(int i=0;i<value[0].size();i++)
    {
        QwtColumnSymbol *symbol = new QwtColumnSymbol(QwtColumnSymbol::Box);
        symbol->setLineWidth(2);
        symbol->setFrameStyle( QwtColumnSymbol::Raised );
        symbol->setPalette(getRandomColor());
        cruve->setSymbol(i,symbol);
    }
    setMode(0);
    setOrientation(0);
    this->replot();
}

void DrawHistogramChart::addModelBases(ModelBase *object)
{
    modelBases.push_back(object);
}
void DrawHistogramChart::setOrientation( int orientation )
{
    QwtPlot::Axis axis1, axis2;

    if ( orientation == 0 )
    {
        axis1 = QwtPlot::xBottom;
        axis2 = QwtPlot::yLeft;
        cruve->setLayoutHint(150);
        cruve->setOrientation( Qt::Vertical );
    }
    else
    {
        axis1 = QwtPlot::yLeft;
        axis2 = QwtPlot::xBottom;
        cruve->setLayoutHint(80);
        cruve->setOrientation( Qt::Horizontal );
    }
    if(cruve->dataSize() > 0)
    {
        if(cruve->dataSize() > 1)
        {
            setAxisScale( axis1, 0, cruve->dataSize() - 1, 1.0 );
        }
        else
        {
            setAxisScale( axis1, 0, 1, 1.0 );  //  一定要设置间隔1.0 函数默认间隔为5 若不设置 当曲线为一条时  显示五个柱
        }
    }
    if(cruve->dataSize() > 10 && orientation == 0)
    {
        cruve->setLayoutHint(100);
    }
    QStringList labels;
    for(int i=0;i<modelBases.size();i++)
    {
        QString str = modelBases[i]->findDataInfo(QString::fromLocal8Bit(WORK_FPS));
        labels += str;
    }
    setAxisScaleDraw(axis1, new DistScaleDraw(labels,orientation));
    setAxisAutoScale( axis2 );
    // 设置刻度值样式
    QwtScaleDraw *scaleDraw1 = axisScaleDraw( axis1 );
    scaleDraw1->enableComponent( QwtScaleDraw::Backbone, false );
    scaleDraw1->enableComponent( QwtScaleDraw::Ticks, false );

    QwtScaleDraw *scaleDraw2 = axisScaleDraw(axis2);
    scaleDraw2->enableComponent( QwtScaleDraw::Backbone, true );
    scaleDraw2->enableComponent( QwtScaleDraw::Ticks, true );

    plotLayout()->setAlignCanvasToScale( axis1, true );
    plotLayout()->setAlignCanvasToScale( axis2, false );

    plotLayout()->setCanvasMargin( 0 );
    //plotLayout()->setAlignCanvasToScales(true);
    updateCanvasMargins();

    replot();
}
void DrawHistogramChart::setMode( int mode )
{
    if ( mode == 0 )
    {
        cruve->setStyle( QwtPlotMultiBarChart::Grouped );
    }
    else
    {
        cruve->setStyle( QwtPlotMultiBarChart::Stacked );
    }
}

QColor DrawHistogramChart::getRandomColor()
{
    static int _colorIndex = 0;
    std::vector<QColor> colors;
    //-----------------预留颜色----------------------//
    colors.push_back(QColor(255, 0, 0));colors.push_back(QColor(0, 255, 0));colors.push_back(QColor(0, 0, 255));colors.push_back(QColor(255, 255, 0));
    colors.push_back(QColor(0, 255, 255));colors.push_back(QColor(255, 0, 255));colors.push_back(QColor(200, 100, 0));colors.push_back(QColor(100, 200, 0));
    colors.push_back(QColor(200, 0, 100));colors.push_back(QColor(0, 200, 100));colors.push_back(QColor(0, 100, 200));colors.push_back(QColor(100, 0, 200));
    colors.push_back(QColor(100, 50, 0));colors.push_back(QColor(50, 100, 0));colors.push_back(QColor(100, 0, 50));colors.push_back(QColor(0, 100, 50));
    colors.push_back(QColor(0, 50, 100));colors.push_back(QColor(50, 0, 100));colors.push_back(QColor(250, 150, 50));colors.push_back(QColor(150, 50, 250));
    colors.push_back(QColor(50, 250, 150));colors.push_back(QColor(180, 100, 10));colors.push_back(QColor(100, 10, 180));colors.push_back(QColor(10, 180, 100));
    QColor color = colors[_colorIndex];
    _colorIndex++;
    if(_colorIndex >= colors.size())
    {
        _colorIndex = 0;
    }
    return color;
}

