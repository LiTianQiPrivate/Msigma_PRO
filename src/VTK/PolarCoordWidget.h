#ifndef POLARCOORDWIDGET_H
#define POLARCOORDWIDGET_H
#include <QVTKOpenGLStereoWidget.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>
#include <vtkRenderWindow.h>
#include <vtkPolyDataMapper.h>
#include <vtkBox.h>
#include <vtkExtractPoints.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include "ModelRCSF.h"
//
#include "ViewInteratorStyleTrackballCamera.h"
#include "ViewBase.h"
#include "PolyDataObject.h"
#include "vtkScalarBarWidget.h"
#include "vtkLookupTable.h"
#include "RoundRuleObject.h"
#include "MsigmaBase.h"

/**
 * @brief The PolarCoordWidget class
 * 二维极坐标色彩图
 */
class PolarCoordWidget : public QVTKOpenGLStereoWidget, public ViewBase, public MsigmaBase
{
public:
    PolarCoordWidget(QWidget *parent = nullptr, QString className = "PolarCoordWidget");
    void OnRightButtonDown(); // 鼠标右键按下事件
    void OnRightButtonUp(); // 鼠标右键抬起事件
    void OnLeftButtonDown(); // 鼠标左键按下
    void OnMouseMove(); // 鼠标移动
    void OnLeftButtonUp(); // 鼠标左键抬起
    void resetCamera();
    void initScalarBarWidget(vtkLookupTable* lookupTable);
public:
    void setModelBases(std::vector<ModelBase *> modelObjects, int index);
    void addModelBase(ModelBase* modelObject);
    void clearModelBase();
    void updataView();
protected:
    vtkSmartPointer<vtkRenderer> renderer; // 渲染器
    vtkSmartPointer<vtkCamera> camera; // 相机
    vtkSmartPointer<ViewInteratorStyleTrackballCamera> viewInteratorStyle; // 轨迹球交互
private:
    PolyDataObject rcsfPolyData; // 隐形数据
    RoundRuleObject roundRuleObject; //刻度尺
    vtkSmartPointer<vtkLookupTable> pColorTable; // 颜色条映射
    vtkSmartPointer<vtkScalarBarWidget> scalarWidget; // 颜色条窗口

};

#endif // POLARCOORDWIDGET_H
