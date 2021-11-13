#include "TableWidget.h"
#include "ui_TableWidget.h"

TableWidget::TableWidget(QWidget *parent) :
    QTableWidget(parent),
    ui(new Ui::TableWidget)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setVisible(false);
    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->setShowGrid(false);
}

TableWidget::~TableWidget()
{
    delete ui;
}
