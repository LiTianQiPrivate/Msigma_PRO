#include "ModelRCSF.h"
#include <QTextStream>
#include <QFile>
#include <QFileInfo>
#include <sstream>
#include <QDebug>

ModelRCSF::ModelRCSF(QString className) : ModelBase(className)
{
    conditionsDatas.push_back(TASK_DATA(QString::fromLocal8Bit(MEASURING)));
    conditionsDatas.push_back(TASK_DATA(QString::fromLocal8Bit(START_FPS)));
    conditionsDatas.push_back(TASK_DATA(QString::fromLocal8Bit(END_FPS)));
    conditionsDatas.push_back(TASK_DATA(QString::fromLocal8Bit(FPS_STEP)));
    conditionsDatas.push_back(TASK_DATA(QString::fromLocal8Bit(POLARIZATION_COMBINATION)));
    conditionsDatas.push_back(TASK_DATA(QString::fromLocal8Bit(TARGET_DIST)));
    conditionsDatas.push_back(TASK_DATA(QString::fromLocal8Bit(TARGET_HEIGHT)));
    conditionsDatas.push_back(TASK_DATA(QString::fromLocal8Bit(ANTENNA_HEIGHT)));
    conditionsDatas.push_back(TASK_DATA(QString::fromLocal8Bit(TARGET_PITCH_ANGLE)));
    conditionsDatas.push_back(TASK_DATA(QString::fromLocal8Bit(TARGET_ROLL_ANGLE)));
    conditionsDatas.push_back(TASK_DATA(QString::fromLocal8Bit(SZ_ANGLE)));
    conditionsDatas.push_back(TASK_DATA(QString::fromLocal8Bit(START_TARGET_ANGLE)));
    conditionsDatas.push_back(TASK_DATA(QString::fromLocal8Bit(END_TARGET_ANGLE)));
    conditionsDatas.push_back(TASK_DATA(QString::fromLocal8Bit(TARGET_NORMAL_ANGLE)));
    conditionsDatas.push_back(TASK_DATA(QString::fromLocal8Bit(REMARK)));
}

void ModelRCSF::loadFile(QString filePath)
{
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }
    rcsMin = INT_MAX;
    rcsMax = INT_MIN;
    QFileInfo fileInfo = QFileInfo(filePath);
    this->fileName = fileInfo.fileName();
    this->oriFileName = fileInfo.fileName();
    QTextStream in(&file);
    QString line = in.readLine();

    while(!line.isNull())
    {
        line = in.readLine();
        if(line.contains("[TASK]"))
        {
            for(int i = 0; i < taskDatas.size(); i++)
            {
                line = in.readLine();
                if(line.contains("[/TASK]"))
                {
                    break;
                }
                for(int j = 0; j < taskDatas.size(); j++)
                {
                    if(line.contains(taskDatas[j].key))
                    {
                        QString str = line.section('=',1,1);
                        taskDatas[j].value = str;
                        break;
                    }
                }
            }
        }

        if(line.contains("[SYSTEM]"))
        {
            for(int i = 0; i < systemDatas.size(); i++)
            {
                line = in.readLine();
                if(line.contains("[/SYSTEM]"))
                {
                    break;
                }
                for(int j = 0; j < systemDatas.size(); j++)
                {
                    if(line.contains(systemDatas[j].key))
                    {
                        QString str = line.section('=',1,1);
                        systemDatas[j].value = str;
                        break;
                    }
                }
            }
        }

        if(line.contains("[CONDITIONS]"))
        {
            for(int i = 0; i < conditionsDatas.size(); i++)
            {
                line = in.readLine();
                if(line.contains("[/CONDITIONS]"))
                {
                    break;
                }
                for(int j = 0; j < conditionsDatas.size(); j++)
                {
                    if(line.contains(conditionsDatas[j].key))
                    {
                        QString str = line.section('=',1,1);
                        conditionsDatas[j].value = str;
                        break;
                    }
                }
            }
        }
        pointDatas.clear();
        if(line.contains("[DATA]"))
        {
            double startAngle = 0;
            double angleGip = 0;
            QString angleStr = findDataInfo(QString::fromLocal8Bit(START_TARGET_ANGLE));
            if(angleStr != "")
            {
                startAngle = angleStr.toDouble();
                qDebug()<<"startAngle="<<startAngle;
            }


            QString angleGipStr = findDataInfo(QString::fromLocal8Bit(TARGET_NORMAL_ANGLE));
            if(angleGipStr != "")
            {
                angleGip = angleGipStr.toDouble();
                qDebug()<<"angleGip="<<angleGip;
            }
            double v1 = 0;
            v1 = startAngle;
            std::vector<Point3D> points;
            while(line != "")
            {
                if(line.contains("[/DATA]"))
                {
                    if(points.size() > 0)
                    {
                        pointDatas.push_back(points);
                        points.clear();
                    }
                    v1 = v1 + angleGip;
                    line = in.readLine();
                    continue;
                }
                if(line.contains("[DATA]"))
                {
                    line = in.readLine();
                    line = in.readLine();
                }
                std::istringstream s(line.toStdString());
                double v2, v3, v4;
                s >> v2 >> v3 >> v4;
                if(rcsMin > v3)
                {
                    rcsMin = v3;
                }
                if(rcsMax < v3)
                {
                    rcsMax = v3;
                }
//                datas.push_back(CURVE_DATA(v1, v2, v3, v4));
                points.push_back(Point3D(v1, v2, v3));
                line = in.readLine();

            }
        }

    }
}

