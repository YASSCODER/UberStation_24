#include "maquette.h"
#include<iostream>
#include "ui_maquette.h"
#include"voiture.h"
#include<QMessageBox>
#include<QTextStream>
#include<QIntValidator>
#include"modifier.h"
using namespace std;
maquette::maquette(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::maquette)
{
    ui->setupUi(this);
    ui->tab_voiture->setModel(V.afficher());
}

maquette::~maquette()
{
    delete ui;
}

void maquette::on_PB_Ajout_clicked()
{
    QString matricule=ui->Matricule->text();
    QString marque=ui->Marque->text();
    QString genre=ui->Genre->text();
    QString hrE=ui->heure_E->text();
    QString hrS=ui->heure_S->text();
    Voiture V(matricule,marque,genre,hrE,hrS);
    bool test = V.ajouter();
           if (test)
           {
               ui->tab_voiture->setModel(V.afficher());

               QMessageBox::information (nullptr, QObject::tr("OK"),
                           QObject::tr("Ajout effectué\n"
                                           "Click cancel to exist."), QMessageBox::Cancel);
           }
           else
               QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                     QObject::tr("Ajout non effectué.\n"
                                                 "Click Cancel to exit."),QMessageBox::Cancel);
}

void maquette::on_PB_supp_clicked()
{
    Voiture V;
    QString MATRICULE=ui->M_supp->text();
    bool test=V.supprimer(MATRICULE);
            QMessageBox msgBox;
            if(test)
            {
                ui->tab_voiture->setModel(V.afficher());
                msgBox.setText("Suppression avec succes.");
            }


            else
                    msgBox.setText("echec de suppression.");
            msgBox.exec();
}


 void maquette::on_btn_edit_clicked()
{
    modifier W;
    W.show();
    W.exec();

}

void maquette::on_btn_afficher_clicked()
{
    ui->tab_voiture->setModel(V.afficher());
}

void maquette::on_btn_calculer_clicked()
{
    Voiture V;
    int nbr_v;
    nbr_v=V.calculer();
    ui->res_calc->display(nbr_v);
}


void maquette::on_btn_stat_clicked()
{

    QSqlQueryModel * model= new QSqlQueryModel();
                        model->setQuery("select * from VOITURE where HRE < 10 ");
                        float heure1=model->rowCount();
                        model->setQuery("select * from VOITURE where HRE  between 10 and 14 ");
                        float heure2=model->rowCount();
                        model->setQuery("select * from VOITURE where HRE >14 ");
                        float heure3=model->rowCount();
                        float total=heure1+heure2+heure3;
                        QString a=QString("moins de 10 hr "+QString::number((heure1*100)/total,'f',2)+"%" );
                        QString b=QString("entre 10 et 14 hr "+QString::number((heure2*100)/total,'f',2)+"%" );
                        QString c=QString("+14 hr "+QString::number((heure3*100)/total,'f',2)+"%" );
                        QPieSeries *series = new QPieSeries();
                        series->append(a,heure1);
                        series->append(b,heure2);
                        series->append(c,heure3);
                if (heure1!=0)
                {QPieSlice *slice = series->slices().at(0);
                 slice->setLabelVisible();
                 slice->setPen(QPen());}
                if ( heure2!=0)
                {
                         // Add label, explode and define brush for 2nd slice
                         QPieSlice *slice1 = series->slices().at(1);
                         //slice1->setExploded();
                         slice1->setLabelVisible();
                }
                if(heure3!=0)
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
                        chart->setTitle("Pourcentage Par heure :Nombre Des voiture "+ QString::number(total));
                        chart->legend()->hide();
                        // Used to display the chart
                        QChartView *chartView = new QChartView(chart);
                        chartView->setRenderHint(QPainter::Antialiasing);
                        chartView->resize(1000,500);
                        chartView->show();


}
