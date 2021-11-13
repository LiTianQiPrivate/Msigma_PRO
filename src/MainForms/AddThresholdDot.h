#ifndef ADDTHRESHOLDDOT_H
#define ADDTHRESHOLDDOT_H

#include <QWidget>

namespace Ui {
class AddThresholdDot;
}

class AddThresholdDot : public QWidget
{
    Q_OBJECT

public:
    explicit AddThresholdDot(int index = 1,QWidget *parent = nullptr);
    ~AddThresholdDot();
    std::vector<QPointF> xyDot;

private slots:
    void on_pushButton_clicked(bool checked);

    void on_pushButton_2_clicked(bool checked);

private:
    Ui::AddThresholdDot *ui;
    int currentIndex;
};

#endif // ADDTHRESHOLDDOT_H
