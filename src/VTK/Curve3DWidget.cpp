#include "Curve3DWidget.h"
#include "Point3D.h"
#include "VTKGeometry.h"
#include <vtkScalarBarActor.h>
#include <vtkFloatArray.h>
#include <vtkPointData.h>
#include "ModelRCSF.h"
#include "vtkProperty.h"
#include "vtkTextProperty.h"

Curve3DWidget::Curve3DWidget(QWidget *parent, QString className) : QVTKOpenGLStereoWidget(parent),MsigmaBase(className)
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

Curve3DWidget::~Curve3DWidget()
{
    for(int i = 0; i < lineObjects.size(); i++)
    {
        delete lineObjects[i];
    }
}

void Curve3DWidget::OnRightButtonDown()
{

}

void Curve3DWidget::OnRightButtonUp()
{

}

void Curve3DWidget::OnLeftButtonDown()
{

}

void Curve3DWidget::OnMouseMove()
{

}

void Curve3DWidget::OnLeftButtonUp()
{

}

void Curve3DWidget::resetCamera()
{
    renderer->ResetCamera();
    this->renderWindow()->Render();
}

void Curve3DWidget::initScalarBarWidget(vtkLookupTable *lookupTable)
{
    scalarWidget->SetInteractor(this->renderWindow()->GetInteractor());
    scalarWidget->GetScalarBarActor()->SetTitle("RCSF");
    scalarWidget->GetScalarBarActor()->SetLookupTable((vtkScalarsToColors*)lookupTable);
    scalarWidget->On();
}

void Curve3DWidget::setModelBases(std::vector<ModelBase *> modelObjects, int index)
{
    clearModelBase();
    if(modelObjects.size() > 0)
    {
        addModelBase(modelObjects[index]);
    }
}

void Curve3DWidget::addModelBase(ModelBase *modelObject)
{

    vtkSmartPointer<vtkFloatArray> pointArray = vtkSmartPointer<vtkFloatArray>::New();
    pointArray->SetNumberOfComponents(1);
    std::vector<std::vector<Point3D>>& lines = modelObject->getPointDatas();
    if(lines.size() <= 1)
    {
        return;
    }
    double bound[6] = {0};
    for(int i = 0; i < lines.size(); i++)
    {
        std::vector<Point3D>& points = lines[i];
        for(int j = 0; j < points.size(); j++)
        {
            Point3D& p = points[j];
            double x = p.x,y = p.y,z = p.z;
            if(i == 0)
            {
                bound[0] = bound[1] = x;
                bound[2] = bound[3] = y;
                bound[4] = bound[5] = z;
            }
            else
            {
                if(x<bound[0])
                    bound[0] = x;
                else if(x>bound[1])
                    bound[1] = x;

                if(y<bound[2])
                    bound[2] = y;
                else if(y>bound[3])
                    bound[3] = y;

                if(z<bound[4])
                    bound[4] = z;
                else if(z>bound[5])
                    bound[5] = z;
            }
        }
    }


    for(int i = 0; i < lines.size(); i++)
    {
        std::vector<Point3D>& points = lines[i];
        LineObject* lineObject = new LineObject;
        lineObject->setPoints(points);
        lineObject->setColor(0, 0, 0);
        lineObjects.push_back(lineObject);
        renderer->AddActor(lineObject->getActor("Curve3DWidget"));

    }

    // 添加刻度尺
    initCubeAxesActor(bound);
    resetCamera();
}

void Curve3DWidget::initCubeAxesActor(double *bound)
{
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


void Curve3DWidget::clearModelBase()
{
    for(int i = 0; i < lineObjects.size(); i++)
    {
        delete lineObjects[i];
    }
    lineObjects.clear();
}

void Curve3DWidget::updataView()
{
    resetCamera();
}
