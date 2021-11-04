#include "dialogA.h"
#include "ui_dialogA.h"
#include <QPixmap>
#include "avions.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QDebug>

dialogA::dialogA(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogA)
{
    ui->setupUi(this);
  //  ui->le_identifiant->setValidator(new QIntValidator(0, 99999999, this));
    ui->tab_afficher->setModel(A.afficher());

}

dialogA::~dialogA()
{
    delete ui;
}


void dialogA::on_pb_Ajouter_clicked()
{
 int identifiant=ui->le_identifiant->text().toInt();
 int capacite=ui->le_capacite->text().toInt();
 QString type=ui->cb_type->currentText();
 QString etat=ui->cb_etat->currentText();
 Avions A(identifiant,capacite,type,etat);
 bool test=A.ajouter();
 //QMessageBox msgBox;

 /*if(test)
 {
     msgBox.setText("Ajout avec succes.");
 ui->tab_afficher->setModel(A.afficher());
 }
 else{
     msgBox.setText("Echec d'ajout");
     msgBox.exec();
}}
*/
 if(test)
 {QMessageBox::information(nullptr, QObject::tr("OK"),
             QObject::tr("Ajout avec succes\n"
                        "click Cancel to exist."), QMessageBox::Cancel);
     ui->tab_afficher->setModel(A.afficher());
 }
     else {
     QMessageBox::critical(nullptr, QObject::tr(" Not OK"),
                  QObject::tr("Ajout non effectué\n"
                             "click Cancel to exist."), QMessageBox::Cancel);
 }

     }


void dialogA::on_pb_supprimer_clicked()
{
    Avions A1; A1.setidentifiant(ui->le_suppression->text().toInt());
    bool test=A1.supprimer(A1.getidentifiant());
    //QMessageBox msgBox;

 /*   if(test)
    {msgBox.setText("Supprimer avec succes.");
    ui->tab_afficher->setModel(A.afficher());
    }
    else
        msgBox.setText("Echec de suppression.");
        msgBox.exec();*/
    if(test)
    {QMessageBox::information(nullptr, QObject::tr("OK"),
                QObject::tr("Supprimé avec succes\n"
                           "click Cancel to exist."), QMessageBox::Cancel);
        ui->tab_afficher->setModel(A.afficher());
    }
        else {
        QMessageBox::critical(nullptr, QObject::tr(" Not OK"),
                     QObject::tr("Echec de suppression\n"
                                "click Cancel to exist."), QMessageBox::Cancel);
}
}

void dialogA::on_pushButton_modifier_2_clicked()
{

}


void dialogA::on_pb_Afficher_clicked()
{

}

