#include "flow.h"
#include "ui_flow.h"
#include "main.h"

Flow::Flow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Flow)
{
    ui->setupUi(this);
}

Flow::~Flow()
{
    delete ui;
}

void Flow::on_actionImport_triggered()
{
    main::importPkg(QFileDialog::getOpenFileName(this, tr("Open Package For Import"), QDir::homePath(), tr("Web Packages (*.webpkg)")));
}

void Flow::on_InfoButton_clicked()
{
    main::info();
}

void Flow::on_startButton_clicked()
{
    main::start();
}

void Flow::on_actionExport_triggered()
{
    main::exportPkg(QFileDialog::getSaveFileName(this, tr("Save Package For Export"), QDir::homePath(), tr("Web Packages (*.webpkg)")));
}

void Flow::on_actionDelete_triggered()
{
    main::deletePkg();
}

void Flow::on_actionRefresh_triggered()
{
    main::refresh();
}
