#include "QwtPlotBase.h"
#include <QMessageBox>
#include <QPalette>

QwtPlotBase::QwtPlotBase(QWidget *parent, QString className):QwtPlot(parent),MsigmaBase(className)
{
    setAutoFillBackground(true);
    //---------设置画布---------//
    backgroundCurve=new QwtPlotCanvas();
    backgroundCurve->setPalette(Qt::white);
    backgroundCurve->setBorderRadius(10);
    setCanvas( backgroundCurve );
    plotLayout()->setAlignCanvasToScales( true );

    setAxisTitle(QwtPlot::yLeft, "Y" );
    setAxisTitle(QwtPlot::xBottom, "X" );
    //----------------设置栅格线-------------------//
    grid = new QwtPlotGrid;
    grid->enableX( true );//设置网格线
    grid->enableY( true );
    grid->setMajorPen( Qt::black, 0, Qt::DotLine );
    grid->attach( this );

    picker = new MyZoomer(canvas());
    picker->setMsigmaBase(this);
    picker->setStateMachine(new QwtPickerTrackerMachine  ());
    picker->setRubberBandPen(QColor(Qt::blue));//线的颜色
    picker->setRubberBand(QwtPicker::CrossRubberBand);
    picker->setTrackerMode(QwtPicker::AlwaysOn);//被激活时候显示
    picker->setTrackerPen(QColor(Qt::black));//字的颜色
    zoomer = new QwtPlotZoomer( canvas() );
    zoomer->setMousePattern( QwtEventPattern::MouseSelect2,
        Qt::LeftButton ,Qt::ControlModifier );
    const QColor c( Qt::darkBlue );
    zoomer->setRubberBandPen(QColor(Qt::blue));
    //zoomer->setRubberBand(QwtPlotZoomer::CrossRubberBand);
    zoomer->setTrackerPen(QColor(Qt::black));
    panner = new QwtPlotPanner(canvas());
    panner->setMouseButton(Qt::RightButton);
    magnifier = new QwtPlotMagnifier( canvas() );
    magnifier->setAxisEnabled( QwtPlot::yRight, false );

    setAutoReplot( true );
}

