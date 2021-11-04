#ifndef DIALOGA_H
#define DIALOGA_H
#include "avions.h"
#include <QDialog>

namespace Ui {class dialogA;}

class dialogA : public QDialog
{
    Q_OBJECT

public:
    explicit dialogA(QWidget *parent = nullptr);
    ~dialogA();

private slots:
    void on_pb_Ajouter_clicked();

    void on_pb_Afficher_clicked();

    void on_pb_supprimer_clicked();

    void on_pushButton_modifier_2_clicked();

private:
    Ui::dialogA *ui;
    Avions A;
};

#endif // DIALOGA_H
