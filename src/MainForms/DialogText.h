#ifndef DIALOGTEXT_H
#define DIALOGTEXT_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class DialogText;
}

class DialogText : public QDialog
{
    Q_OBJECT

public:
    explicit DialogText(QWidget *parent = nullptr);
    ~DialogText();
    QString getEditText();
    void setLabelText(QString str);
    bool getChangedText();
private slots:
    void on_buttonBox_clicked(QAbstractButton *button);
private:
    Ui::DialogText *ui;
    bool changedText;

};

#endif // DIALOGTEXT_H