QwtPlotBase::~QwtPlotBase()
{
    delete panner;
    delete magnifier;
    delete zoomer;
    delete picker;
    delete grid;
    delete backgroundCurve;
}
void QwtPlotBase::getStandIndex(int index)
{
    if(this->modelBases.empty())
    {
        //QMessageBox::information(this, QString::fromLocal8Bit("数据加载失败！"), QString::fromLocal8Bit("请先加载数据!"));
        return ;
    }
    if(index == 0)   //  画箭头标注
    {
        if(zoomer)
        {
            delete zoomer;
            zoomer = NULL;
        }
        picker->setRubberBand(QwtPicker::NoRubberBand);
        picker->setDrawShapeType(0);
        update();
    }
    else if(index == 1)   //  画圆圈标注
    {
        if(zoomer)
        {
            delete zoomer;
            zoomer = NULL;
        }
        picker->setRubberBand(QwtPicker::NoRubberBand);
        picker->setDrawShapeType(1);
        update();
    }
    else if(index == 2)   //   方括号标注
    {
        if(zoomer)
        {
            delete zoomer;
            zoomer = NULL;
        }
        picker->setRubberBand(QwtPicker::NoRubberBand);
        picker->setDrawShapeType(2);
        update();
    }
    else if(index == 3) //  画黑色小旗标注
    {
        if(zoomer)
        {
            delete zoomer;
            zoomer = NULL;
        }
        picker->setRubberBand(QwtPicker::NoRubberBand);
        picker->setDrawShapeType(3);
        update();
    }
    else if(index == 4)   //  椭圆带箭头
    {
        if(zoomer)
        {
            delete zoomer;
            zoomer = NULL;
        }
        picker->setRubberBand(QwtPicker::NoRubberBand);
        picker->setDrawShapeType(4);
        update();
    }
    else if(index == 5)    // 双箭头
    {
        if(zoomer)
        {
            delete zoomer;
            zoomer = NULL;
        }
        picker->setRubberBand(QwtPicker::NoRubberBand);
        picker->setDrawShapeType(5);
        update();
    }
    else if(index == 6)   // 幅值差异
    {
        if(zoomer)
        {
            delete zoomer;
            zoomer = NULL;
        }
        picker->setRubberBand(QwtPicker::NoRubberBand);
        picker->setDrawShapeType(6);
        update();
    }
    else if(index == 7)   // 关键点标注
    {
        if(zoomer)
        {
            delete zoomer;
            zoomer = NULL;
        }
        drawLineFlag = true;
        this->replot();
        picker->setRubberBand(QwtPicker::NoRubberBand);
        picker->setDrawShapeType(7);
        update();
    }
    else if(index == 10)    // 逐点标注
    {
        if(zoomer)
        {
            delete zoomer;
            zoomer = NULL;
        }
        drawLineFlag = false;

        picker->setRubberBand(QwtPicker::NoRubberBand);
        picker->setDrawShapeType(7);
        this->replot();
        update();
    }
    else if(index == 11)   //  取消标注
    {
        zoomer = new QwtPlotZoomer( canvas() );
        zoomer->setMousePattern( QwtEventPattern::MouseSelect2,
            Qt::LeftButton ,Qt::ControlModifier );
        const QColor c( Qt::darkBlue );
        zoomer->setRubberBandPen(QColor(Qt::blue));
        zoomer->setTrackerPen(QColor(Qt::black));
        this->replot();
        picker->setDrawShapeType(9);
        picker->setRubberBand(QwtPicker::CrossRubberBand);
        update();
    }
    else if(index == 12)    // 文本标注
    {
        if(zoomer)
        {
            delete zoomer;
            zoomer = NULL;
        }
        drawLineFlag = false;

        picker->setRubberBand(QwtPicker::NoRubberBand);
        picker->setDrawShapeType(12);
        this->replot();
        update();
    }
    else if(index == 13)
    {
        if(zoomer)
        {
            delete zoomer;
            zoomer = NULL;
        }
        drawLineFlag = false;

        picker->setRubberBand(QwtPicker::NoRubberBand);
        picker->setDrawShapeType(13);
        this->replot();
        update();
    }
    else if(index == 8)    // 撤销标注
    {
        this->removeItem(getLastDrawBase());
        this->replot();
        if(drawBases.size() > 0)
        {
            drawBases.pop_back();
        }
        picker->setRubberBand(QwtPicker::CrossRubberBand);
        picker->setDrawShapeType(8);
        update();
    }
    else if(index == 9)    //  删除所有标注
    {
        for(int i=0;i<drawBases.size();i++)
        {
            this->removeItem(drawBases[i]);
            delete drawBases[i];
        }
        drawBases.clear();
        zoomer = new QwtPlotZoomer( canvas() );
        zoomer->setMousePattern( QwtEventPattern::MouseSelect2,
            Qt::LeftButton ,Qt::ControlModifier );
        const QColor c( Qt::darkBlue );
        zoomer->setRubberBandPen(QColor(Qt::blue));
        zoomer->setTrackerPen(QColor(Qt::black));
        this->replot();
        picker->setRubberBand(QwtPicker::CrossRubberBand);
        picker->setDrawShapeType(9);
        update();
    }
}
void QwtPlotBase::paintArrow(QPointF beginPoint, QPointF endPoint)
{
    if(drawBases.size() == 0)
    {
        return;
    }
    drawBase = getLastDrawBase();
    drawBase->setPoint(beginPoint,endPoint);
    drawBase->setRenderHint(QwtPlotItem::RenderAntialiased);
    drawBase->attach(this);
    this->replot();
}

void QwtPlotBase::createArrow(QPointF beginPoint, QPointF endPoint)
{
    PaintDrawBase* arrow1 = new PaintDrawArrow(beginPoint,endPoint,Qt::blue);
    drawBases.push_back(arrow1);
}

void QwtPlotBase::paintRectLine(QPointF beginPoint, QPointF endPoint)
{
    if(drawBases.empty())
    {
        return;
    }
    drawBase = getLastDrawBase();
    drawBase->setPoint(beginPoint,endPoint);
    drawBase->setRenderHint(QwtPlotItem::RenderAntialiased);
    drawBase->attach(this);
    this->replot();
}

