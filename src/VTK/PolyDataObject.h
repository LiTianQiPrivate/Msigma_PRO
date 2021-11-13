#ifndef POLYDATAOBJECT_H
#define POLYDATAOBJECT_H
#include "vtkPolyData.h"
#include "vtkActor.h"
#include "vtkSmartPointer.h"
#include "vtkModelBase.h"
#include "vtkOBBTree.h"
#include "Point3D.h"
#include "MyActor.h"

class PolyDataObject : public vtkModelBase
{
public:
    PolyDataObject(QString className = "PolyDataObject");
    void loadPolyData(QString filePath); // 加载STL数据
    void savePolyData(QString filePath); // 保存数据为STL
    void loadPolyData_VTK(QString filePath); // 加载VTK数据
    void savePolyData_VTK(QString filePath); // 保存数据为VTK

    vtkPolyData* getPolyData(); // 获取模型数据结构
    vtkActor* getActor(QString viewerName); // 获取模型Actor
    void setVisibility(bool value); // 设置可见性
    bool isVisibility(); // 判断可见性
    void setColor(int r, int g, int b); // 设置颜色0~255
    void setOpacity(double value); // 设置透明度0~1
    void rotate(double angle, Normal axis, Point3D center); // 旋转模型
    void move(Normal n); // 移动模型
    void calNormal(int type); // 0计算点法相  1计算单元法相
    bool findActor(vtkActor* value); // 判断value是否存在
    void zoomToValue(double value, Point3D c); // 缩放到多大
protected:

    vtkSmartPointer<vtkPolyData> polyData; // 模型数据
    MyActor actor; // 模型显示Actor
    int color[3]; // 模型颜色
    vtkSmartPointer<vtkOBBTree> tree; // 模型obbtree,能够提高快速查找速度，模型数据发生变化，使用前需要更新此参数
};

#endif // POLYDATAOBJECT_H
