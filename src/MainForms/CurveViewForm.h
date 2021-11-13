#ifndef CURVEVIEWFORM_H
#define CURVEVIEWFORM_H

#include <QWidget>
#include "ViewForm.h"
#include <QMouseEvent>
namespace Ui {
class CurveViewForm;
}

class CurveViewForm : public QWidget
{
    Q_OBJECT

public:
    explicit CurveViewForm(QWidget *parent = nullptr);
    ~CurveViewForm();
    void resizeEvent(QResizeEvent *event);
    void initUpdataLayout();
    int getViewFormCount();
    ViewForm *getViewFromWidget(int index);
    void addModelBase(ModelBase* modelBase, int viewID);

private slots:

    void on_grodtoolButton_clicked();

    void on_hortoolButton_clicked();

    void on_vertoolButton_clicked();

    void on_checkBox1_clicked(bool checked);

    void on_checkBox2_clicked(bool checked);

    void on_checkBox_3_clicked(bool checked);

    void on_checkBox_4_clicked(bool checked);

private:
    Ui::CurveViewForm *ui;
    std::vector<ViewForm*> viewForms;
    int layoutType = 0; // 0, 1, 2
protected:
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // CURVEVIEWFORM_H
