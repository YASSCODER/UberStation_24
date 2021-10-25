#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QSqlQueryModel>
class Client
{
public:
    Client();
    Client(QString,QString,QString,QString,QString);
    QString getCIN_C();
    QString getNom();
    QString getPrenom();
    QString getNumeroTel();
    QString getMail();
    void setCIN_C(QString);
    void setNom(QString);
    void setPrenom(QString);
    void setNumeroTel(QString);
    void setMail(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(QString);
private:
 QString CIN_C,Nom,Prenom,NumeroTel,Mail;


};

#endif // CLIENT_H