void QwtPlotBase::createRectLine(QPointF beginPoint, QPointF endPoint)
{
    PaintDrawBase *rectLine1 = new PaintDrawRectLine(beginPoint,endPoint,Qt::blue);
    drawBases.push_back(rectLine1);
}

void QwtPlotBase::paintElipse(QPointF beginPoint, QPointF endPoint)
{
    if(drawBases.empty())
    {
        return;
    }
    drawBase = getLastDrawBase();
    drawBase->setPoint(beginPoint,endPoint);
    drawBase->setRenderHint(QwtPlotItem::RenderAntialiased);
    drawBase->attach(this);
    this->replot();
}

void QwtPlotBase::createElipse(QPointF beginPoint, QPointF endPoint)
{
    PaintDrawBase *elipse1 = new PaintDrawElipse(beginPoint,endPoint,Qt::blue);
    drawBases.push_back(elipse1);
}

void QwtPlotBase::paintBracket(QPointF beginPoint, QPointF endPoint)
{
    if(drawBases.empty())
    {
        return;
    }
    drawBase = getLastDrawBase();
    drawBase->setPoint(beginPoint,endPoint);
    drawBase->setRenderHint(QwtPlotItem::RenderAntialiased);
    drawBase->attach(this);
    this->replot();
}

void QwtPlotBase::createBracket(QPointF beginPoint, QPointF endPoint)
{
    PaintDrawBase *bracket1 = new PaintDrawBracket(beginPoint,endPoint,Qt::blue);
    drawBases.push_back(bracket1);
}

void QwtPlotBase::paintElipseArrow(QPointF beginPoint, QPointF endPoint)
{
    if(drawBases.empty())
    {
        return;
    }
    drawBase = getLastDrawBase();
    drawBase->setPoint(beginPoint,endPoint);
    drawBase->setRenderHint(QwtPlotItem::RenderAntialiased);
    drawBase->attach(this);
    this->replot();
}

void QwtPlotBase::createElipseArrow(QPointF beginPoint, QPointF endPoint)
{
    PaintDrawBase *elipseArrow1 = new PaintDrawElipseArrow(beginPoint,endPoint,Qt::blue);
    drawBases.push_back(elipseArrow1);
}

void QwtPlotBase::paintDoubleArrow(QPointF beginPoint, QPointF endPoint)
{
    if(drawBases.empty())
    {
        return;
    }
    drawBase = getLastDrawBase();
    drawBase->setPoint(beginPoint,endPoint);
    drawBase->setRenderHint(QwtPlotItem::RenderAntialiased);
    drawBase->attach(this);
    this->replot();
}

void QwtPlotBase::createDoubleArrow(QPointF beginPoint, QPointF endPoint)
{
    PaintDrawBase *doubleArrow1 = new PaintDrawDoubleArrow(beginPoint,endPoint,Qt::blue);
    drawBases.push_back(doubleArrow1);
}

void QwtPlotBase::paintPaintDrawDoubleMouse(QPointF beginPoint, QPointF endPoint)
{
    if(drawBases.empty())
    {
        return;
    }
    drawBase = getLastDrawBase();
    drawBase->setPoint(beginPoint,endPoint);
    drawBase->setRenderHint(QwtPlotItem::RenderAntialiased);
    drawBase->attach(this);
    this->replot();
}

void QwtPlotBase::createPaintDrawDoubleMouse(QPointF beginPoint, QPointF endPoint)
{
    PaintDrawBase *doubleMouse1 = new PaintDrawDoubleMouse(beginPoint,endPoint,Qt::blue);
    drawBases.push_back(doubleMouse1);
}

void QwtPlotBase::paintPicture(QPointF beginPoint, QPointF endPoint)
{
    if(drawBases.empty())
    {
        return;
    }
    QString path = QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("选择图片"),".","Image Files(*.png *.jpg)");
    QPixmap img;
    if(!(img.load(path)))
    {
         QMessageBox::warning(this, QString("打开图像失败"), QString("打开图像失败!"));
         return;
    }
    drawBase = getLastDrawBase();
    drawBase->setPoint(beginPoint,endPoint);
    drawBase->setPicture(img);
    drawBase->setRenderHint(QwtPlotItem::RenderAntialiased);
    drawBase->attach(this);
    this->replot();
}

