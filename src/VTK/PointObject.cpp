#include "PointObject.h"
#include "vtkProperty.h"
#include "vtkPolyDataMapper.h"

PointObject::PointObject(QString className) : vtkModelBase(className)
{
    sphere = vtkSmartPointer<vtkSphereSource>::New();
    sphere->SetCenter(0, 0, 0);
    sphere->SetRadius(0.2);
//    auto mapper1 = vtkSmartPointer<vtkPolyDataMapper>::New();
//    mapper1->ScalarVisibilityOff();
//    mapper1->SetInputConnection(sphere->GetOutputPort());
    actor.setAlgorithmOutput(sphere->GetOutputPort());
//    actor.setMapper(mapper1);
    actor.setColor(0, 0, 255);
}

vtkActor *PointObject::getActor(QString viewerName)
{
    return actor.getActor(viewerName);
}

void PointObject::setVisibility(bool value)
{
    actor.setVisibility(value);
}

bool PointObject::isVisibility()
{
    return actor.getVisibility();
}

void PointObject::setColor(int r, int g, int b)
{
    actor.setColor(r, g, b);

}

void PointObject::setOpacity(double value)
{
    actor.setOpacity(value);
}

void PointObject::setPoint(Point3D p)
{
    sphere->SetCenter(p.x, p.y, p.z);
}

Point3D PointObject::getPoint()
{
    double* p = sphere->GetCenter();
    return Point3D(p[0], p[1], p[2]);
}

void PointObject::setSize(double size)
{
    sphere->SetRadius(size);
}

bool PointObject::findActor(vtkActor *value)
{
    return actor.findActor(value);
}
