#ifndef DIALOGA_H
#define DIALOGA_H
#include "avions.h"
#include <QDialog>
#include <QVariant>

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

    void on_tab_afficher_activated(const QModelIndex &index);

    //void on_pb_modifier_clicked();

    void on_pb_rechercher_clicked();

    //void on_cb_modifier_currentIndexChanged(int index)

    void on_cb_modifier_currentIndexChanged(int index);

    void on_cb_suppression_activated(const QString &arg1);

    void on_cb_suppression_activated(int index);

    void on_pb_trier_clicked();

    void on_comboBox_trier_activated(const QString &arg1);

    void on_comboBox_trier_activated(int index);

    void on_cb_tri_activated(const QString &arg1);

    void on_pb_tri_capacite_clicked();

    void on_pb_tri_etat_clicked();

    void on_pb_tri_type_clicked();

    void on_pb_pdf_clicked();

private:
    Ui::dialogA *ui;
    Avions A;
    void setCenter(QVariant, QVariant);
};

#endif // DIALOGA_H
