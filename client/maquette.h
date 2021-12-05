#ifndef MAQUETTE_H
#define MAQUETTE_H

#include <QDialog>
#include "client.h"
#include <QPrinter>
#include <QPrintDialog>
#include "Arduino.h"


namespace Ui {
class maquette;
}

class QSystemTrayIcon;

class maquette : public QDialog
{
    Q_OBJECT

public:
    explicit maquette(QWidget *parent = nullptr);
    ~maquette();

private slots:
    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_modifier_clicked();

    void on_pb_rechercher_clicked();

    void on_pb_afficher_clicked();



    void on_CIN_aff_clicked();

    void on_pb_imprimer_clicked();

    void on_qrcodegen_clicked();

    void on_pb_affichage_clicked();

    void on_le_CIN_rech_textChanged(const QString &rech);





    void on_pb_tri_CIN_clicked();

    void on_pb_tri_nom_clicked();

    void on_pb_tri_prenom_clicked();

    void on_pb_tri_num_clicked();

    void on_tab_client_activated(const QModelIndex &index);
    void update_label();
    void on_pb_entrer_clicked();

private:
    Ui::maquette *ui;
    Client C;
    Arduino A;
    QByteArray data;



};

#endif // MAQUETTE_H
