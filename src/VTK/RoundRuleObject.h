#ifndef ROUNDRULEOBJECT_H
#define ROUNDRULEOBJECT_H
#include "PointObject.h"
#include "LineObject.h"
#include "TextObject.h"

class RoundRuleObject
{
public:
    RoundRuleObject();
    void initData(double r, double startAngle);
public:

    PointObject points[360];
    LineObject lineObject;
    TextObject text[36];

};

#endif // ROUNDRULEOBJECT_H
