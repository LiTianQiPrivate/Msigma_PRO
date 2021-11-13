#ifndef VIEWBASE_H
#define VIEWBASE_H


class ViewBase
{
public:
    enum MOUSE_ACTION
    {
        INVALID_MOUSE
    };
    ViewBase();
    virtual void OnMouseMove()
    {

    }
    virtual void OnLeftButtonDown()
    {

    }
    virtual void OnLeftButtonUp()
    {

    }
    virtual void OnRightButtonDown()
    {

    }
    virtual void OnRightButtonUp()
    {

    }
    MOUSE_ACTION getMouseAction() const;
    void setMouseAction(const MOUSE_ACTION &value);

protected:
    MOUSE_ACTION mouseAction; // 鼠标交互类型
};

#endif // VIEWBASE_H
