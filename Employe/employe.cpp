#include "employe.h"
#include<QString>
#include<QSqlQuery>
#include<QtDebug>
#include<QObject>
Employee::Employee()
{
    cin="";
    prenom="";
    nom="";
    age=0;
    tache="";
}
bool Employee::ajouter()
{
bool test=false;
QSqlQuery query;
      query.prepare("INSERT INTO Employee (id, forename, surname) "
                    "VALUES (:id, :forename, :surname)");

      query.bindValue(":forename", nom);
      query.bindValue(":surname", prenom);
     return query.exec();
}
Employee::Employee(QString a,QString b )
{
    nom=a;
    prenom=b;
}
void Employee::setnom(QString n)
{
    nom = n;
}
void Employee::setprenom(QString n)
{
    prenom = n;
}
void Employee::setcin(QString n)
{
    cin = n;
}
void Employee::setage(int n)
{
    age = n;
}
void Employee::settache(QString n)
{
    tache = n;
}

QString Employee::get_nom()
{return nom;}

QString Employee::get_prenom()
{return prenom;}

QString Employee::get_cin()
{return cin;}

int Employee::get_age()
{return age;}

QString Employee::get_tache()
{return tache;}
QSqlQueryModel* afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

         model->setQuery("SELECT* FROM employee");
         model->setHeaderData(0, Qt::Horizontal, QObject("Name"));
         model->setHeaderData(1, Qt::Horizontal, QObject("Salary"));
    return model;
}
bool Employee::supprimer(int id)
{
    QSqlQueryModel* model=new QSqlQueryModel();

         model->setQuery("Delete from employee");
         model->setHeaderData(0, Qt::Horizontal, QObject("Name"));
         model->setHeaderData(1, Qt::Horizontal, QObject("Salary"));
    return model;
}
