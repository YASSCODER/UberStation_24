#include "client.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>


Client::Client()
{
CIN_C=" ";
Nom=" ";
Prenom=" ";
NumeroTel= " ";
Mail= " ";
}

Client::Client(QString CIN_C,QString Nom,QString Prenom,QString NumeroTel,QString Mail)
{this->CIN_C=CIN_C;
  this->Nom=Nom;
    this->Prenom=Prenom;
    this->NumeroTel=NumeroTel;
    this->Mail=Mail;
}

QString Client::getCIN_C(){return CIN_C;}
QString Client::getNom(){return Nom;}
QString Client::getPrenom(){return Prenom;}
QString Client::getNumeroTel(){return NumeroTel;}
QString Client::getMail(){return Mail;}
void Client::setCIN_C(QString CIN_C){this->CIN_C=CIN_C;}
void Client::setNom(QString Nom){this->Nom=Nom;}
void Client::setPrenom(QString Prenom){this->Prenom=Prenom;}
void Client::setNumeroTel(QString NumeroTel){this->NumeroTel=NumeroTel;}
void Client::setMail(QString Mail){this->Mail=Mail;}
bool Client::ajouter()
{
    QSqlQuery query;
         query.prepare("INSERT INTO Client (CIN_C, Nom, Prenom, NumeroTel, Mail) "
                       "VALUES (:CIN_C, :Nom, :Prenom, :NumeroTel, :Mail)");
         query.bindValue(0, CIN_C);
         query.bindValue(1, Nom);
         query.bindValue(2, Prenom);
         query.bindValue(3, NumeroTel);
         query.bindValue(4, Mail);
         return query.exec();
}
bool Client::supprimer(QString CIN_C)
{
    QSqlQuery query;
         query.prepare("Delete from client where CIN_C=:CIN_C");
         query.bindValue(0, CIN_C);

         return query.exec();


}
QSqlQueryModel* Client::afficher()
{
  QSqlQueryModel* model= new QSqlQueryModel();

        model->setQuery("SELECT* FROM client");
        model->setHeaderData(0, Qt::Horizontal,QObject::tr("CIN_C"));
        model->setHeaderData(1, Qt::Horizontal,QObject::tr("Nom"));
        model->setHeaderData(2, Qt::Horizontal,QObject::tr("Prenom"));
        model->setHeaderData(3, Qt::Horizontal,QObject::tr("NumeroTel"));
        model->setHeaderData(4, Qt::Horizontal,QObject::tr("Mail"));




 return model;
}
