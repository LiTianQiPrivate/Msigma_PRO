#ifndef DATATRANSLATIONALINE_H
#define DATATRANSLATIONALINE_H

#include <QWidget>

namespace Ui {
class DataTranslationAline;
}
/**
 * @brief The DataTranslationAline class
 * 数据平滑与分析
 */
class DataTranslationAline : public QWidget
{
    Q_OBJECT

public:
    explicit DataTranslationAline(QWidget *parent = nullptr);
    ~DataTranslationAline();

private:
    Ui::DataTranslationAline *ui;
};

#endif // DATATRANSLATIONALINE_H
