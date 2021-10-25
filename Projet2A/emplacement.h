#ifndef EMPLACEMENT_H
#define EMPLACEMENT_H


#include <QString>
#include <QSqlQueryModel>

class Emplacement
{
public:
    Emplacement();
    Emplacement (int, QString, int);
    int getid();
    QString getlocalisation();
    int getnb_max();
    void setid(int);
    void setlocalisation (QString);
    void setnb_max (int);
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer (int);


private:
    int id, nb_max;
    QString localisation;
};
#endif // EMPLACEMENT_H
