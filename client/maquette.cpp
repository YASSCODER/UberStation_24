#include "maquette.h"
#include "ui_maquette.h"
#include "client.h"
//#include <QIntValidator>
#include <QObject>
#include <QMessageBox>
maquette::maquette(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::maquette)
{
    ui->setupUi(this);
  //  ui->le_CIN->setValidator( new QIntValidator(100, 999, this));
    ui->tab_client->setModel(C.afficher());


}

maquette::~maquette()
{
    delete ui;
}

void maquette::on_pb_ajouter_clicked()
{
    QString CIN_C=ui->le_CIN->text();
    QString Nom=ui->le_nom->text();
    QString Prenom=ui->le_prenom->text();
    QString NumeroTel=ui->le_numTel->text();
    QString Mail=ui->le_mail->text();
  Client C(CIN_C,Nom,Prenom,NumeroTel,Mail);
  bool test = C.ajouter();
  QMessageBox msgBox;
  if (test)


             msgBox.setText("Ajout avec succes.");
                        else
             msgBox.setText("Echec d'ajout.");

         msgBox.exec();
}




void maquette::on_pb_supprimer_clicked()
{
  Client C1; C1.setCIN_C(ui->le_CIN_supp->text());
  bool test=C1.supprimer(C1.getCIN_C());
  QMessageBox msgBox;
  if (test)


             msgBox.setText("Suppression avec succes.");
                        else
             msgBox.setText("Echec de suppression.");

         msgBox.exec();
}

