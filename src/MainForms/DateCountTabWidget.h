#ifndef DATECOUNTTABWIDGET_H
#define DATECOUNTTABWIDGET_H

#include <QWidget>
#include <QTableWidget>
namespace Ui {
class DateCountTabWidget;
}
class ModelBase;
class DateCountTabWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DateCountTabWidget(QWidget *parent = nullptr);
    ~DateCountTabWidget();
    void addModelObject(ModelBase *object);
    std::vector<ModelBase *> modelBases;
    QAction *getActionState();
    int getCount();
    std::vector<ModelBase *> getModelBase()
    {
        return modelBases;
    }
    QTableWidget *getTableWidget();
    void addColumnTab(QTableWidget *table);
    int tableCount = 0;
    std::vector<QString> strs;
    std::vector<std::vector<double> > tableValues;
    void setTableWidgetValue(std::vector<std::vector<double> > values);
private slots:
    void on_tableWidget_customContextMenuRequested(const QPoint &pos);

    void on_pushButton_3_clicked(bool checked);

    void on_pushButton_4_clicked(bool checked);

    void on_pushButton_5_clicked(bool checked);

    void on_pushButton_6_clicked(bool checked);

private:
    Ui::DateCountTabWidget *ui;
};

#endif // DATECOUNTTABWIDGET_H
