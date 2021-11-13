#ifndef MODELRCS_H
#define MODELRCS_H
#include "ModelBase.h"

class ModelRCS : public ModelBase
{
public:
    struct CURVE_DATA
    {
        CURVE_DATA(double v1, double v2, double v3)
        {
            azt = v1;
            rcs = v2;
            phi = v3;
        }
        double azt;
        double rcs;
        double phi;
    };
    ModelRCS(QString className = "ModelRCS");
    void loadFile(QString filePath);
    std::vector<TASK_DATA>& getConditionsDatas()
    {
        return conditionsDatas;
    }
    QString findDataInfo(QString key);
    bool findDataInfoFlag(QString key);
    std::vector<Point2D> getPoint2D();
public:
    std::vector<TASK_DATA> conditionsDatas;
//    std::vector<CURVE_DATA> datas;

};

#endif // MODELRCS_H
