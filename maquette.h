#ifndef MAQUETTE_H
#define MAQUETTE_H

#include <QDialog>
#include<accident.h>
#include <QPrintDialog>
#include <QPrinter>
#include <QLCDNumber>
namespace Ui {
class maquette;
}

class maquette : public QDialog
{
    Q_OBJECT

public:
    explicit maquette(QWidget *parent = nullptr);
    ~maquette();

private slots:
    void on_PB_Ajout_clicked();
    void on_PB_supp_clicked();
    //void on_btn_afficher_clicked();
    void on_PB_modifier_clicked();

    void on_PDF_clicked();

    void on_rechercher_clicked();

    void on_email_clicked();

    void on_browse_clicked();

    void on_imprimer_clicked();

    void on_calculer_clicked();

private:
    Ui::maquette *ui;
    Accident A;
     QStringList files;
};

#endif // MAQUETTE_H
