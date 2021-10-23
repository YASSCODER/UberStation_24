#ifndef GARAGE_H
#define GARAGE_H

#include <QDialog>

namespace Ui {
class Garage;
}

class Garage : public QDialog
{
    Q_OBJECT

public:
    explicit Garage(QWidget *parent = nullptr);
    ~Garage();

private:
    Ui::Garage *ui;
};

#endif // GARAGE_H
