#include "ModelRCS.h"
#include <QTextStream>
#include <QFile>
#include <QFileInfo>
#include <sstream>
ModelRCS::ModelRCS(QString className) : ModelBase(className)
{
    conditionsDatas.push_back(TASK_DATA(QString::fromLocal8Bit(MEASURING)));
    conditionsDatas.push_back(TASK_DATA(QString::fromLocal8Bit(FPS_COUNT)));
    conditionsDatas.push_back(TASK_DATA(QString::fromLocal8Bit(WORK_FPS)));
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

void ModelRCS::loadFile(QString filePath)
{
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }
    pointDatas.clear();
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

        std::vector<Point3D> points;
        if(line.contains("[DATA]"))
        {
            line = in.readLine();
            line = in.readLine();
            while(line != "")
            {
                if(line.contains("[/DATA]"))
                {
                    break;
                }
                static int index = 0;
                std::istringstream s(line.toStdString());
                double v1, v2, v3;
                s >> v1 >> v2 >> v3;
//                datas.push_back(CURVE_DATA(v1, v2, v3));
                points.push_back(Point3D(v1, v2, 0));
                line = in.readLine();
                index++;
            }
        }
        if(points.size() > 0)
        {
            pointDatas.push_back(points);
        }

    }
}
QString ModelRCS::findDataInfo(QString key)
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

bool ModelRCS::findDataInfoFlag(QString key)
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


std::vector<Point2D> ModelRCS::getPoint2D()
{
    std::vector<Point2D> data;
    if(pointDatas.size() == 0)
    {
        return data;
    }
    std::vector<Point3D>& points = pointDatas[0];

    for(int i = 0; i < points.size(); i++)
    {
        data.push_back(Point2D(points[i].x, points[i].y));
    }
    return data;
}

