#include "DataTranslationAline.h"
#include "ui_DataTranslationAline.h"

DataTranslationAline::DataTranslationAline(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataTranslationAline)
{
    ui->setupUi(this);
}

DataTranslationAline::~DataTranslationAline()
{
    delete ui;
}
