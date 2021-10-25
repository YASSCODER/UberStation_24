#include "maquette.h"
#include "ui_maquette.h"
#include"voiture.h"
#include<QMessageBox>
maquette::maquette(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::maquette)
{
    ui->setupUi(this);
}

maquette::~maquette()
{
    delete ui;
}

void maquette::on_PB_Ajout_clicked()
{
    QString matricule=ui->Matricule->text();
    QString marque=ui->Marque->text();
    QString genre=ui->Genre->text();
    int hrE=ui->heure_E->text().toInt();
    int hrS=ui->heure_S->text().toInt();
    Voiture V(matricule,marque,genre,hrE,hrS);
    bool test = V.ajouter();
           if (test)
           {

               QMessageBox::information (nullptr, QObject::tr("OK"),
                           QObject::tr("Ajout effectué\n"
                                           "Click cancel to exist."), QMessageBox::Cancel);
           }
           else
               QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                     QObject::tr("Ajout non effectué.\n"
                                                 "Click Cancel to exit."),QMessageBox::Cancel);
}


void maquette::on_PB_supp_clicked()
{


        bool test = V.supprimer(matricule);
        if (test)
        {

            QMessageBox::information (nullptr, QObject::tr("OK"),
                        QObject::tr("Suppression effectué\n"
                                        "Click cancel to exist."), QMessageBox::Cancel);
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                  QObject::tr("Suppression non effectué.\n"));

}
