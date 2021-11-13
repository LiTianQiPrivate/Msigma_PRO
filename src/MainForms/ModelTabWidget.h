#ifndef MODELTABWIDGET_H
#define MODELTABWIDGET_H

#include <QWidget>
#include "TabButtonForm.h"
#include "CurveViewForm.h"
#include <QString>


namespace Ui {
class ModelTabWidget;
}

class ModelTabWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ModelTabWidget(QWidget *parent = nullptr);
    ~ModelTabWidget();
    CurveViewForm* getCurrentCurveViewForm();
private slots:
    void on_addToolButton_Cliced();
    void on_removeToolButton_Cliced();
    void on_chengedToolButton_Cliced();

private:
    Ui::ModelTabWidget *ui;
    TabButtonForm tabButtonForm;
    std::vector<CurveViewForm*> curveViewForms;


};

#endif // MODELTABWIDGET_H
