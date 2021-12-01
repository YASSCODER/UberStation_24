#include "maquette.h"
#include "ui_maquette.h"
#include "emplacement.h"
#include <QMessageBox>
#include <QObject>
#include <QSqlQueryModel>
#include <QIntValidator>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QVBoxLayout>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QPixmap>
#include <iostream>


using namespace std;


maquette::maquette(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::maquette)
{

    ui->setupUi(this);

    //Localisation


    //Buttons




    ui->le_nb_max->setValidator(new QIntValidator(2, 999999, this));
    ui->le_prix->setValidator(new QIntValidator(3, 999999, this));

    ui->tab_emplacement->setModel(E.afficher());
    ui->le_id->setValidator(new QIntValidator(0, 999999, this));


    //stat
     //E.statistique()->setParent(ui->horizontalFrame);

     //Camera
     mCamera = new QCamera (this);
     mCameraViewfinder = new QCameraViewfinder(this);
     mCameraImageCapture = new QCameraImageCapture(mCamera, this);
     mLayout = new QVBoxLayout;
     mOptionMenu = new QMenu ("Option", this);
     mTurnOnAction = new QAction ("Turn on", this);
     mTurnOffAction = new QAction ("Turn off", this);
     mCaptureAction = new QAction ("Capture", this);

     mOptionMenu->addActions({mTurnOnAction, mTurnOffAction, mCaptureAction});
     ui->pb_option->setMenu(mOptionMenu);
     mCamera->setViewfinder(mCameraViewfinder);
     mLayout->addWidget(mCameraViewfinder);
     mLayout->setMargin(0);
     ui->scrollArea->setLayout(mLayout);
     connect (mTurnOnAction, &QAction::triggered, [&]()
     {
        mCamera->start();
     });
     connect (mTurnOffAction, &QAction::triggered, [&]()
     {
         mCamera->stop();
     });
     connect (mCaptureAction, &QAction::triggered, [&]()
     {
         auto filename=QFileDialog::getSaveFileName(this, "capture", "/", "Image (*.jpg; *.jpeg)");

         if (filename.isEmpty())
         {
             return;
         }
         mCameraImageCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
         QImageEncoderSettings imageEncoderSettings;
         imageEncoderSettings.setCodec("image/jpeg");
         imageEncoderSettings.setResolution(1600,1200);
         mCameraImageCapture->setEncodingSettings(imageEncoderSettings);
         mCamera->setCaptureMode(QCamera::CaptureStillImage);
         mCamera->start();
         mCamera->searchAndLock();
         mCameraImageCapture->capture(filename);
         mCamera->unlock();
     });

}

maquette::~maquette()
{
    delete ui;
}

void maquette::on_pb_ajouter_clicked()
{
       int id = ui->le_id->text().toInt();
       QString localisation = ui->le_localisation->text();
       int nb_max = ui->le_nb_max->text().toInt();
       float prix = ui->le_prix->text().toInt();
       Emplacement E(id, localisation, nb_max, prix);

       if (id == 0)
       {
           QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                 QObject::tr("ID vide .\n"
                                             "Click Cancel to exist."),QMessageBox::Cancel);
       }
       else if (nb_max == 0)
       {
           QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                 QObject::tr("nombre maximale vide .\n"
                                             "Click Cancel to exist."),QMessageBox::Cancel);
       }
       else if (prix == 0)
       {
           QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                 QObject::tr("prix vide .\n"
                                             "Click Cancel to exist."),QMessageBox::Cancel);
       }
       else if (localisation == NULL)
       {
           QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                 QObject::tr("localisation vide .\n"
                                             "Click Cancel to exist."),QMessageBox::Cancel);
       }
       else
       {
           bool test = E.ajouter();
           if (test)
           {

               //Refresh
               ui->tab_emplacement->setModel(E.afficher());


               QMessageBox::information (nullptr, QObject::tr("OK"),
                           QObject::tr("Ajout effectué\n"
                                           "Click cancel to exist."), QMessageBox::Cancel);
           }
           else
               QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                     QObject::tr("Ajout non effectué.\n"
                                                 "Click Cancel to exist."),QMessageBox::Cancel);
       }

}

void maquette::on_pb_supprimer_clicked()
{
    //int id = ui->le_id_supp->text().toUInt();
    QString p = ui->sup->currentText();
    int id = p.toInt();
    if (id == 0)
    {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("ID vide .\n"
                                          "Click Cancel to exist."),QMessageBox::Cancel);
    }
    else
    {

        bool test = E.supprimer(id);
        if (test)
        {
            //Refresh
            ui->tab_emplacement->setModel(E.afficher());

            QMessageBox::information (nullptr, QObject::tr("OK"),
                        QObject::tr("Suppression effectué\n"
                                        "Click cancel to exist."), QMessageBox::Cancel);
        }
        else
            {
                QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                  QObject::tr("Suppression non effectué.\n"
                                              "Click Cancel to exist."),QMessageBox::Cancel);
        }
    }



}


