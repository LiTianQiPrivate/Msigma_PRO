#ifndef VTKMODELBASE_H
#define VTKMODELBASE_H
#include <QString>
#include <vtkMatrix4x4.h>
#include "Point3D.h"
/**
 * @brief The ModelBase class 模型基类保存基本信息
 */
class vtkModelBase
{
public:
    vtkModelBase(QString name);
    virtual void setVisibility(bool value){}
    virtual bool isVisibility(){return 0;}
    virtual void setColor(int r, int g, int b){}
    virtual void setOpacity(double value){}
    QString getName() const;
    void setName(const QString &value);

    QString getObjectName() const;
    void setObjectName(QString value);
    virtual void move(Normal n){}
    virtual void rotate(double angle, Normal axis, Point3D center){}// 旋转模型

protected:
    QString name;
    QString objectName;
};

#endif // VTKMODELBASE_H
