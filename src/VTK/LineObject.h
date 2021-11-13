#ifndef LINEOBJECT_H
#define LINEOBJECT_H

#include "vtkActor.h"
#include "vtkSmartPointer.h"
#include "vtkModelBase.h"
#include "vtkSphereSource.h"
#include "Point3D.h"
#include "Common.h"
#include "vtkLineSource.h"
#include "MyActor.h"
/**
 * @brief The LineObject class 多线段模型
 */
class LineObject : public vtkModelBase
{
public:
    LineObject(QString className = "LineObject");
    vtkActor* getActor(QString viewerName);
    void setVisibility(bool value);
    bool isVisibility();
    void setColor(int r, int g, int b);
    void setOpacity(double value);
    void clearPoints();
    void addPoint(Point3D p);
    void setPoints(std::vector<Point3D> points);
    std::vector<Point3D> getPoints();
    int getPointCount();
    Point3D getPoint(int index);
    void setPoint(int index, Point3D p);
    bool findActor(vtkActor *value);
    void setLineWidth(int width);
    void setIsPick(bool isPick);
private:
    VSP<vtkLineSource> polyLine;
    MyActor lineActor;
    int color[3]; // 模型颜色
};

#endif // LINEOBJECT_H
