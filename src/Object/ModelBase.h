 #ifndef MODELBASE_H
#define MODELBASE_H

#include <QString>
#include <vector>
#include "KeyText.h"
#include "Point3D.h"
#include "QColor"
class ModelBase
{
public:
    struct TASK_DATA
    {
        TASK_DATA(QString k = "", QString v = "")
        {
            key = k;
            value = v;
        }
        QString key = "";
        QString value = "";
    };
    ModelBase(QString className = "");
    QString getClassName();
    QString FileName();
    void setFileName(QString str)
    {
        fileName = str;
    }
    std::vector<TASK_DATA>& getTaskDatas();
    std::vector<TASK_DATA>& getSystemDatas();
    virtual std::vector<TASK_DATA>& getConditionsDatas() = 0;
    virtual QString findDataInfo(QString key) = 0;
    virtual bool findDataInfoFlag(QString key) = 0;
    virtual std::vector<Point2D> getPoint2D(){return std::vector<Point2D>();}
//    virtual std::vector<Point3D> getPoint3D(){return std::vector<Point3D>();}
    std::vector<std::vector<Point3D>>& getPointDatas(){return pointDatas;}
    QColor getColor();
    virtual void setShowHideFlag(bool v)
    {
        showHide = v;
    }
    virtual bool getShowHideFlag()
    {
        return showHide;
    }
public:
    bool showHide = true;  // 默认显示
    QString fileName = "";
    QString oriFileName = "";
    std::vector<TASK_DATA> taskDatas;
    std::vector<TASK_DATA> systemDatas;
    std::vector<std::vector<Point3D>> pointDatas; // 数据
    QString className;
protected:
    QColor color;


};

#endif // MODELBASE_H
