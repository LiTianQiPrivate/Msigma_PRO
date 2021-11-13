#ifndef MODELRAM_H
#define MODELRAM_H
#include "ModelBase.h"
#include <QString>

class ModelRAM : public ModelBase
{
public:
    struct CURVE_DATA
    {
        CURVE_DATA(double v1, double v2)
        {
            fo = v1;
            refl = v2;
        }
        double fo;
        double refl;
    };
    ModelRAM(QString className = "ModelRAM");
    void loadFile(QString filePath);
    std::vector<TASK_DATA>& getConditionsDatas()
    {
        return conditionsDatas;
    }
    QString findDataInfo(QString key);
    bool findDataInfoFlag(QString key);
    std::vector<Point2D> getPoint2D();
    void setPoint2D(std::vector<Point2D> point);

public:
    std::vector<TASK_DATA> conditionsDatas;
//    std::vector<CURVE_DATA> datas;

};

#endif // MODELRAM_H
