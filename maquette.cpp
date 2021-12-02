#include "mail.h"
#include "maquette.h"
#include "ui_maquette.h"
#include"accident.h"
#include<iostream>
#include <QObject>
#include<QSqlQuery>
#include<QMessageBox>
#include<QIntValidator>
#include <QPainter>
#include <QPdfWriter>
#include <QDesktopServices>
#include <QUrl>
#include <QFileDialog>
#include <QPrintDialog>
#include <QPrinter>
#include <QTextCursor>
#include <QLCDNumber>
#include <QImage>

using namespace std;
maquette::maquette(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::maquette)
{
    ui->setupUi(this);
    ui->tableView->setModel(A.afficher());

}

maquette::~maquette()
{
    delete ui;
}

void maquette::on_PB_Ajout_clicked()
{
    QString matricule=ui->matricule->text();
    QString chauffeur=ui->chauffeur->text();
    QString lieu=ui->lieu->text();
    QString fautif=ui->fautif->text();
    QString dat=ui->date->text();
    Accident A(matricule,chauffeur,lieu,fautif,dat);
    bool test = A.ajouter();
           if (test)
           {
               ui->tableView->setModel(A.afficher());

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
    Accident A;
    QString MATRICULE=ui->matricule_s->text();
    bool test=A.supprimer(MATRICULE);
            QMessageBox msgBox;

            if(test)
            {
                ui->tableView->setModel(A.afficher());
                msgBox.setText("Suppression avec succes.");
            }


            else
                    msgBox.setText("echec de suppression.");
            msgBox.exec();
}


void maquette::on_PB_modifier_clicked()
{

           QString matricule= ui->matricule->text();
           QString chauffeur= ui->chauffeur->text();
           QString lieu= ui->lieu->text();
           QString fautif= ui->fautif->text();
           QString dat= ui->date->text();
           Accident A1(matricule,chauffeur,lieu,fautif,dat);
           bool test=A1.modifier();
           if (test)
                    {
                            ui->tableView->setModel(A.afficher());
                        QMessageBox::information(nullptr,QObject::tr("OK"),
                                             QObject::tr("modification établie"),
                                             QMessageBox::Ok);}
                    else{
                    QMessageBox::critical(nullptr,QObject::tr("ERROR404"),
                                            QObject::tr("modification non établie"),
                                            QMessageBox::Cancel);}

}




void maquette::on_PDF_clicked()
{
QPrinter printer;
printer.setOutputFormat(QPrinter::PdfFormat);
printer.setOutputFileName("PDFaccidents.pdf");
     QPdfWriter pdf("C:/Users/Aziz/Desktop/classe_acc/PDFaccidents.pdf");
    QPainter painter(&pdf);
    QImage logo(":/logo/VVS.png");
painter.drawImage(50,50,logo);

                                int i = 4000;
                                  painter.setPen(Qt::red);
                                  painter.setFont(QFont("Arial", 30));
                                  painter.drawText(2300,1200,"Liste Des Accidents");
                                  painter.setPen(Qt::black);
                                  painter.setFont(QFont("Arial", 50));                                
                                  painter.drawRect(1500,200,7300,2600);
                                  painter.drawRect(0,3000,9600,500);
                                  painter.setFont(QFont("Arial", 9));
                                  painter.drawText(300,3300,"MATRICULE");
                                  painter.drawText(2300,3300,"CHAUFFEUR");
                                  painter.drawText(4300,3300,"LIEU");
                                  painter.drawText(6300,3300,"FAUTIF");
                                  painter.drawText(8300,3300,"DAT");




                                  QSqlQuery query;
                                  query.prepare("select * from ACCIDENT");
                                  query.exec();
                                  while (query.next())
                                  {
                                      painter.drawText(300,i,query.value(0).toString());
                                      painter.drawText(2300,i,query.value(1).toString());
                                      painter.drawText(4300,i,query.value(2).toString());
                                      painter.drawText(6300,i,query.value(3).toString());
                                      painter.drawText(8300,i,query.value(4).toString());



                                     i = i +500;
                                  }
                                  int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
                                      if (reponse == QMessageBox::Yes)
                                      {
                                          QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/Aziz/Desktop/classe_acc/PDFaccidents.pdf"));

                                          painter.end();
                                      }
                                      if (reponse == QMessageBox::No)
                                      {
                                           painter.end();
                                      }

}

void maquette::on_rechercher_clicked()
{
    QString matricule = ui->matricule_re->text();
     ui->tableView->setModel(A.afficher_matricule(matricule));
}

void maquette::on_imprimer_clicked()
{
    QPrinter rd;
        QPrintDialog d(&rd,this);
        d.setWindowTitle("Print Accident");
        d.addEnabledOption(QAbstractPrintDialog::PrintSelection);
        if (d.exec() != QDialog::Accepted)
            return ;

}
void maquette::on_calculer_clicked()
{
        ui->lcdNumber_calculer->display(A.calculernbacc());
}
/*
void maquette::on_browse_clicked()
{

        files.clear();

        QFileDialog dialog(this);
        dialog.setDirectory(QDir::homePath());
        dialog.setFileMode(QFileDialog::ExistingFiles);

        if (dialog.exec())
            files = dialog.selectedFiles();

        QString fileListString;
        foreach(QString file, files)
            fileListString.append( """ + QFileInfo(file).fileName() + "" " );

        ui->fichier->setText( fileListString );

}
void maquette::on_email_clicked()
{
    QString ch;

        ch=ui->rec->text();

       if(ch.contains("@", Qt::CaseInsensitive)==true)
        {mail* Mail = new mail ("medaziz.zalila@esprit.tn",ui->pass->text(), "smtp.gmail.com");
          connect(Mail, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

          if( !files.isEmpty() )
              Mail->sendMail("medaziz.zalila@esprit.tn", ui->rec->text() , ui->objet->text(),ui->msg->text(),files );
          else
              Mail->sendMail("medaziz.zalila@esprit.tn", ui->rec->text() , ui->objet->text(),ui->msg->text());
    }
       else
           QMessageBox::information(nullptr,QObject::tr("mail non envoyé"),
                                    QObject::tr("mail non envoyé. \n"
                                                "Click Cancel to exist."),QMessageBox::Cancel);
}

*/



