#include "TextObject.h"
#include "Geometry/VTKGeometry.h"

TextObject::TextObject(QString className) : vtkModelBase(className)
{
    actor1 = vtkSmartPointer<vtkTextActor3D>::New();
    actor1->GetTextProperty()->SetFontSize(100);
    actor1->GetTextProperty()->SetColor(1.0, 0.0, 0.0);
//    actor1->GetTextProperty()->SetJustificationToRight();
//    actor1->GetTextProperty()->SetVerticalJustificationToTop();
    actor1->GetTextProperty()->SetFontFamilyToTimes();
    actor1->GetTextProperty()->SetFontFamily(VTK_FONT_FILE);
    actor1->GetTextProperty()->SetFontFile("./simkai.ttf");
    actor1->GetTextProperty()->SetVerticalJustificationToCentered();
    actor1->GetTextProperty()->SetJustificationToCentered();
    actor1->SetPosition(0, 0, 0);
//    actor1->RotateX(180);
    actor1->SetScale(zoom);

}

vtkProp *TextObject::getActor()
{
    return actor1;
}

void TextObject::setVisibility(bool value)
{
    actor1->SetVisibility(value);
}

bool TextObject::isVisibility()
{
    return actor1->GetVisibility();
}

void TextObject::setColor(int r, int g, int b)
{
    actor1->GetTextProperty()->SetColor(((double)r)/255, ((double)g)/255, ((double)b)/255);
    actor1->Modified();

}

void TextObject::setOpacity(double value)
{
    actor1->GetTextProperty()->SetOpacity(value);
}

void TextObject::setTextPos(Point3D p)
{
    actor1->SetPosition(p.x, p.y, p.z);
}

void TextObject::setText(QString text)
{
    actor1->SetInput(text.toUtf8());
}

void TextObject::moveData(Point3D s, Point3D e)
{
    actor1->SetPosition(e.x, e.y, e.z);
}

void TextObject::rotateData(Point3D s, Point3D e)
{
    double* p = actor1->GetPosition();
    Point3D center(p[0], p[1], p[2]);
    Normal n1 = s - center;
    Normal n2 = e - center;

    double angle = VTKGeometry::getAngleDegOf2Vec(n1, n2);

    Vector3 n = crossProduct(n1.toVector3(), n2.toVector3());
    if(n.z < 0)
    {
        actor1->RotateZ(angle);
    } else {
        actor1->RotateZ(-angle);
    }

}

void TextObject::zoomData(Point3D s, Point3D e)
{
    double* p = actor1->GetPosition();
    Point3D center(p[0], p[1], p[2]);
    double d1 = point3Distance(s, center);
    double d2 = point3Distance(e, center);
    if(d2 > d1)
    {
        zoom = zoom + 0.0001;
    } else {
        zoom = zoom - 0.0001;
        if(zoom <= 0)
        {
            zoom = 0;
        }
    }
    actor1->SetScale(zoom);
}

void TextObject::setSize(double size)
{
    zoom = size;
    actor1->SetScale(zoom);
    actor1->Modified();
//    actor1->GetTextProperty()->SetFontSize(size);
}