void maquette::on_pb_modifier_clicked()
{
    int id = ui->le_id->text().toInt();
    QString localisation = ui->le_localisation->text();
    int nb_max = ui->le_nb_max->text().toInt();
    float prix = ui->le_prix->text().toInt();

    if (id == 0)
    {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("ID vide .\n"
                                          "Click Cancel to exist."),QMessageBox::Cancel);
    }
    else if (nb_max == 0)
    {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("nombre maximale vide .\n"
                                          "Click Cancel to exist."),QMessageBox::Cancel);
    }
    else if (prix == 0)
    {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("prix vide .\n"
                                          "Click Cancel to exist."),QMessageBox::Cancel);
    }
    else if (localisation == NULL)
    {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("localisation vide .\n"
                                          "Click Cancel to exist."),QMessageBox::Cancel);
    }
    else
    {
        bool test = E.modifier(id,localisation,nb_max, prix);
        if (test)
        {

            //Refresh
            ui->tab_emplacement->setModel(E.afficher());

            QMessageBox::information (nullptr, QObject::tr("OK"),
                        QObject::tr("modification effectué\n"
                                        "Click cancel to exist."), QMessageBox::Cancel);


        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                  QObject::tr("modification non effectué.\n"
                                              "Click Cancel to exist."),QMessageBox::Cancel);
        }}




}

void maquette::on_pb_afficher_clicked()
{

    bool test = E.afficher();
    if (test)
    {
        //Refresh
        ui->tab_emplacement->setModel(E.afficher());

        QMessageBox::information (nullptr, QObject::tr("OK"),
                    QObject::tr("affichage effectué\n"
                                    "Click cancel to exist."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("affichage non effectué.\n"
                                          "Click Cancel to exist."),QMessageBox::Cancel);
}

void maquette::on_pb_id_afficher_clicked()
{
    ui->sup->setModel(E.afficher());
}


void maquette::on_pb_calculer_clicked()
{

    ui->res_calculer->display(E.calculerBudget());

}

void maquette::on_pb_stat_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from EMPLACEMENT where PRIX < 100 ");
    float prix=model->rowCount();
    model->setQuery("select * from EMPLACEMENT where PRIX  between 100 and 200 ");
    float prix1=model->rowCount();
    model->setQuery("select * from EMPLACEMENT where PRIX>200 ");
    float prix2=model->rowCount();
    float total=prix+prix1+prix2;
    QString a = QString("moins de 100 DT  "+QString::number((prix*100)/total,'f',2)+"%" );
    QString b = QString("entre 100 et 200 DT "+QString::number((prix1*100)/total,'f',2)+"%" );
    QString c = QString("+200 DT "+QString::number((prix2*100)/total,'f',2)+"%" );
    QPieSeries *series = new QPieSeries();
    series->append(a,prix);
    series->append(b,prix1);
    series->append(c,prix2);
    if (prix!= 0)
    {
        QPieSlice *slice = series->slices().at(0);
        slice->setLabelVisible();
        slice->setPen(QPen());
    }
    if ( prix1!=0)
    {
             // Add label, explode and define brush for 2nd slice
             QPieSlice *slice1 = series->slices().at(1);
             //slice1->setExploded();
             slice1->setLabelVisible();
    }
    if(prix2!=0)
    {
             // Add labels to rest of slices
             QPieSlice *slice2 = series->slices().at(2);
             //slice1->setExploded();
             slice2->setLabelVisible();
    }
            // Create the chart widget
            QChart *chart = new QChart();
            // Add data to chart with title and hide legend
            chart->addSeries(series);
            chart->setTitle("Pourcentage Par PRIX :Nombre Des EMPLACEMENT "+ QString::number(total));
            chart->legend()->hide();
            // Used to display the chart
            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);
            chartView->resize(1000,500);
            chartView->show();
}

void maquette::on_pb_triLocalisation_clicked()
{
    Emplacement *E = new Emplacement();
       ui->tab_emplacement->setModel(E->triLocalisation());
}

void maquette::on_pb_triId_clicked()
{
    Emplacement *E = new Emplacement();
       ui->tab_emplacement->setModel(E->triId());
}

void maquette::on_pb_triNbMax_clicked()
{
    Emplacement *E = new Emplacement();
       ui->tab_emplacement->setModel(E->triNb_max());
}

void maquette::on_pb_triPrix_clicked()
{
    Emplacement *E = new Emplacement();
       ui->tab_emplacement->setModel(E->triPrix());
}



void maquette::on_pb_localisation_afficher_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT LOCALISATION FROM EMPLACEMENT");

    ui->Localisation_combobox->setModel(model);
}

void maquette::on_pb_localisation_clicked()
{
    QString p=ui->Localisation_combobox->currentText();
    QDesktopServices::openUrl(QUrl("http://maps.google.com.sg/maps?q="+p+"&oe=utf-8&rls=org.mozilla:en-US:official&client=firefox-a&um=1&ie=UTF-8&hl=en&sa=N&tab=wl"));
}



void maquette::on_tab_emplacement_activated(const QModelIndex &index)
{
    ui->le_id->setText(ui->tab_emplacement->model()->data(ui->tab_emplacement->model()->index(index.row(),0)).toString());

    ui->le_localisation->setText(ui->tab_emplacement->model()->data(ui->tab_emplacement->model()->index(index.row(),1)).toString());
    ui->le_nb_max->setText(ui->tab_emplacement->model()->data(ui->tab_emplacement->model()->index(index.row(),2)).toString());
    ui->le_prix->setText(ui->tab_emplacement->model()->data(ui->tab_emplacement->model()->index(index.row(),3)).toString());
}
