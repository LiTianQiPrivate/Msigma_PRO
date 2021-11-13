#ifndef VIEWINTERATORSTYLETRACKBALLCAMERA_H
#define VIEWINTERATORSTYLETRACKBALLCAMERA_H

#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkCellPicker.h"
#include "vtkRenderer.h"
//
//#include "Common.h"

class ViewBase;

class ViewInteratorStyleTrackballCamera : public vtkInteractorStyleTrackballCamera
{
public :
    static ViewInteratorStyleTrackballCamera* New();
    vtkTypeMacro(ViewInteratorStyleTrackballCamera, vtkInteractorStyleTrackballCamera);
    //
    ViewInteratorStyleTrackballCamera();
    //
//    void setModelWidget(PointCloudViewer* widget);
    void setRenderer(vtkRenderer* renderer);
    void resetMouseWheelValue();
    void set2DMode(bool arg);
    //
    virtual void OnMouseMove();
    virtual void OnLeftButtonDown();
    virtual void OnLeftButtonUp();
    virtual void OnMiddleButtonDown();
    virtual void OnMiddleButtonUp();
    virtual void OnRightButtonDown();
    virtual void OnRightButtonUp();
    virtual void OnMouseWheelForward();
    virtual void OnMouseWheelBackward();

    void setViewBase(ViewBase *value);

public:
    bool leftButtonPressed, middleButtonPressed, rightButtonPressed;
private:
    vtkRenderer* renderer;
    //    VSP<vtkCellPicker> picker;

    bool twoDimensional;
    ViewBase* modelViewer; // 3D窗口

};


#endif // VIEWINTERATORSTYLETRACKBALLCAMERA_H
