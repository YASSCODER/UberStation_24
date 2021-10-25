#include "emplacement.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>

Emplacement::Emplacement()
{
    id = 0 ;
    localisation = " ";
    nb_max = 0;
}

Emplacement::Emplacement (int id, QString localisation, int nb_max)
{
    this->id = id;
    this->localisation = localisation;
    this->nb_max = nb_max;
}

int Emplacement::getid(){return id;}
QString Emplacement::getlocalisation(){return localisation;}
int Emplacement::getnb_max(){return nb_max;}
void Emplacement::setid(int id){this->id = id;}
void Emplacement::setlocalisation (QString localisation){this->localisation = localisation;}
void Emplacement::setnb_max (int nb_max){this->nb_max = nb_max;}
bool Emplacement::ajouter()
{

    QSqlQuery query;
    QString id_string = QString:: number(id);
    QString nb_max_string = QString:: number(nb_max);
        query.prepare("INSERT INTO emplacement (id, localisation, nb_max) "
                      "VALUES (:id, :localisation, :nb_max)");
        query.bindValue(":id", id_string);
        query.bindValue(":localisation", localisation);
        query.bindValue(":nb_max", nb_max_string);
        return query.exec();


}

bool Emplacement::supprimer(int id)
{
    QSqlQuery query;
    QString id_string = QString:: number(id);

        query.prepare("Delete from emplacement where ID = :id");

        query.bindValue(":id", id_string);
        return query.exec();
}

QSqlQueryModel* Emplacement::afficher()
{

    QSqlQueryModel *model = new QSqlQueryModel;
       model->setQuery("SELECT * FROM emplacement");
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("Localisation"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nombre maximale"));

       return model;
}
