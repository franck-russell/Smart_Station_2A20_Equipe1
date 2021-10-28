#ifndef AVION_H
#define AVION_H
#include "avions.h"


#include <QDialog>

namespace Ui {
class avion;
}

class avion : public QDialog
{
    Q_OBJECT

public:
    explicit avion(QWidget *parent = nullptr);
    ~avion();

private slots:
    void on_pushButton_Ajouter_clicked();

    void on_pb_Ajouter_clicked();

private:
    Ui::avion *ui;
    Avions A;
};

#endif // AVION_H
