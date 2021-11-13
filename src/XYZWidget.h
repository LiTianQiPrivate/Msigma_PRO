#ifndef XYZWIDGET_H
#define XYZWIDGET_H

#include <QDialog>
#include "ModelRCSF.h"

namespace Ui {
class XYZWidget;
}

class XYZWidget : public QDialog
{
    Q_OBJECT

public:
    explicit XYZWidget(QWidget *parent = nullptr);
    ~XYZWidget();
    void setModelRCSF(ModelRCSF* modelRcsf);
    void getReturn(int& xType, double& value);
    bool getIsOK();


private slots:
    void on_xcomboBox_currentIndexChanged(int index);

    void on_okpushButton_clicked();

    void on_cancelpushButton_clicked();

private:
    Ui::XYZWidget *ui;
    ModelRCSF* modelRCSF = nullptr;
    bool isOK = false;
};

#endif // XYZWIDGET_H
