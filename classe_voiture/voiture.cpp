#include "voiture.h"
#include<QDebug>
#include<QSqlQuery>
#include<QObject>

Voiture::Voiture()
{
    matricule=" ";
    marque=" ";
    genre=" ";
    hrE=0;
    hrS=0;
}
Voiture::Voiture(QString matricule,QString marque,QString genre,int HE, int HS)
{
  this->matricule=matricule;
    this->marque=marque;
    this->genre=genre;
    this->hrE=HE;
    this->hrS=HS;
}
QString Voiture::getMatricule()
{
    return matricule;
}
QString Voiture::getMarque()
{
    return marque;
}
QString Voiture::getGenre()
{
    return genre;
}
int Voiture::getHE()
{
    return hrE;
}
int Voiture::getHS()
{
    return hrS;
}
void Voiture::setmatricule(QString matricule)
{
    this->matricule=matricule;
}
void Voiture::setmarque(QString marque)
{
    this->marque=marque;
}
void Voiture::setgenre(QString genre)
{
    this->genre=genre;
}
void Voiture::sethe(int he)
{
    this->hrE=he;
}
void Voiture::seths(int hs)
{
    this->hrS=hs;
}
bool Voiture::ajouter()
{
    bool test=false;

      QSqlQuery query;
      QString hrE_string = QString:: number(hrE);
      QString hrS_string = QString:: number(hrS);

      query.prepare("INSERT INTO voiture (matricule, marque, genre, heE, hrS) "
                    "VALUES (:matricule, :marque, :genre, :hrE, :heS)");
      query.bindValue(":matricule", matricule);
      query.bindValue(":marque", marque);
      query.bindValue(":genre", genre);
      query.bindValue(":hrE", hrE);
      query.bindValue(":hrS", hrS);
      query.exec();

    return test;
}
QSqlQueryModel* Voiture::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel;

          model->setQuery("SELECT * FROM voiture");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("matricule"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("marque"));
           model->setHeaderData(2, Qt::Horizontal, QObject::tr("genre"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("hrE"));
             model->setHeaderData(4, Qt::Horizontal, QObject::tr("hrS"));

    return model;
}

bool Voiture::supprimer(QString matricule)
{
    QSqlQuery query;

        query.prepare("Delete from voiture where matricule = :matricule");

        query.bindValue(":matricule", matricule);
        return query.exec();
}
