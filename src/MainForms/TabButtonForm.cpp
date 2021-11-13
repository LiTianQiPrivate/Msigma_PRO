#include "TabButtonForm.h"
#include "ui_TabButtonForm.h"

TabButtonForm::TabButtonForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabButtonForm)
{
    ui->setupUi(this);
}

TabButtonForm::~TabButtonForm()
{
    delete ui;
}

QToolButton *TabButtonForm::getAddButton()
{
    return ui->addtoolButton;
}

QToolButton *TabButtonForm::getRemoveButton()
{
    return ui->removetoolButton;
}

QToolButton *TabButtonForm::getChangedButton()
{
    return ui->changedButton;
}

