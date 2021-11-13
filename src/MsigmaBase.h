#ifndef MSIGMABASE_H
#define MSIGMABASE_H
#include <vector>
#include <QString>
#include <QPointF>
#include "PaintDrawRect.h"
#include "PaintDrawArrow.h"
#include "PaintDrawRectLine.h"
#include "PaintDrawElipse.h"
#include "PaintDrawBracket.h"
#include "PaintDrawBase.h"
#include "PaintDrawElipseArrow.h"
#include "PaintDrawDoubleArrow.h"
#include "PaintDrawAmplitudeLine.h"
#include "PaintDrawKeyPoint.h"
#include "PaintDrawDoubleMouse.h"
#include "PaintDrawPicture.h"
class ModelBase;
class MsigmaBase
{
public:
    MsigmaBase(QString name);
    virtual ~MsigmaBase();
    virtual void setModelBases(std::vector<ModelBase*> modelObjects,int index){}
    virtual void addModelBase(ModelBase* modelObject){}
    virtual void clearModelBase(){}
    virtual void showModelBase(int index){}
    virtual void hideModelBase(int index){}
    virtual bool isVisible(int index){return true;}
    virtual void removeModelBase(int index){}
    virtual void updataView(){}
    virtual int setPenWidth(int width){return width;}  // 设置线宽
    QString getClassName() const;
    void setClassName(const QString &value);
    ModelBase* getModelBase(int index);
    virtual void on_lineStyleComboBoxActivated(int v,int index){}
    virtual void drawRibbonCruve(ModelBase* modelObject,double y1,double y2,bool v){}
    virtual void drawThresholdDotCruve(std::vector<QPointF> dot,bool v){}
    virtual void drawXRiboonCruve(ModelBase* modelObject,double x1,double x2,bool v){}
    virtual void drawXBackRiboonCruve(ModelBase* modelObject,double x1,double x2,bool v){}
    virtual void getStandIndex(int index){}
    virtual std::vector<QPointF> mouseMove(QPointF p){std::vector<QPointF> point;point.push_back(p);return point;}

    virtual void paintArrow(QPointF beginPoint, QPointF endPoint){}
    virtual void createArrow(QPointF beginPoint, QPointF endPoint){}

    virtual void paintRectLine(QPointF beginPoint, QPointF endPoint){}
    virtual void createRectLine(QPointF beginPoint, QPointF endPoint){}

    virtual void paintElipse(QPointF beginPoint, QPointF endPoint){}
    virtual void createElipse(QPointF beginPoint, QPointF endPoint){}

    virtual void paintBracket(QPointF beginPoint, QPointF endPoint){}
    virtual void createBracket(QPointF beginPoint, QPointF endPoint){}

    virtual void paintElipseArrow(QPointF beginPoint, QPointF endPoint){}
    virtual void createElipseArrow(QPointF beginPoint, QPointF endPoint){}

    virtual void paintDoubleArrow(QPointF beginPoint, QPointF endPoint){}
    virtual void createDoubleArrow(QPointF beginPoint, QPointF endPoint){}

    virtual void paintKeyPoint(QPointF beginPoint, QPointF endPoint){}
    virtual void createKeyPoint(QPointF beginPoint, QPointF endPoint){}

    virtual void paintAmplitudeLine(QPointF beginPoint, QPointF endPoint){}
    virtual void createAmplitudeLine(QPointF beginPoint, QPointF endPoint){}

    virtual void paintPaintDrawDoubleMouse(QPointF beginPoint, QPointF endPoint){}
    virtual void createPaintDrawDoubleMouse(QPointF beginPoint, QPointF endPoint){}

    virtual void paintPicture(QPointF beginPoint, QPointF endPoint){}
    virtual void createPicture(QPointF beginPoint, QPointF endPoint){}

    virtual PaintDrawBase *getLastDrawBase(){return new PaintDrawBase;}

    virtual void setAxisX(double xMin,double xMax,double xstep){}
    virtual void setAxisY(double yMin,double yMax,double ystep){}

    virtual void setInputText(QString str){}
    virtual void setGridState(bool v){}
    virtual void setBackGroupLightDark(int index){}
    virtual void setModelBasesFlag(std::vector<ModelBase *> base)
    {
        modelBases =  base;
    }
    std::vector<ModelBase*> modelBases;
protected:
    QString className = "";
/* viewFrom上排按钮虚函数 */
public:
    virtual void on_checkBoxPointClick(bool v){}
    virtual void on_checkMinBoxPointClick(bool v){}
    virtual void on_checkMaxBoxPointClick(bool v){}
    virtual void on_checkTurnBoxPointClick(bool v){}
    virtual void on_checkCurveSelectClick(bool v){}
    virtual void on_checkManyCurveSelectClick(bool v){}
public:    //  数据统计与分析模块虚函数
    virtual void drawStatisicalAnalysis(double x1, double x2, double x3, double x4){}
    virtual void clearDateVluess(){}
    virtual void clearRect(){}
    virtual double getXMinValue(){return 0.0;}
    virtual double getXMaxValue(){return 0.0;}
};

#endif // MSIGMABASE_H
