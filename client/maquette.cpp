#include "maquette.h"
#include "ui_maquette.h"
#include "client.h"
#include <QIntValidator>
#include <QObject>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QDebug>
#include <QSqlQuery>
#include <QComboBox>
#include "QrCode.hpp"
#include "notif.h"
#include "Arduino.h"


using namespace qrcodegen;
maquette::maquette(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::maquette)
{
    ui->setupUi(this);
    ui->le_CIN->setValidator( new QIntValidator(100, 999, this));
    ui->le_numTel->setValidator(new QIntValidator(100, 999,this));
    ui->tab_client->setModel(C.afficher());
    ui->sup->setModel(C.wombo_combo());

}

maquette::~maquette()
{
    delete ui;
}

void maquette::on_pb_ajouter_clicked()
{
    int CIN =ui->le_CIN->text().toInt();
    QString NOM=ui->le_nom->text();
    QString PRENOM=ui->le_prenom->text();
    int NUMERO_TEL=ui->le_numTel->text().toInt();
  Client C(CIN,NOM,PRENOM,NUMERO_TEL);
  if (CIN == 0)
  {
      QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                            QObject::tr("CIN vide .\n"
                                        "Click Cancel to exist."),QMessageBox::Cancel);
  }
  else
      if (NOM == NULL)
      {
          QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                QObject::tr("NOM vide .\n"
                                            "Click Cancel to exist."),QMessageBox::Cancel);
      }

      else
          if (PRENOM == NULL)
      {
          QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                QObject::tr("PRENOM vide .\n"
                                            "Click Cancel to exist."),QMessageBox::Cancel);
      }

      else
          if (NUMERO_TEL == 0)
      {
          QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                QObject::tr("NUMERO_TEL vide .\n"
                                            "Click Cancel to exist."),QMessageBox::Cancel);
      }


  bool test = C.ajouter();
  notif m("CLIENT","client ajouté avec succés");

                m.afficher();
  QMessageBox msgBox;
  if (test)
  {
      ui->tab_client->setModel(C.afficher());
        ui->sup->setModel(C.wombo_combo());

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
Client C;

  int CIN=ui->sup->currentText().toInt();



  bool test=C.supprimer(CIN);
  QMessageBox msgBox;
  if (test)
    {   ui->tab_client->setModel(C.afficher());
ui->sup->setModel(C.wombo_combo());
             msgBox.setText("Suppression avec succes.");
  }
                        else
             msgBox.setText("Echec de suppression.");

         msgBox.exec();
}


void maquette::on_pb_modifier_clicked()
{
        int CIN=ui->le_CIN->text().toInt();
        QString NOM=ui->le_nom->text();
        QString PRENOM=ui->le_prenom->text();
        int NUMERO_TEL=ui->le_numTel->text().toInt();
        Client C;
        bool test=C.modifier(CIN,NOM,PRENOM,NUMERO_TEL );

        if(test)
        {
             ui->tab_client->setModel(C.afficher());
             ui->sup->setModel(C.wombo_combo());
            QMessageBox::information(nullptr,QObject::tr("ok"),
                                     QObject::tr("modification effectue\n""click cancel to exit."),
                                     QMessageBox::Cancel);

        }

        else
            QMessageBox::critical(nullptr,QObject::tr("not ok"),
                                     QObject::tr("modification non effectue\n""click cancel to exit."),
                                     QMessageBox::Cancel);
    }

void maquette::on_pb_rechercher_clicked()
{
    QString rech =ui->le_CIN_rech->text();
        ui->tab_client->setModel(C.rechercher(rech));
}

void maquette::on_pb_tri_CIN_clicked()
{
    Client *C = new Client();
    ui->tab_client->setModel(C->tri_CIN());
}



void maquette::on_pb_tri_nom_clicked()
{
    Client *C = new Client();
    ui->tab_client->setModel(C->tri_nom());
}