void QwtPlotBase::createPicture(QPointF beginPoint, QPointF endPoint)
{
    PaintDrawBase *picture1 = new PaintDrawPicture(beginPoint,endPoint,Qt::blue);
    drawBases.push_back(picture1);
}

void QwtPlotBase::paintAmplitudeLine(QPointF beginPoint, QPointF endPoint)
{
    if(drawBases.empty())
    {
        return;
    }
    double num = 99999;
    double num2 = 99999;
    QPointF bPoint;
    QPointF ePoint;
    for(int i=0;i<maxPoint.size();i++)
    {
        double num1 = sqrt((maxPoint[i].x-beginPoint.x())*(maxPoint[i].x-beginPoint.x())+
                           (maxPoint[i].y-beginPoint.y())*(maxPoint[i].y-beginPoint.y()));
        if( num1 < num)
        {
            num = num1;
            bPoint.setX(maxPoint[i].x);
            bPoint.setY(maxPoint[i].y);
        }

        num1 = sqrt((maxPoint[i].x-endPoint.x())*(maxPoint[i].x-endPoint.x())+
                           (maxPoint[i].y-endPoint.y())*(maxPoint[i].y-endPoint.y()));
        if( num1 < num2)
        {
            num2 = num1;
            ePoint.setX(maxPoint[i].x);
            ePoint.setY(maxPoint[i].y);
        }
    }
    double dis = sqrt((bPoint.x()-ePoint.x())*(bPoint.x()-ePoint.x())+
                      (bPoint.y()-ePoint.y())*(bPoint.y()-ePoint.y()));
    QString sss(QString::number(dis));
    drawBase = getLastDrawBase();
    drawBase->setInputText(sss);
    drawBase->setPoint(bPoint,ePoint);
    drawBase->setRenderHint(QwtPlotItem::RenderAntialiased);
    drawBase->attach(this);
    this->replot();
}

void QwtPlotBase::createAmplitudeLine(QPointF beginPoint, QPointF endPoint)
{
    PaintDrawBase *amplitudeLine1 = new PaintDrawAmplitudeLine(beginPoint,endPoint,Qt::blue);
    drawBases.push_back(amplitudeLine1);
}

void QwtPlotBase::paintKeyPoint(QPointF beginPoint, QPointF endPoint)
{
    if(drawBases.empty())
    {
        return;
    }
    endPoint.setX(beginPoint.x());
    endPoint.setY(yMax);
    drawBase = getLastDrawBase();
    drawBase->setPoint(beginPoint,endPoint);
    drawBase->setXPoint(QPointF(xMin,beginPoint.y()),drawLineFlag);
    drawBase->setRenderHint(QwtPlotItem::RenderAntialiased);
    drawBase->attach(this);
    this->replot();
}

void QwtPlotBase::createKeyPoint(QPointF beginPoint, QPointF endPoint)
{
    PaintDrawBase *keyPoint1 = new PaintDrawKeyPoint(beginPoint,endPoint,Qt::blue);
    drawBases.push_back(keyPoint1);
}
void QwtPlotBase::setGridState(bool v)
{
    if(v)
    {
        grid->show();
    }
    else
    {
        grid->hide();
    }
    this->replot();
}

void QwtPlotBase::setBackGroupLightDark(int index)
{
    if(index == 0)
    {
        backgroundCurve->setPalette(Qt::white);
        grid->setMajorPen( Qt::black, 0, Qt::DotLine );
    }
    else if(index == 1)
    {
        backgroundCurve->setPalette(Qt::black);
        grid->setMajorPen( Qt::white, 0, Qt::DotLine );
    }
    this->replot();
}

PaintDrawBase *QwtPlotBase::getLastDrawBase()
{
    if(drawBases.size() > 0)
    {
        return drawBases[drawBases.size() - 1];
    }
    return NULL;
}
void QwtPlotBase::setInputText(QString str)
{
    drawBase->setInputText(str);
}

