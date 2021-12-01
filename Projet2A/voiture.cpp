#include "voiture.h"
#include "ui_voiture.h"

voiture::voiture(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::voiture)
{
    ui->setupUi(this);
}

voiture::~voiture()
{
    delete ui;
}
