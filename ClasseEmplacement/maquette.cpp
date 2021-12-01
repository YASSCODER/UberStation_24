#include "maquette.h"
#include "ui_maquette.h"
#include "emplacement.h"
#include <QMessageBox>
#include <QObject>
#include <QSqlQueryModel>
#include <QIntValidator>



maquette::maquette(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::maquette)
{
    ui->setupUi(this);
    ui->le_id->setValidator(new QIntValidator(0, 999999, this));
    ui->le_nb_max->setValidator(new QIntValidator(2, 999999, this));
   // ui->tab_emplacement->setModel(E.afficher());

}

maquette::~maquette()
{
    delete ui;
}

void maquette::on_pb_ajouter_clicked()
{
       int id = ui->le_id->text().toInt();
       QString localisation = ui->le_localisation->text();
       int nb_max = ui->le_nb_max->text().toInt();
       Emplacement E(id, localisation, nb_max);
       bool test = E.ajouter();
       if (test)
       {
           //Refresh
           //ui->tab_emplacement->setModel(E.afficher());

           QMessageBox::information (nullptr, QObject::tr("OK"),
                       QObject::tr("Ajout effectué\n"
                                       "Click cancel to exist."), QMessageBox::Cancel);
       }
       else
           QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                 QObject::tr("Ajout non effectué.\n"
                                             "Click Cancel to exist."),QMessageBox::Cancel);

}

void maquette::on_pb_supprimer_clicked()
{
    int id = ui->le_id_supp->text().toUInt();
    bool test = E.supprimer(id);
    if (test)
    {

        QMessageBox::information (nullptr, QObject::tr("OK"),
                    QObject::tr("Suppression effectué\n"
                                    "Click cancel to exist."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Suppression non effectué.\n"
                                          "Click Cancel to exist."),QMessageBox::Cancel);



}
