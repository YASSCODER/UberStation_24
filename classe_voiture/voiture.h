#ifndef VOITURE_H
#define VOITURE_H
#include<QString>
#include <QSqlQueryModel>
class Voiture
{
private:
    QString matricule, marque, genre;
    int hrE, hrS;
public:
    Voiture();
    Voiture(QString,QString,QString,int,int);
    //getters
    QString getMatricule();
    QString getMarque();
    QString getGenre();
    int getHE();
    int getHS();
    //setters
    void setmatricule(QString);
    void setmarque(QString);
    void setgenre(QString);
    void sethe(int);
    void seths(int);
    bool ajouter();
    bool supprimer(QString);
    QSqlQueryModel* afficher();
};

#endif // VOITURE_H
