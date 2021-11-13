#ifndef ADDCHECKBOX_H
#define ADDCHECKBOX_H

#include <QWidget>
#include <QCheckBox>
#include <set>
/**
 *
 * 动态添加checkBox
 */
namespace Ui {
class AddCheckBox;
}
struct datas
{
    std::set<int> key;
    std::set<QString> value1;
    std::set<QString> value2;
    std::set<QString> value3;
    std::set<QString> value4;
    std::set<QString> value5;
    std::set<QString> value6;
    std::set<QString> value7;
    std::set<QString> value8;
};
class AddCheckBox : public QWidget
{
    Q_OBJECT

public:
    explicit AddCheckBox(QWidget *parent = nullptr);
    ~AddCheckBox();
    void addTypeData(datas data,int index);
    std::set<QString> getClickButton();

private slots:
    void on_chickCheckBox(bool v);

private:
    Ui::AddCheckBox *ui;
    std::set<QString> keys;
    std::set<QString> values;
    std::vector<QCheckBox*> checkBoxs1;
    std::vector<QCheckBox*> checkBoxs2;
    std::vector<QCheckBox*> checkBoxs3;
    std::vector<QCheckBox*> checkBoxs4;
    std::vector<QCheckBox*> checkBoxs5;
    std::vector<QCheckBox*> checkBoxs6;
    std::vector<QCheckBox*> checkBoxs7;
    std::vector<QCheckBox*> checkBoxs8;
    int m_currentIndex;   // 记录curveShowAndSetWidget里现在所选的窗口
};

#endif // ADDCHECKBOX_H
