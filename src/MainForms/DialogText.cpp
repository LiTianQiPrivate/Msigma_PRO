#include "DialogText.h"
#include "ui_DialogText.h"

DialogText::DialogText(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogText)
{
    changedText = false;
    ui->setupUi(this);
}

DialogText::~DialogText()
{
    delete ui;
}

QString DialogText::getEditText()
{
    return ui->lineEdit->text();
}

void DialogText::setLabelText(QString str)
{
    ui->label->setText(str);
}

bool DialogText::getChangedText()
{
    return changedText;
}
/**
 * @brief DialogText::on_buttonBox_clicked
 * @param button
 */
void DialogText::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button == (QAbstractButton *)(ui->buttonBox->button(QDialogButtonBox::Ok)))
    {
        changedText = true;
    }
    else if(button == (QAbstractButton *)ui->buttonBox->button(QDialogButtonBox::Cancel))
    {
        changedText = false;
    }
}
