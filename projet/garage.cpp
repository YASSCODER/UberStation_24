#include "garage.h"
#include "ui_garage.h"

Garage::Garage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Garage)
{
    ui->setupUi(this);
}

Garage::~Garage()
{
    delete ui;
}
