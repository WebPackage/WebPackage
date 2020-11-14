#include "info.h"
#include "ui_info.h"
#include "main.h"

Info::Info(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::info)
{
    ui->setupUi(this);
}

Info::~Info()
{
    delete ui;
}

void Info::on_buttonBox_clicked(QAbstractButton *button)
{
    close();
}
