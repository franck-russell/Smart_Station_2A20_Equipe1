#ifndef DIALOGA_H
#define DIALOGA_H
#include "avions.h"
#include "arduino.h"
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

    void on_pb_rechercher_clicked();

    void on_cb_modifier_currentIndexChanged(int index);

    void on_cb_suppression_activated(int index);

    void on_pb_tri_capacite_clicked();

    void on_pb_tri_etat_clicked();

    void on_pb_tri_type_clicked();

    void on_pb_pdf_clicked();

    void on_pp_docExel_clicked();

    void on_cb_trie_currentIndexChanged(int index);

    void on_le_recherche_avancee_textChanged();

    void on_pushButton_clicked();

    void on_pb_pageWeb_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::dialogA *ui;
    Avions A;
    QByteArray data;
    arduino O;
};

#endif // DIALOGA_H
