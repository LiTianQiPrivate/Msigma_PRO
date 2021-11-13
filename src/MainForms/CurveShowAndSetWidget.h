#ifndef CURVESHOWANDSETWIDGET_H
#define CURVESHOWANDSETWIDGET_H

#include <QWidget>
#include "CurveViewForm.h"
#include "AddCheckBox.h"
#include "AddThresholdDot.h"
namespace Ui {
class CurveShowAndSetWidget;
}
class AddCheckBox;
class CurveShowAndSetWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CurveShowAndSetWidget(QWidget *parent = nullptr);
    ~CurveShowAndSetWidget();
    int getCurrentWindow();  // 获取当前窗口
    void setCheckBox(std::vector<ModelBase *>modelBases, int index);    // 判断当前窗口动态创建checkBox
    void setCheckBoxState();
    void getModelBase(std::vector<ModelBase *>modelBases, int index);
private slots:
    void on_comboBox_7_currentIndexChanged(int index);
    void on_pushButton_clicked(bool checked);

    void on_pushButton_2_clicked(bool checked);

    void on_pushButton_9_clicked(bool checked);

    void on_pushButton_10_clicked(bool checked);

    void on_pushButton_3_clicked(bool checked);

//    void on_pushButton_4_clicked(bool checked);

    void on_pushButton_5_clicked(bool checked);

    void on_pushButton_6_clicked(bool checked);

    void on_pushButton_7_clicked(bool checked);

 //   void on_pushButton_8_clicked(bool checked);

    void on_pushButton_11_clicked(bool checked);

    void on_pushButton_12_clicked(bool checked);

    void on_pushButton_18_clicked(bool checked);

    void on_pushButton_13_clicked(bool checked);

    void on_pushButton_14_clicked(bool checked);

    void on_pushButton_15_clicked(bool checked);

    void on_pushButton_16_clicked(bool checked);

    void on_pushButton_17_clicked(bool checked);

    void on_comboBox_8_activated(int index);

    void on_comboBox_9_activated(int index);

    void on_radioButton_clicked(bool checked);

    void on_comboBox_6_activated(int index);

private:
    Ui::CurveShowAndSetWidget *ui;
    int m_currentIndex;
    std::vector<ModelBase *>m_modelBases[4];
    AddCheckBox *addCheckBox;
    AddThresholdDot *dot = nullptr;
};

#endif // CURVESHOWANDSETWIDGET_H
