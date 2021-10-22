#ifndef VOITURE_H
#define VOITURE_H

#include <QDialog>

namespace Ui {
class voiture;
}

class voiture : public QDialog
{
    Q_OBJECT

public:
    explicit voiture(QWidget *parent = nullptr);
    ~voiture();

private:
    Ui::voiture *ui;
};

#endif // VOITURE_H
