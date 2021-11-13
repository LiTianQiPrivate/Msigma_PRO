#include "WaterfallWidget.h"
#include "Point3D.h"
#include "VTKGeometry.h"
#include <vtkScalarBarActor.h>
#include <vtkFloatArray.h>
#include <vtkPointData.h>
#include "ModelRCSF.h"
#include "vtkProperty.h"
#include "vtkTextProperty.h"

WaterfallWidget::WaterfallWidget(QWidget *parent, QString className) : QVTKOpenGLStereoWidget(parent),MsigmaBase(className)
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

    // 刻度尺
    m_cubeAxesActor = vtkSmartPointer<vtkCubeAxesActor>::New();
    m_cubeAxesActor->SetCamera(renderer->GetActiveCamera());
}


void WaterfallWidget::OnRightButtonDown()
{

}

void WaterfallWidget::OnRightButtonUp()
{

}

void WaterfallWidget::OnLeftButtonDown()
{

}

void WaterfallWidget::OnMouseMove()
{

}

void WaterfallWidget::OnLeftButtonUp()
{

}

void WaterfallWidget::resetCamera()
{
    renderer->ResetCamera();
    this->renderWindow()->Render();
}

void WaterfallWidget::initScalarBarWidget(vtkLookupTable *lookupTable)
{
    scalarWidget->SetInteractor(this->renderWindow()->GetInteractor());
    scalarWidget->GetScalarBarActor()->SetTitle("RCSF");
    scalarWidget->GetScalarBarActor()->SetLookupTable((vtkScalarsToColors*)lookupTable);
    scalarWidget->On();
}

void WaterfallWidget::setModelBases(std::vector<ModelBase *> modelObjects, int index)
{
    clearModelBase();
    if(modelObjects.size() > 0)
    {
        addModelBase(modelObjects[modelObjects.size() - 1]);
    }
}

