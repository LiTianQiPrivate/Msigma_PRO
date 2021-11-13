#ifndef POINTOBJECT_H
#define POINTOBJECT_H
#include "vtkActor.h"
#include "vtkSmartPointer.h"
#include "vtkModelBase.h"
#include "vtkSphereSource.h"
#include "Point3D.h"
#include "MyActor.h"

/**
 * @brief The PointObject class 点的数据模型
 */
class PointObject : public vtkModelBase
{
public:
    PointObject(QString className = "PointObject");
    vtkActor* getActor(QString viewerName); // 获取actor
    void setVisibility(bool value); // 设置可见性
    bool isVisibility(); // 判断可见性
    void setColor(int r, int g, int b); // 设置颜色
    void setOpacity(double value); // 设置透明度
    void setPoint(Point3D p); // 设置位置
    Point3D getPoint(); // 获取位置
    void setSize(double size); // 设置点大小
    bool findActor(vtkActor *value); // 是否存在value
private:
    vtkSmartPointer<vtkSphereSource> sphere;
    MyActor actor;
};

#endif // POINTOBJECT_H
