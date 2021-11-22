#ifndef DATAPRINTANDOUTPUT_H
#define DATAPRINTANDOUTPUT_H

#include <QWidget>

namespace Ui {
class DataPrintAndOutput;
}
/**
 * @brief The DataPrintAndOutput class
 * 数据打印与输出
 */
class DataPrintAndOutput : public QWidget
{
    Q_OBJECT

public:
    explicit DataPrintAndOutput(QWidget *parent = nullptr);
    ~DataPrintAndOutput();

private:
    Ui::DataPrintAndOutput *ui;
};

#endif // DATAPRINTANDOUTPUT_H
