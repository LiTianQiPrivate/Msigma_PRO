#include "ModelBase.h"
#include "VTKGeometry.h"

ModelBase::ModelBase(QString className)
{
    this->className = className;
    taskDatas.push_back(TASK_DATA(QString::fromLocal8Bit(TARGET_NAME)));
    taskDatas.push_back(TASK_DATA(QString::fromLocal8Bit(TARGET_EXPLAIN)));
    taskDatas.push_back(TASK_DATA(QString::fromLocal8Bit(EXPERIMENT_NAME)));
    taskDatas.push_back(TASK_DATA(QString::fromLocal8Bit(EXPERIMENT_PERSON)));
    taskDatas.push_back(TASK_DATA(QString::fromLocal8Bit(EXPERIMENT_UNIT)));
    taskDatas.push_back(TASK_DATA(QString::fromLocal8Bit(TASK_CODE)));
    taskDatas.push_back(TASK_DATA(QString::fromLocal8Bit(TASK_SOURCE)));
    taskDatas.push_back(TASK_DATA(QString::fromLocal8Bit(DATA_SOURCE)));
    taskDatas.push_back(TASK_DATA(QString::fromLocal8Bit(DATA_TYPE)));
    taskDatas.push_back(TASK_DATA(QString::fromLocal8Bit(MEASUREMENT_SITE)));
    taskDatas.push_back(TASK_DATA(QString::fromLocal8Bit(MEASUREMENT_DATE)));
    taskDatas.push_back(TASK_DATA(QString::fromLocal8Bit(SCALE)));
    taskDatas.push_back(TASK_DATA(QString::fromLocal8Bit(CALIBRATION_FORM)));
    taskDatas.push_back(TASK_DATA(QString::fromLocal8Bit(CALIBRATION_NAME)));
    taskDatas.push_back(TASK_DATA(QString::fromLocal8Bit(CALIBRATION_SIZE)));
    taskDatas.push_back(TASK_DATA(QString::fromLocal8Bit(INDETERMINACY)));
    taskDatas.push_back(TASK_DATA(QString::fromLocal8Bit(RANGE)));
    taskDatas.push_back(TASK_DATA(QString::fromLocal8Bit(QUALITY_GRADE)));
    taskDatas.push_back(TASK_DATA(QString::fromLocal8Bit(USER_EVALUATION)));
    taskDatas.push_back(TASK_DATA(QString::fromLocal8Bit(REMARK)));

    systemDatas.push_back(TASK_DATA(QString::fromLocal8Bit(DEVE_NAME)));
    systemDatas.push_back(TASK_DATA(QString::fromLocal8Bit(WORK_SYSTEM)));
    systemDatas.push_back(TASK_DATA(QString::fromLocal8Bit(DYNAMIC_RANGE)));
    systemDatas.push_back(TASK_DATA(QString::fromLocal8Bit(MEAN_POWER)));
    systemDatas.push_back(TASK_DATA(QString::fromLocal8Bit(POWER_STABILITY)));
    systemDatas.push_back(TASK_DATA(QString::fromLocal8Bit(SENSITIVITY)));
    systemDatas.push_back(TASK_DATA(QString::fromLocal8Bit(NOISE_FACTOR)));
    systemDatas.push_back(TASK_DATA(QString::fromLocal8Bit(LINEARITY)));
    systemDatas.push_back(TASK_DATA(QString::fromLocal8Bit(FRE_STABILITY)));
    systemDatas.push_back(TASK_DATA(QString::fromLocal8Bit(REMARK)));

    color = VTKGeometry::getRandomColor();
}

QString ModelBase::getClassName()
{
    return className;
}

std::vector<ModelBase::TASK_DATA> &ModelBase::getTaskDatas()
{
    return taskDatas;
}

std::vector<ModelBase::TASK_DATA> &ModelBase::getSystemDatas()
{
    return systemDatas;
}

QColor ModelBase::getColor()
{
    return color;
}

QString ModelBase::FileName()
{
    return fileName;
}
