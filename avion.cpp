#include "avion.h"
#include "ui_avion.h"
#include <QPixmap>
#include "avions.h"
avion::avion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::avion)
{
    ui->setupUi(this);
    ui->tab_afficher->setModel(A.afficher());

}

avion::~avion()
{
    delete ui;
}


void avion::on_pb_Ajouter_clicked()
{
 int id=ui->le_id->text().toInt();
 int capacite=ui->le_capacite->text().toInt();
 QString type=ui->cb_type->text();
 QString etat=ui->cb_etat->text();
 Avions A(id,capacite,type,etat);

}

