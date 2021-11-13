#ifndef MODELTREEWIDGET_H
#define MODELTREEWIDGET_H

#include <QWidget>
#include "ModelBase.h"

namespace Ui {
class ModelTreeWidget;
}

class ModelTreeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ModelTreeWidget(QWidget *parent = nullptr);
    ~ModelTreeWidget();
    void addModelObject(ModelBase* object);
    void closeItem(); // 合并item
    void showItem(int index); // 展开

private:
    Ui::ModelTreeWidget *ui;
};

#endif // MODELTREEWIDGET_H
