#ifndef VIEWFORM_H
#define VIEWFORM_H

#include <QWidget>
#include <QMouseEvent>
#include "MsigmaBase.h"
#include "paintarea.h"

namespace Ui {
class ViewForm;
}
class ViewForm : public QWidget
{
    Q_OBJECT

public:
    explicit ViewForm(QWidget *parent = nullptr);
    ~ViewForm();
    void resizeEvent(QResizeEvent *event);
    void addModelBase(ModelBase* modelBase);
    virtual void setCurrentQWT(int index);
    std::vector<ModelBase *>getModelBase();
    void updataTableWidgetItem(std::vector<ModelBase *>base);
    std::vector<ModelBase*> modelBases;
    bool ribbonXBackFlag = false;
    double leftBackVertical;
    double rightBackVertical;
    void setXBackRibbon(bool v,double x1,double x2);
    bool ribbonXFlag = false;
    double leftVertical;
    double rightVertical;
    void setXRibbon(bool v,double x1,double x2);
    bool ribbonFlag = false;
    double upDouble;
    double downDouble;
    void setRibbon(bool v,double y1,double y2);
    std::vector<QPointF> dots;
    bool thresholdDotFlag = false;
    bool setThresholdDot(std::vector<QPointF> dot);
    MsigmaBase* getMsigmaBase()
    {
        if(msigmaBase)
        {
            return msigmaBase;
        }
        return NULL;
    }
    void setLegendName(int index);
    void setComboxHide();
private slots:
    void on_deleteaction_triggered();
    void on_tableWidget_customContextMenuRequested(const QPoint &pos);
    void on_tableWidget_cellClicked(int row, int column);
    void on_comboBox_activated(int index);

    virtual void on_curve_triggered();

    virtual void on_dashed_triggered();

    virtual void on_pillar_triggered();

    virtual void on_ladder_triggered();

    void on_hideaction_triggered();

    void on_setaction_triggered();
public:
    Ui::ViewForm *ui;

    MsigmaBase* msigmaBase = nullptr;
    std::vector<ModelBase *> tempBase;// 其中只存储所选中的一条数据 用vector方便当参数使用

    int tableColumn = 3; // 模型列表列数
    int number = 0;    // 默认
public:
    void paintEvent(QPaintEvent *event);
};

#endif // VIEWFORM_H
