#ifndef VIEWFORMRCS_H
#define VIEWFORMRCS_H

#include <QWidget>
#include "ViewForm.h"
#include "MsigmaBase.h"
#include "ModelBase.h"
#include "set"
namespace Ui {
class ViewFormRCS;
}

class ViewFormRCS : public QWidget
{
    Q_OBJECT

public:
    explicit ViewFormRCS(QWidget *parent = nullptr);
    ~ViewFormRCS();
    void addModelBase(ModelBase* modelBase);
    void resizeEvent(QResizeEvent *event);
private:
    Ui::ViewFormRCS *ui;
    std::vector<ModelBase *> modelBases;
    MsigmaBase  *msigmaBase = nullptr;
public:
    std::vector<QString> nameStr;
    void setLabel2Tetx(ModelBase* modelBase);
public:
    std::vector<QString> pitchStr;
    void setLabel3Tetx(ModelBase* modelBase);
public:
    std::vector<QString> rollStr;
    void setLabel4Tetx(ModelBase* modelBase);
public:
    std::vector<QString> polarStr;
    void setLabel5Tetx(ModelBase* modelBase);
public:
    std::vector<QString> fpsStr;
    void setLabel6Tetx(ModelBase* modelBase);
public:
    std::vector<QString> dataStr;
    void setLabel7Tetx(ModelBase* modelBase);
public:
    std::vector<QString> timeStr;
    void setLabel8Tetx(ModelBase* modelBase);
public:
    void setTableWidgetStatistical(double x1,double x2,double x3,double x4);
    void clearDataValue();
    void clearFillRect();
    double getXMin();
    double getXMax();

};

#endif // VIEWFORMRCS_H
