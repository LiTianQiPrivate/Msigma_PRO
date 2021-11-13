#include "LineObject.h"
#include "vtkPolyDataMapper.h"
#include "vtkProperty.h"
#include "VTKGeometry.h"
#include "vtkPoints.h"

LineObject::LineObject(QString className) : vtkModelBase(className)
{
    polyLine = VSP<vtkLineSource>::New();
    VSP<vtkPoints> linePoints = VSP<vtkPoints>::New();
    linePoints->InsertPoint(0, 0, 0, 0);;
    linePoints->InsertPoint(1, 0, 0, 0);;
    polyLine->SetPoints(linePoints);
//    auto mapper = VSP<vtkPolyDataMapper>::New();
//    mapper->ScalarVisibilityOff();
//    mapper->SetInputConnection(polyLine->GetOutputPort());
    lineActor.setAlgorithmOutput(polyLine->GetOutputPort());
//    lineActor.setMapper(mapper);
    setColor(255, 0, 0);
    lineActor.setLineWidth(1);
}

vtkActor *LineObject::getActor(QString viewerName)
{
    return lineActor.getActor(viewerName);
}

void LineObject::setVisibility(bool value)
{
    lineActor.setVisibility(value);
}
bool LineObject::isVisibility()
{
    return lineActor.getVisibility();
}

void LineObject::setColor(int r, int g, int b)
{
    color[0] = r;
    color[1] = g;
    color[2] = b;
    lineActor.setColor(r, g, b);
}

void LineObject::setOpacity(double value)
{
    lineActor.setOpacity(value);
}

void LineObject::clearPoints()
{
    VSP<vtkPoints> linePoints = VSP<vtkPoints>::New();
    polyLine->SetPoints(linePoints);
}

void LineObject::addPoint(Point3D p)
{
    polyLine->GetPoints()->InsertNextPoint(p.x, p.y, p.z);
    if(getPointCount() > 1)
        polyLine->Update();
}

void LineObject::setPoints(std::vector<Point3D> points)
{
    VSP<vtkPoints> linePoints = VSP<vtkPoints>::New();
    for(int i = 0; i < points.size(); i++)
    {
        Point3D p = points[i];
        linePoints->InsertPoint(i, p.x, p.y, p.z);
    }
    polyLine->SetPoints(linePoints);
    polyLine->Update();
}

std::vector<Point3D> LineObject::getPoints()
{
    std::vector<Point3D> points;
    for(int i = 0; i < getPointCount(); i++)
    {
        points.push_back(getPoint(i));
    }
    return points;
}

int LineObject::getPointCount()
{
    return polyLine->GetPoints()->GetNumberOfPoints();
}

Point3D LineObject::getPoint(int index)
{
    double* p = polyLine->GetPoints()->GetPoint(index);
    return Point3D(p[0], p[1], p[2]);
}

void LineObject::setPoint(int index, Point3D p)
{
    double* pp = polyLine->GetPoints()->GetPoint(index);
    pp[0] = p.x;
    pp[1] = p.y;
    pp[2] = p.z;
}

bool LineObject::findActor(vtkActor *value)
{
    return lineActor.findActor(value);
}

void LineObject::setLineWidth(int width)
{
    lineActor.setLineWidth(width);
}

void LineObject::setIsPick(bool isPick)
{
    if(isPick)
    {
        lineActor.setColor(color[0] + 20, color[1] + 20, color[2] + 20);
    } else {
        lineActor.setColor(color[0], color[1], color[2]);
    }
}
