#ifndef MAQUETTE_AHMED_H
#define MAQUETTE_AHMED_H

#include <QDialog>
#include<QMainWindow>
#include<QPrinter>
#include<QPrintDialog>
#include"QMessageBox"
#include"employes.h"
#include <QTcpSocket>
#include<QTimer>
namespace Ui {
class QTcpSocket;
class maquette_ahmed;
}

class maquette_ahmed : public QDialog
{
    Q_OBJECT

public:
    explicit maquette_ahmed(QWidget *parent = nullptr);
    ~maquette_ahmed();

private slots:
    void on_bt_ajouter_clicked();
    void myfunction();


    void on_bt_supprimer_clicked();



    void on_pushButton_modifier_clicked();

    void on_pushButton_imprimer_clicked();

    void on_tab_employes_clicked(const QModelIndex &index);

    void on_pushButton_impression_clicked();

    void on_pushButton_stat_clicked();

    void on_pushButton_tri_croissant_clicked();

    void on_pushButton_tri_decroissant_clicked();

    void on_lineEdit_recherche_textChanged(const QString &arg1);

    void on_pushButton_calcul_clicked();

    void on_QrCode_clicked();

    void on_pb_connecter_clicked();

    void on_pb_envoyer_clicked();

private:
    Ui::maquette_ahmed *ui;
    employes Etmp;
    QTcpSocket *mSocket;
     QTimer *timer;
};

#endif // MAQUETTE_AHMED_H
