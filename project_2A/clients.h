#ifndef CLIENTS_H
#define CLIENTS_H

#include <QDialog>

namespace Ui {
class clients;
}

class clients : public QDialog
{
    Q_OBJECT

public:
    explicit clients(QWidget *parent = nullptr);
    ~clients();

private:
    Ui::clients *ui;
};

#endif // CLIENTS_H
