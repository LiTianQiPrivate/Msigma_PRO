#ifndef TEXTOBJECT_H
#define TEXTOBJECT_H
#include "vtkModelBase.h"
#include "vtkActor.h"
#include "vtkSmartPointer.h"
#include "Point3D.h"
#include "vtkPolyData.h"
#include "vtkTextProperty.h"
#include "vtkTextActor3D.h"

class TextObject : public vtkModelBase
{
public:
    TextObject(QString className = "TextObject");
    vtkProp* getActor();
    void setVisibility(bool value);
    bool isVisibility();
    void setColor(int r, int g, int b);
    void setOpacity(double value);
    void setTextPos(Point3D p);
    void setText(QString text);
    void moveData(Point3D s, Point3D e); // 轮廓线移动
    void rotateData(Point3D s, Point3D e); // 旋转
    void zoomData(Point3D s, Point3D e);  // 缩放
    void setSize(double size);
private:
    vtkSmartPointer<vtkTextActor3D> actor1;
    double zoom = 0.001;
};

#endif // TEXTOBJECT_H
