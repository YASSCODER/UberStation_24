#ifndef MAQUETTE_H
#define MAQUETTE_H

#include <QDialog>
#include<voiture.h>
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

    void on_btn_afficher_clicked();

    void on_btn_edit_clicked();

    void on_btn_option_clicked();

private:
    Ui::maquette *ui;
    Voiture V;
};

#endif // MAQUETTE_H
