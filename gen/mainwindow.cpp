#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "main.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->idLineEdit->setText(id);
    ui->titleLineEdit->setText(title);
    ui->descriptionLineEdit->setText(description);
    ui->authorLineEdit->setText(author);
    ui->versionLineEdit->setText(version);
    ui->iconLineEdit->setText(icon);
    ui->typeLineEdit->setText(type);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    id = ui->idLineEdit->text();
    title = ui->titleLineEdit->text();
    description = ui->descriptionLineEdit->text();
    author = ui->authorLineEdit->text();
    version = ui->versionLineEdit->text();
    icon = ui->iconLineEdit->text();
    type = ui->typeLineEdit->text();
    generate();
}
