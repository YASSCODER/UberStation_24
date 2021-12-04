#ifndef MAQUETTE_H
#define MAQUETTE_H

#include <QMainWindow>
#include "emplacement.h"
#include "arduino.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>





namespace Ui {
class maquette;
}

class QCamera;
class QCameraViewfinder;
class QCameraImageCapture;
class QVBoxLayout;
class  QMenu;
class QAction;
class QMapControl;

class maquette : public QMainWindow
{
    Q_OBJECT

public:
    explicit maquette(QWidget *parent = nullptr);
    ~maquette();


private slots:
    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_modifier_clicked();

    void on_pb_afficher_clicked();

    void on_pb_id_afficher_clicked();

    void on_pb_calculer_clicked();

    void on_pb_stat_clicked();

    void on_pb_triLocalisation_clicked();

    void on_pb_triId_clicked();

    void on_pb_triNbMax_clicked();

    void on_pb_triPrix_clicked();


    void on_pb_localisation_clicked();

    void on_pb_localisation_afficher_clicked();



    void on_tab_emplacement_activated(const QModelIndex &index);



    void update_label();

    void on_pb_entrer_clicked();





private:
    Emplacement E;
    Ui::maquette *ui;
    QCamera *mCamera;
    QCameraViewfinder *mCameraViewfinder;
    QCameraImageCapture *mCameraImageCapture;
    QVBoxLayout *mLayout;
    QMenu *mOptionMenu;
    QAction *mTurnOnAction;
    QAction *mTurnOffAction;
    QAction *mCaptureAction;

    QByteArray data;
    Arduino A;


};

#endif // MAQUETTE_H
