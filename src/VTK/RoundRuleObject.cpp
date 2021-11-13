#include "RoundRuleObject.h"

RoundRuleObject::RoundRuleObject()
{

}

void RoundRuleObject::initData(double r, double startAngle)
{
    int count = 360;
    std::vector<Point3D> roundPoint;
    for(int i = 0; i < count; i++)
    {
        Point3D point;
        point.x = r * sin(2*3.1415926/count*i);
        point.y = r * cos(2*3.1415926/count*i);
        point.z = 0;
        points[i].setSize(0.5);
        points[i].setPoint(point);
        roundPoint.push_back(point);
    }
    lineObject.setPoints(roundPoint);

    count = 36;
    for(int i = 0; i < count; i++)
    {
        Point3D point;
        point.x = (r+6) * sin(2*3.1415926/count*i);
        point.y = (r+6) * cos(2*3.1415926/count*i);
        point.z = 0;
        text[i].setSize(0.09);
        text[i].setTextPos(point);
        text[i].setText(QString::number(startAngle));
        startAngle = startAngle + 10;
    }

}