QString ModelRCSF::findDataInfo(QString key)
{
    for(int i = 0; i < taskDatas.size(); i++)
    {
        if(key == taskDatas[i].key)
        {
            return taskDatas[i].value;
        }
    }
    for(int i = 0; i < systemDatas.size(); i++)
    {
        if(key == systemDatas[i].key)
        {
            return systemDatas[i].value;
        }
    }
    for(int i = 0; i < conditionsDatas.size(); i++)
    {
        if(key == conditionsDatas[i].key)
        {
            return conditionsDatas[i].value;
        }
    }
    return "";
}

bool ModelRCSF::findDataInfoFlag(QString key)
{
    for(int i = 0; i < taskDatas.size(); i++)
    {
        if(key == taskDatas[i].key)
        {
            return true;
        }
    }
    for(int i = 0; i < systemDatas.size(); i++)
    {
        if(key == systemDatas[i].key)
        {
            return true;
        }
    }
    for(int i = 0; i < conditionsDatas.size(); i++)
    {
        if(key == conditionsDatas[i].key)
        {
            return true;
        }
    }
    return false;
}

void ModelRCSF::setXStype(int type)
{
    xStype = type;
}

void ModelRCSF::setCurrentValue(double value)
{
    currentValue = value;
}


std::vector<Point2D> ModelRCSF::getPoint2D()
{
    std::vector<Point2D> points;
    if(xStype == 0) // 频率
    {
        for(int i = 0; i < pointDatas.size(); i++)
        {
            std::vector<Point3D>& currentpoints = pointDatas[i];
            if(fabs(currentpoints[0].x - currentValue)<=0.00001)
            {
                for(int j = 0; j < currentpoints.size(); j++)
                {
                    Point3D& p = currentpoints[j];
                    points.push_back(Point2D(p.y, p.z));
                }
                return points;
            }
        }
    } else if(xStype == 1) { // 角度
        for(int i = 0; i < pointDatas.size(); i++)
        {
            std::vector<Point3D>& currentpoints = pointDatas[i];
            for(int j = 0; j < currentpoints.size(); j++)
            {
                if(fabs(currentpoints[j].y - currentValue) <= 0.00001)
                {
                        Point3D& p = currentpoints[j];
                        points.push_back(Point2D(p.x, p.z));
                }
            }
        }
        return points;
    }
    return points;
}

//std::vector<Point3D> ModelRCSF::getPoint3D()
//{
//    std::vector<Point3D> points;
//    for(int i = 0; i < datas.size(); i++)
//    {
//        points.push_back(Point3D(datas[i].angle, datas[i].fo, datas[i].rcs));
//    }
//    return points;
//}

int ModelRCSF::getXcount()
{
    QString startStr = findDataInfo(QString::fromLocal8Bit(START_TARGET_ANGLE));
    QString endStr = findDataInfo(QString::fromLocal8Bit(END_TARGET_ANGLE));
    QString angleGipStr = findDataInfo(QString::fromLocal8Bit(TARGET_NORMAL_ANGLE));

    return 1 + (endStr.toFloat() - startStr.toFloat())/angleGipStr.toFloat();
}

void ModelRCSF::getRCSRange(double &min, double& max)
{
    min = rcsMin;
    max = rcsMax;
}

