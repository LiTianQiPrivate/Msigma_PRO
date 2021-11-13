#ifndef VIEWFROMHISGRAM_H
#define VIEWFROMHISGRAM_H

#include <QWidget>
#include "DrawHistogramChart.h"

namespace Ui {
class ViewFromHisgram;
}

class ViewFromHisgram : public QWidget
{
    Q_OBJECT

public:
    explicit ViewFromHisgram(QWidget *parent = nullptr);
    ~ViewFromHisgram();
    void resizeEvent(QResizeEvent *event);
    DrawHistogramChart  *msigmaBase = nullptr;
    void getValues(std::vector<std::vector<double> > values, std::vector<QString> strs, int index);
    DrawHistogramChart  *setDrawHistogramChart()
    {
        return msigmaBase;
    }
private slots:
    void on_comboBox_2_activated(int index);

    void on_comboBox_3_activated(int index);

private:
    Ui::ViewFromHisgram *ui;

};

#endif // VIEWFROMHISGRAM_H
