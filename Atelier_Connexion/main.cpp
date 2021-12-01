#include "maquette_ahmed.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include"employes.h"
#include"login.h"
#include <QCoreApplication>
#include"chatserver.h"
using namespace ApexAlliance;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Connection c;
    login l;
   // bool test_login;

    bool test=c.createconnect();
   // l.show();
   // test_login=l.on_pushButton_login_clicked();
    maquette_ahmed w;
   // if(test_login)
    //{
        //l.hide();
    ChatServer Server;
    if(!Server.startServer(3333)){
        qDebug()<<"Error:"<<Server.errorString();
        //return 1;

    }
    qDebug()<<"Server   started ...";

    if(test)
    {l.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


//}
    return a.exec();
}
