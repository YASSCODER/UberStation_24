#ifndef MAQUETTE_H
#define MAQUETTE_H

#include <QDialog>
#include "client.h"
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
    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

private:
    Ui::maquette *ui;
    Client C;

};

#endif // MAQUETTE_H
