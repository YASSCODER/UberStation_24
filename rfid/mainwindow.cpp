#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
     //le slot update_label suite à la reception du signal readyRead (reception des données).
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_label()
{
    data=A.read_from_arduino();

    if(data=="1")
{
        ui->label_3->setText("acces autoriser"); // si les données reçues de arduino via la liaison série sont égales à 1
    // alors afficher ON


}
    else if (data=="0")
{
        ui->label_3->setText("acces non autoriser");
    // si les données reçues de arduino via la liaison série sont égales à 0
     //alors afficher ON
    A.write_to_arduino("2");

   }
    else if (data=="3")
{
        ui->label_3->setText("");
    // si les données reçues de arduino via la liaison série sont égales à 0
     //alors afficher ON

   }
   // A.write_to_arduino("5");

}
