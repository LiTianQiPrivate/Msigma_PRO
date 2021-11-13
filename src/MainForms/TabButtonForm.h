#ifndef TABBUTTONFORM_H
#define TABBUTTONFORM_H

#include <QWidget>
#include <QToolButton>

namespace Ui {
class TabButtonForm;
}

class TabButtonForm : public QWidget
{
    Q_OBJECT

public:
    explicit TabButtonForm(QWidget *parent = nullptr);
    ~TabButtonForm();
    QToolButton* getAddButton();
    QToolButton* getRemoveButton();
    QToolButton* getChangedButton();

private:
    Ui::TabButtonForm *ui;
};

#endif // TABBUTTONFORM_H
