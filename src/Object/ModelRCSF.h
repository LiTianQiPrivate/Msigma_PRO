#ifndef MODELRCSF_H
#define MODELRCSF_H

#include "ModelBase.h"
#include "Point3D.h"
class ModelRCSF : public ModelBase
{
public:
    struct CURVE_DATA
    {
        CURVE_DATA(double v1, double v2, double v3, double v4)
        {
            angle = v1;
            fo = v2;
            rcs = v3;
            phi = v4;
        }
        double angle;
        double fo;
        double rcs;
        double phi;
    };
    ModelRCSF(QString className = "ModelRCSF");
    void loadFile(QString filePath);
    QString findDataInfo(QString key);
    bool findDataInfoFlag(QString key);
    std::vector<TASK_DATA>& getConditionsDatas()
    {
        return conditionsDatas;
    }
    void setXStype(int type);
    void setCurrentValue(double value);
    std::vector<Point2D> getPoint2D();
//    std::vector<Point3D> getPoint3D();

    int getXcount();
    void getRCSRange(double& min, double &max);
public:
    std::vector<TASK_DATA> conditionsDatas;
//    std::vector<CURVE_DATA> datas;
    double rcsMin = 0;
    double rcsMax = 0;
    int xStype = -1; // X轴类型 0 频率  1 角度
    double currentValue; // 当前锁定的角度或频率值
};

#endif // MODELRCSF_H