void WaterfallWidget::addModelBase(ModelBase *modelObject)
{

    vtkSmartPointer<vtkFloatArray> pointArray = vtkSmartPointer<vtkFloatArray>::New();
    pointArray->SetNumberOfComponents(1);
    std::vector<std::vector<Point3D>>& lines = modelObject->getPointDatas();
    if(lines.size() <= 1)
    {
        return;
    }
    double min = 10000000, max = -100000000;
    for(int i = 0; i < lines.size(); i++)
    {
        std::vector<Point3D>& points = lines[i];
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
//    if(is2D)
//    {
//        vtkPoints* points = rcsfPolyData.getPolyData()->GetPoints();
//        for(int i = 0; i < points->GetNumberOfPoints(); i++)
//        {
//            double* p = points->GetPoint(i);
//            points->SetPoint(i, p[0], p[1], 0);
//        }
//        rcsfPolyData.getPolyData()->SetPoints(points);
//    }

    VTKGeometry::makeTriangles(lines, rcsfPolyData.getPolyData(), false);

    // 添加颜色映射与颜色条窗口
    pColorTable->SetRange(min,max);
    pColorTable->SetTableRange(min,max);
    pColorTable->SetHueRange(0.6, 0);//HSV  H
    pColorTable->Build();
    rcsfPolyData.getPolyData()->GetPointData()->SetScalars(pointArray);
    rcsfPolyData.getActor("WaterfallWidget")->GetMapper()->SetLookupTable(pColorTable);
    rcsfPolyData.getActor("WaterfallWidget")->GetMapper()->SetScalarRange(min, max);
    rcsfPolyData.getActor("WaterfallWidget")->GetMapper()->ScalarVisibilityOn();
    renderer->AddActor(rcsfPolyData.getActor("WaterfallWidget"));
    initScalarBarWidget(pColorTable);
    // 添加刻度尺

    initCubeAxesActor(rcsfPolyData.getPolyData());



    resetCamera();
}

void WaterfallWidget::initCubeAxesActor(vtkPolyData *polyData)
{
    polyData->ComputeBounds();
    double* bound = polyData->GetBounds();
    //设置x、y、z轴的起始和终止值

    m_cubeAxesActor->SetBounds(bound);
    //设置坐标轴线的宽度
    m_cubeAxesActor->GetXAxesLinesProperty()->SetLineWidth(4);
    m_cubeAxesActor->GetYAxesLinesProperty()->SetLineWidth(4);
    m_cubeAxesActor->GetZAxesLinesProperty()->SetLineWidth(4);
    //设置标题和标签文本的屏幕大小。默认值为10.0。
    m_cubeAxesActor->SetScreenSize(7);
    //指定标签与轴之间的距离。默认值为20.0。
    m_cubeAxesActor->SetLabelOffset(20);
    m_cubeAxesActor->GetLabelTextProperty(0)->SetColor(0, 0, 0);
    m_cubeAxesActor->GetLabelTextProperty(1)->SetColor(0, 0, 0);
    m_cubeAxesActor->GetLabelTextProperty(2)->SetColor(0, 0, 0);
    m_cubeAxesActor->GetXAxesLinesProperty()->SetColor(0, 0, 0);
    m_cubeAxesActor->GetYAxesLinesProperty()->SetColor(0, 0, 0);
    m_cubeAxesActor->GetZAxesLinesProperty()->SetColor(0, 0, 0);

    m_cubeAxesActor->SetXTitle("");
    m_cubeAxesActor->SetYTitle("");
    m_cubeAxesActor->SetZTitle("");

    m_cubeAxesActor->GetTitleTextProperty(0)->SetColor(0, 0, 0);
    m_cubeAxesActor->GetTitleTextProperty(1)->SetColor(0, 0, 0);
    m_cubeAxesActor->GetTitleTextProperty(2)->SetColor(0, 0, 0);
    //显示坐标轴
    m_cubeAxesActor->SetVisibility(true);
//    if(is2D)
//    {
//        m_cubeAxesActor->SetZAxisVisibility(false);
//    }
    //指定一种模式来控制轴的绘制方式
    m_cubeAxesActor->SetFlyMode(3);
//    m_cubeAxesActor->SetFlyModeToStaticEdges();//调整坐标轴显示固定在一个轴上

    //网格设置
    //开启x、y、z轴的网格线绘制
    m_cubeAxesActor->SetDrawXGridlines(false);
    m_cubeAxesActor->SetDrawYGridlines(false);
    m_cubeAxesActor->SetDrawZGridlines(false);
//    m_cubeAxesActor->DrawXGridlinesOn();
//    m_cubeAxesActor->DrawYGridlinesOn();
//    m_cubeAxesActor->DrawZGridlinesOn();
    //设置x、y、z轴的内部网格线不绘制
    m_cubeAxesActor->SetDrawXInnerGridlines(false);
    m_cubeAxesActor->SetDrawYInnerGridlines(false);
    m_cubeAxesActor->SetDrawZInnerGridlines(false);
    //设置x、y、z轴网格线的颜色
    m_cubeAxesActor->GetXAxesGridlinesProperty()->SetColor(0, 0, 0);
    m_cubeAxesActor->GetYAxesGridlinesProperty()->SetColor(0, 0, 0);
    m_cubeAxesActor->GetZAxesGridlinesProperty()->SetColor(0, 0, 0);
    //指定网格线呈现的样式
    m_cubeAxesActor->SetGridLineLocation(2);
    //
    //刻度的设置
    //不显示x、y、z轴的次刻度
    m_cubeAxesActor->XAxisMinorTickVisibilityOff();
    m_cubeAxesActor->YAxisMinorTickVisibilityOff();
    m_cubeAxesActor->ZAxisMinorTickVisibilityOff();
    //设置刻度标签的显示方式(参数1为false，刻度标签按0-200000显示；为true时，按0-200显示)
    m_cubeAxesActor->SetLabelScaling(1, 0, 0, 0);
    //设置刻度线显示的位置(内部、外部、两侧)
    m_cubeAxesActor->SetTickLocation(1);


    renderer->AddActor(m_cubeAxesActor);
}

void WaterfallWidget::setIs2D(bool value)
{
    is2D = value;
}


void WaterfallWidget::clearModelBase()
{

}

void WaterfallWidget::updataView()
{
    resetCamera();
}
