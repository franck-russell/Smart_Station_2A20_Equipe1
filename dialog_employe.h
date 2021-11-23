#ifndef DIALOG_EMPLOYE_H
#define DIALOG_EMPLOYE_H
#include "employe.h"
#include "chat.h"
#include <QDialog>
#include "chat1.h"

namespace Ui {
class Dialog_employe;
}

class Dialog_employe : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_employe(QWidget *parent = nullptr);
    ~Dialog_employe();

private slots:
    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_modifier_clicked();

    void on_pb_trim_clicked();

    void on_pb_tris_clicked();

    void on_pb_trip_clicked();

    void on_le_recherche_textChanged();

    void on_pb_pdf_clicked();

    void on_pb_chat_clicked();

    void on_pb_nettoyer_clicked();

    void on_cb_matricule_currentIndexChanged(int index);

private:
    Ui::Dialog_employe *ui;
    Employe Etmp;
    chat *c;
    chat1 *c1;
};

#endif // DIALOG_EMPLOYE_H
