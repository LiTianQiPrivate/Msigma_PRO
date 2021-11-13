#include "MsigmaBase.h"

MsigmaBase::MsigmaBase(QString name)
{
    className = name;
}

MsigmaBase::~MsigmaBase()
{

}


QString MsigmaBase::getClassName() const
{
    return className;
}

void MsigmaBase::setClassName(const QString &value)
{
    className = value;
}

ModelBase *MsigmaBase::getModelBase(int index)
{
    if(index >= modelBases.size())
    {
        return NULL;
    }
    return modelBases[index];
}