void maquette::on_pb_tri_prenom_clicked()
{
    Client *C = new Client();
    ui->tab_client->setModel(C->tri_prenom());
}



void maquette::on_pb_tri_num_clicked()
{
    Client *C = new Client();
    ui->tab_client->setModel(C->tri_num());
}


void maquette::on_pb_imprimer_clicked()
{
    QPrinter printer;
    QPrintDialog dialog(&printer, this);
    dialog.setWindowTitle("Print Document");
    if(ui->textEdit->textCursor().hasSelection())
        dialog.addEnabledOption(QAbstractPrintDialog::PrintSelection);
    if(dialog.exec() != QDialog::Accepted)
    {
        return ;
    }
}

void maquette::on_qrcodegen_clicked()
{


    int tabeq=ui->tab_client_2->currentIndex().row();
              QVariant cinn=ui->tab_client_2->model()->data(ui->tab_client_2->model()->index(tabeq,0));
              QString CIN= cinn.toString();
              QSqlQuery qry;
              qry.prepare("select * from CLIENT where CIN=:CIN");
              qry.bindValue(":CIN",CIN);
              qry.exec();
                 QString  iden,NOM,PRENOM,NUMERO_TEL ,ide;

              while(qry.next()){

                  CIN=qry.value(1).toString();
                  NOM=qry.value(2).toString();
                  PRENOM=qry.value(3).toString();
                  NUMERO_TEL=qry.value(4).toString();


              }
              ide=QString(CIN);
                     ide="CIN:"+iden+"NOM:"+NOM+"PRENOM:"+PRENOM,"NUMTEL:"+NUMERO_TEL;
              QrCode qr = QrCode::encodeText(ide.toUtf8().constData(), QrCode::Ecc::HIGH);

              // Read the black & white pixels
              QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
              for (int y = 0; y < qr.getSize(); y++) {
                  for (int x = 0; x < qr.getSize(); x++) {
                      int color = qr.getModule(x, y);  // 0 for white, 1 for black

                      // You need to modify this part
                      if(color==0)
                          im.setPixel(x, y,qRgb(254, 254, 254));
                      else
                          im.setPixel(x, y,qRgb(0, 0, 0));
                  }
              }
              im=im.scaled(200,200);
              ui->qrcodecommande->setPixmap(QPixmap::fromImage(im));

   }

void maquette::on_pb_affichage_clicked()
{
    ui->tab_client_2->setModel(C.afficher());
}


void maquette::on_le_CIN_rech_textChanged(const QString &rech)
{

        ui->tab_client->setModel(C.rechercher(rech));
}


void maquette::on_tab_client_activated(const QModelIndex &index)
{
    ui->le_CIN->setText(ui->tab_client->model()->data(ui->tab_client->model()->index(index.row(),0)).toString());
    ui->le_nom->setText(ui->tab_client->model()->data(ui->tab_client->model()->index(index.row(),1)).toString());
    ui->le_prenom->setText(ui->tab_client->model()->data(ui->tab_client->model()->index(index.row(),2)).toString());
    ui->le_numTel->setText(ui->tab_client->model()->data(ui->tab_client->model()->index(index.row(),3)).toString());

}

void maquette::update_label()
{
    data = A.read_from_arduino();
    if (data == "1")
    {
        ui->etat_label->setText("Ouvert");
        QMessageBox::information (nullptr, QObject::tr("OK"),
                    QObject::tr("la voiture est entrée\n"
                                    "Click cancel to exist."), QMessageBox::Cancel);


    }else if (data == "0")
    {
        ui->etat_label->setText("Fermer");
        QMessageBox::information (nullptr, QObject::tr("OK"),
                    QObject::tr("Pas de voiture\n"
                                    "Click cancel to exist."), QMessageBox::Cancel);

    }


}

void maquette::on_pb_entrer_clicked()
{
    A.write_to_arduino("1");
}

