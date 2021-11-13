#ifndef CURVE3DWIDGET_H
#define CURVE3DWIDGET_H
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
#include "ViewInteratorStyleTrackballCamera.h"
#include "ViewBase.h"
#include "PolyDataObject.h"
#include "vtkScalarBarWidget.h"
#include "vtkLookupTable.h"
#include "MsigmaBase.h"
#include "vtkCubeAxesActor.h"
#include "LineObject.h"

/**
 * @brief The Curve3DWidget class
 * 3D曲线图
 */
class Curve3DWidget : public QVTKOpenGLStereoWidget, public ViewBase, public MsigmaBase
{
public:
    Curve3DWidget(QWidget *parent = nullptr, QString classname = "Curve3DWidget");
    ~Curve3DWidget();
    void OnRightButtonDown(); // 鼠标右键按下事件
    void OnRightButtonUp(); // 鼠标右键抬起事件
    void OnLeftButtonDown(); // 鼠标左键按下
    void OnMouseMove(); // 鼠标移动
    void OnLeftButtonUp(); // 鼠标左键抬起
    void resetCamera();
    void initScalarBarWidget(vtkLookupTable* lookupTable);
    void initCubeAxesActor(double* bound);
public:
    void setModelBases(std::vector<ModelBase *> modelObjects, int index);
    void addModelBase(ModelBase* modelObject);
    void clearModelBase();
    void updataView();

protected:
    vtkSmartPointer<vtkRenderer> renderer; // 渲染器
    vtkSmartPointer<ViewInteratorStyleTrackballCamera> viewInteratorStyle; // 轨迹球交互
    vtkSmartPointer<vtkLookupTable> pColorTable; // 颜色条映射
    vtkSmartPointer<vtkScalarBarWidget> scalarWidget; // 颜色条窗口
    vtkSmartPointer<vtkCubeAxesActor> m_cubeAxesActor; // 刻度尺
    std::vector<LineObject*> lineObjects; // 曲线
};

#endif // CURVE3DWIDGET_H
