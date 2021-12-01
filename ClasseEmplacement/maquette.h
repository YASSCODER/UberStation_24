#ifndef MAQUETTE_H
#define MAQUETTE_H

#include <QMainWindow>
#include "emplacement.h"

namespace Ui {
class maquette;
}

class maquette : public QMainWindow
{
    Q_OBJECT

public:
    explicit maquette(QWidget *parent = nullptr);
    ~maquette();

private slots:
    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

private:
    Emplacement E;
    Ui::maquette *ui;
};

#endif // MAQUETTE_H
