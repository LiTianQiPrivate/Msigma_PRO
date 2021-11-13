#include "MyZoomer.h"
#include <QMessageBox>
MyZoomer::MyZoomer(QWidget *canvas ):
    QwtPlotZoomer( canvas )
{
    setTrackerMode( QwtPlotZoomer::AlwaysOn );
}

void MyZoomer::setMsigmaBase(MsigmaBase *value)
{
    msigmaBase = value;
}

void MyZoomer::widgetMousePressEvent( QMouseEvent * event)
{
    QwtPlotZoomer::widgetMousePressEvent(event);

    if (event->button() == Qt::LeftButton) {
        beginPoint = (event->pos());
        changeBeginPoint = QwtPlotZoomer::invTransform(event->pos());
        switch(m_drawShapeType)
        {
        case EnumDrawArrow:
            if(msigmaBase)
            {
                msigmaBase->createArrow(changeBeginPoint, changeBeginPoint);
            }
             break;
        case EnumDrawEllipse:
            if(msigmaBase)
            {
                msigmaBase->createElipse(changeBeginPoint, changeBeginPoint);
            }
             break;
        case EnumDrawBrackets:
            if(msigmaBase)
            {
                msigmaBase->createBracket(changeBeginPoint, changeBeginPoint);
            }
             break;
        case EnumDrawRectLine:
            if(msigmaBase)
            {
                msigmaBase->createRectLine(changeBeginPoint, changeBeginPoint);
            }
             break;
        case EnumDrawElipseArrow:
            if(msigmaBase)
            {
                msigmaBase->createElipseArrow(changeBeginPoint, changeBeginPoint);
            }
            break;
        case EnumDrawDoubleArrow:
            if(msigmaBase)
            {
                msigmaBase->createDoubleArrow(changeBeginPoint, changeBeginPoint);
            }
            break;
        case EnumDrawAmplitudeLine:
            if(msigmaBase)
            {
                msigmaBase->createAmplitudeLine(changeBeginPoint, changeBeginPoint);
            }
            break;
        case EnmuDrawKeyPoint:
            if(msigmaBase)
            {
                msigmaBase->createKeyPoint(changeBeginPoint, changeBeginPoint);
//                DialogText *text = new DialogText;
//                text->exec();
//                QString str = text->getEditText();
//                msigmaBase->paintKeyPoint(changeBeginPoint, changeBeginPoint);
//                msigmaBase->setInputText(str);
                msigmaBase->paintKeyPoint(changeBeginPoint, changeBeginPoint);
            }
            break;
        case EnumDrawNone:
            break;
        case EnumDrawText:
            if(msigmaBase)
            {
                msigmaBase->createPaintDrawDoubleMouse(changeBeginPoint, changeBeginPoint);
                DialogText *text = new DialogText;
                text->exec();
                QString str = text->getEditText();
                msigmaBase->paintPaintDrawDoubleMouse(changeBeginPoint, changeBeginPoint);
                msigmaBase->setInputText(str);
                msigmaBase->paintPaintDrawDoubleMouse(changeBeginPoint, changeBeginPoint);
            }
            break;
        case EnumDrawPicture:
            if(msigmaBase)
            {
                msigmaBase->createPicture(changeBeginPoint, changeBeginPoint);
            }
            break;
        default:
            break;
        }
    }
}
void MyZoomer::widgetMouseReleaseEvent(QMouseEvent * event)
{
    QwtPlotZoomer::widgetMouseReleaseEvent(event);
    if(event->button() == Qt::LeftButton)
    {
        endPoint = (event->pos());
        changeEndPoint = QwtPlotZoomer::invTransform((event->pos()));
        switch(m_drawShapeType)
        {
        case EnumDrawArrow:
            if(msigmaBase)
            {
                DialogText *text = new DialogText;
                text->exec();
                QString str = text->getEditText();
                msigmaBase->setInputText(str);
                msigmaBase->paintArrow(changeBeginPoint,changeEndPoint);
            }
             break;
        case EnumDrawEllipse:
            if(msigmaBase)
            {
                DialogText *text = new DialogText;
                text->exec();
                QString str = text->getEditText();
                msigmaBase->setInputText(str);
                msigmaBase->paintElipse(changeBeginPoint,changeEndPoint);
            }
             break;
        case EnumDrawBrackets:
            if(msigmaBase)
            {
                DialogText *text = new DialogText;
                text->exec();
                QString str = text->getEditText();
                msigmaBase->setInputText(str);
                msigmaBase->paintBracket(changeBeginPoint,changeEndPoint);
            }
             break;
        case EnumDrawRectLine:
            if(msigmaBase)
            {
                DialogText *text = new DialogText;
                text->exec();
                QString str = text->getEditText();
                msigmaBase->setInputText(str);
                msigmaBase->paintRectLine(changeBeginPoint,changeEndPoint);
            }
             break;
        case EnumDrawElipseArrow:
            if(msigmaBase)
            {
                DialogText *text = new DialogText;
                text->exec();
                QString str = text->getEditText();
                msigmaBase->setInputText(str);
                msigmaBase->paintElipseArrow(changeBeginPoint,changeEndPoint);
            }
            break;
        case EnumDrawDoubleArrow:
            if(msigmaBase)
            {
                DialogText *text = new DialogText;
                text->exec();
                QString str = text->getEditText();
                msigmaBase->setInputText(str);
                msigmaBase->paintDoubleArrow(changeBeginPoint, changeEndPoint);
            }
            break;
        case EnumDrawAmplitudeLine:
            if(msigmaBase)
            {
//                DialogText *text = new DialogText;
//                text->exec();
//                QString str = text->getEditText();
//                msigmaBase->setInputText(str);
                msigmaBase->paintAmplitudeLine(changeBeginPoint, changeEndPoint);
            }
            break;
        case EnumDrawPicture:
            if(msigmaBase)
            {
                msigmaBase->paintPicture(changeBeginPoint, changeEndPoint);
            }
            break;
        case EnumDrawNone:
             break;
        default:
            break;
//        case EnmuDrawKeyPoint:
//            if(msigmaBase)
//            {
//                DialogText *text = new DialogText;
//                text->exec();
//                QString str = text->getEditText();
//                msigmaBase->setInputText(str);
//                msigmaBase->paintKeyPoint(changeBeginPoint, changeBeginPoint);
//            }
//            break;

//        case EnumDrawText:
//            if(msigmaBase)
//            {
//                DialogText *text = new DialogText;
//                text->exec();
//                QString str = text->getEditText();
//                msigmaBase->setInputText(str);
//                msigmaBase->paintPaintDrawDoubleMouse(changeBeginPoint, changeBeginPoint);
//            }
//            break;
        }
    }
}
void MyZoomer::widgetMouseMoveEvent(QMouseEvent* event)
{
    QwtPlotZoomer::widgetMouseMoveEvent(event);
    if (event->buttons() & Qt::LeftButton)
    {
        endPoint = (event->pos());
        changeEndPoint = QwtPlotZoomer::invTransform((event->pos()));
        switch(m_drawShapeType)
        {
        case EnumDrawArrow:
            if(msigmaBase)
            {
                msigmaBase->paintArrow(changeBeginPoint,changeEndPoint);
            }
             break;
        case EnumDrawEllipse:
            if(msigmaBase)
            {
                msigmaBase->paintElipse(changeBeginPoint,changeEndPoint);
            }
             break;
        case EnumDrawBrackets:
            if(msigmaBase)
            {
                msigmaBase->paintBracket(changeBeginPoint,changeEndPoint);
            }
             break;
        case EnumDrawRectLine:
            if(msigmaBase)
            {
                msigmaBase->paintRectLine(changeBeginPoint,changeEndPoint);
            }
             break;
        case EnumDrawElipseArrow:
            if(msigmaBase)
            {
                msigmaBase->paintElipseArrow(changeBeginPoint,changeEndPoint);
            }
            break;
        case EnumDrawDoubleArrow:
            if(msigmaBase)
            {
                msigmaBase->paintDoubleArrow(changeBeginPoint, changeEndPoint);
            }
            break;
        case EnumDrawAmplitudeLine:
            if(msigmaBase)
            {
                msigmaBase->paintAmplitudeLine(changeBeginPoint, changeEndPoint);
            }
            break;
//        case EnumDrawPicture:
//            if(msigmaBase)
//            {
//                msigmaBase->paintPicture(changeBeginPoint, changeEndPoint);
//            }
//            break;
        case EnumDrawNone:
             break;
        default:
            break;
//        case EnmuDrawKeyPoint:
//            if(msigmaBase)
//            {
//                msigmaBase->paintKeyPoint(changeBeginPoint, changeBeginPoint);
//            }
//            break;

//        case EnumDrawText:
//            if(msigmaBase)
//            {
//                msigmaBase->paintPaintDrawDoubleMouse(changeBeginPoint, changeBeginPoint);
//            }
//            break;

        }
    }
}
void MyZoomer::widgetMouseDoubleClickEvent( QMouseEvent * event)
{
    QwtPlotZoomer::widgetMouseDoubleClickEvent(event);
}
QPointF MyZoomer::getBeginPoint()
{
    return beginPoint;
}
QPointF MyZoomer::getEndPoint()
{
    return endPoint;
}
void MyZoomer::setDrawShapeType(int index)
{
    m_drawShapeType = index;
}
QPointF MyZoomer::beginPointChange()
{
    return changeBeginPoint;
}
QPointF MyZoomer::endPointChange()
{
    return changeEndPoint;
}
