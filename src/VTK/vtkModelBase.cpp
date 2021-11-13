#include "vtkModelBase.h"
vtkModelBase::vtkModelBase(QString name)
{
    this->name = name;
}

QString vtkModelBase::getName() const
{
    return name;
}

void vtkModelBase::setName(const QString &value)
{
    name = value;
}

QString vtkModelBase::getObjectName() const
{
    return objectName;
}

void vtkModelBase::setObjectName(QString value)
{
    objectName = value;
}

