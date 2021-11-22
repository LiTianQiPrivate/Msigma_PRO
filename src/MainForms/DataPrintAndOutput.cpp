#include "DataPrintAndOutput.h"
#include "ui_DataPrintAndOutput.h"

DataPrintAndOutput::DataPrintAndOutput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataPrintAndOutput)
{
    ui->setupUi(this);
}

DataPrintAndOutput::~DataPrintAndOutput()
{
    delete ui;
}
