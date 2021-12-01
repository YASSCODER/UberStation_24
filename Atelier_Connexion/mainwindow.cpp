#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"employe.h"
#include<QMessageBox>
#include<QIntValidator>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     QValidator *validator = new QIntValidator(100, 999, this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

