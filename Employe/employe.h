#ifndef EMPLOYE_H
#define EMPLOYE_H
#include<QString>
#include <QSqlQueryModel>

class Employee
{
public:
    Employee();
    Employee(QString a,QString b );
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    void setnom(QString n);
    void setprenom(QString n);
    void setcin(QString n);
    void setage(int n);
    void settache(QString n);
    QString get_cin();
    QString get_prenom();
    QString get_nom();
    int get_age();
    QString get_tache();

private:
     QString cin, prenom ,nom,tache;
     int age;
};
#endif // EMPLOYE_H
