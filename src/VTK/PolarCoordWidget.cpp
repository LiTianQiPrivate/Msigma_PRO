#include "PolarCoordWidget.h"
#include "Point3D.h"
#include "VTKGeometry.h"
#include <vtkScalarBarActor.h>
#include <vtkFloatArray.h>
#include <vtkPointData.h>
vtkStandardNewMacro(ViewInteratorStyleTrackballCamera);
PolarCoordWidget::PolarCoordWidget(QWidget *parent, QString className) : QVTKOpenGLStereoWidget(parent),MsigmaBase(className)
{
    renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->SetBackground(1, 1, 1);
    this->renderWindow()->AddRenderer(renderer);
    // 交互器
    viewInteratorStyle = vtkSmartPointer<ViewInteratorStyleTrackballCamera>::New();
    viewInteratorStyle->setRenderer(renderer);
    vtkCellPicker* interactionPicker = vtkCellPicker::New();
    this->renderWindow()->GetInteractor()->SetPicker(interactionPicker);
    this->renderWindow()->GetInteractor()->SetInteractorStyle(viewInteratorStyle);
    viewInteratorStyle->setViewBase(this);
    scalarWidget = vtkScalarBarWidget::New();
    pColorTable = vtkSmartPointer<vtkLookupTable>::New();
}

void PolarCoordWidget::OnRightButtonDown()
{

}

void PolarCoordWidget::OnRightButtonUp()
{

}

void PolarCoordWidget::OnLeftButtonDown()
{

}

void PolarCoordWidget::OnMouseMove()
{

}

void PolarCoordWidget::OnLeftButtonUp()
{

}


void PolarCoordWidget::resetCamera()
{
    renderer->ResetCamera();
    this->renderWindow()->Render();
}

void PolarCoordWidget::initScalarBarWidget(vtkLookupTable *lookupTable)
{
    scalarWidget->SetInteractor(this->renderWindow()->GetInteractor());
    scalarWidget->GetScalarBarActor()->SetTitle("RCSF");
    scalarWidget->GetScalarBarActor()->SetLookupTable((vtkScalarsToColors*)lookupTable);
    scalarWidget->On();
}
void PolarCoordWidget::setModelBases(std::vector<ModelBase *> modelObjects, int index)
{
    clearModelBase();
    if(modelObjects.size() > 0)
    {
        addModelBase(modelObjects[modelObjects.size() - 1]);
    }
}
void PolarCoordWidget::addModelBase(ModelBase *modelObject)
{
    vtkSmartPointer<vtkFloatArray> pointArray = vtkSmartPointer<vtkFloatArray>::New();
    pointArray->SetNumberOfComponents(1);
    std::vector<std::vector<Point3D>>& pointsAll = modelObject->getPointDatas();
    if(pointsAll.size() <= 1)
    {
        return;
    }

    double startAngle = pointsAll[0][0].x;
    double endAngle = pointsAll[pointsAll.size() - 1][0].x;


    double min = 10000000, max = -100000000;
    for(int i = 0; i < pointsAll.size(); i++)
    {
        std::vector<Point3D>& points = pointsAll[i];
        for(int j = 0; j < points.size(); j++)
        {
            Point3D& p = points[j];
            pointArray->InsertNextValue(p.z);
            if(min > p.z)
            {
                min = p.z;
            }
            if(max < p.z)
            {
                max = p.z;
            }
        }
    }

    // 1.按照半径 一列一列划分数据
    int count = pointsAll.size();
    //  在中心点位置绘制一个圆
    std::vector<Point3D> roundPoint;
    for(int i = 0; i < count; i++)
    {
        Point3D point;
        point.x = 1 * sin(2*3.1415926/count*i);
        point.y = 1 * cos(2*3.1415926/count*i);
        point.z = 0;
        roundPoint.push_back(point);
    }

    std::vector<std::vector<Point3D>> lines;
    for(int i = 0; i < roundPoint.size(); i++)
    {
        std::vector<Point3D> rows;
        std::vector<Point3D>& points = pointsAll[i];
        for(int j = 0; j < points.size(); j++)
        {
            Point3D& p = points[j];
            Point3D pp(0, 0, 0);
            pp.move(&roundPoint[i], p.y);
            rows.push_back(pp);
        }
        lines.push_back(rows);
    }
    // 2.剖分数据
    if(endAngle - startAngle == 360)
    {
        VTKGeometry::makeTriangles(lines, rcsfPolyData.getPolyData(), true);
    } else {
        VTKGeometry::makeTriangles(lines, rcsfPolyData.getPolyData(), false);
    }
    rcsfPolyData.zoomToValue(200, Point3D(0, 0, 0));
    // 3.添加颜色映射与颜色条窗口
    pColorTable->SetRange(min,max);
    pColorTable->SetTableRange(min,max);
    pColorTable->SetHueRange(0.6, 0);//HSV  H
    pColorTable->Build();
    rcsfPolyData.getPolyData()->GetPointData()->SetScalars(pointArray);
    rcsfPolyData.getActor("PolarCoordWidget")->GetMapper()->SetLookupTable(pColorTable);
    rcsfPolyData.getActor("PolarCoordWidget")->GetMapper()->SetScalarRange(min, max);
    rcsfPolyData.getActor("PolarCoordWidget")->GetMapper()->ScalarVisibilityOn();
    renderer->AddActor(rcsfPolyData.getActor("PolarCoordWidget"));
    initScalarBarWidget(pColorTable);
    // 添加刻度线
    roundRuleObject.initData(105, startAngle);
    for(int i = 0; i < 360; i++)
    {
        renderer->AddActor(roundRuleObject.points[i].getActor("PolarCoordWidget"));
    }
    for(int i = 0; i < 36; i++)
    {
        renderer->AddActor(roundRuleObject.text[i].getActor());
    }
    renderer->AddActor(roundRuleObject.lineObject.getActor("PolarCoordWidget"));




    resetCamera();
}

void PolarCoordWidget::clearModelBase()
{
    renderer->RemoveActor(rcsfPolyData.getActor("PolarCoordWidget"));
    for(int i = 0; i < 360; i++)
    {
        renderer->RemoveActor(roundRuleObject.points[i].getActor("PolarCoordWidget"));
    }
    for(int i = 0; i < 36; i++)
    {
        renderer->RemoveActor(roundRuleObject.text[i].getActor());
    }
    renderer->RemoveActor(roundRuleObject.lineObject.getActor("PolarCoordWidget"));
    resetCamera();
}

void PolarCoordWidget::updataView()
{
    resetCamera();
}
