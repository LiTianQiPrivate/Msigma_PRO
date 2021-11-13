#ifndef STATISTICALANALYSISWIDGET_H
#define STATISTICALANALYSISWIDGET_H

#include <QWidget>
#include <QTableWidgetItem>

namespace Ui {
class StatisticalAnalysisWidget;
}

class StatisticalAnalysisWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StatisticalAnalysisWidget(QWidget *parent = nullptr);
    ~StatisticalAnalysisWidget();

private slots:
    void on_tableWidget_itemChanged(QTableWidgetItem *item);

    void on_pushButton_clicked(bool checked);

    void on_pushButton_2_clicked(bool checked);

    void on_pushButton_3_clicked(bool checked);

private:
    Ui::StatisticalAnalysisWidget *ui;
};

#endif // STATISTICALANALYSISWIDGET_H
