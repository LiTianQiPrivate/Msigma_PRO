#ifndef STEPWIDGET_H
#define STEPWIDGET_H

#include <QWidget>
#include <QToolBox>

namespace Ui {
class StepWidget;
}

class StepWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StepWidget(QWidget *parent = nullptr);
    ~StepWidget();
    void setWidget(int index, QWidget* widget);
    int getStepWidgetIndex();
    QToolBox *getStepWidgetQtoolBox();

private:
    Ui::StepWidget *ui;
};

#endif // STEPWIDGET_H
