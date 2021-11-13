#ifndef MODELTABLEWIDGET_H
#define MODELTABLEWIDGET_H

#include <QWidget>
#include "ModelBase.h"
#include "QMouseEvent"
#include <QMenu>
#include "QTableWidget"
#include "qtoolbutton.h"
#include <QPushButton>

namespace Ui {
class ModelTableWidget;
}

class ModelTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ModelTableWidget(QWidget *parent = nullptr);
    ~ModelTableWidget();
    void addModelObject(ModelBase *object);

//    void on_moveUp_clicked();

private slots:
    void on_tableWidget_customContextMenuRequested(const QPoint &pos);

    void on_add1Action_triggered();

    void on_add2action_triggered();

    void on_add3action_triggered();

    void on_add4action_triggered();

    void on_tableWidget_itemClicked(QTableWidgetItem *item);

private:
    Ui::ModelTableWidget *ui;
    std::vector<ModelBase*> modelBases;
    std::vector<ModelBase*> modelBase_1;
    QPushButton toolButton1;
    QPushButton toolButton2;

};

#endif // MODELTABLEWIDGET_H
