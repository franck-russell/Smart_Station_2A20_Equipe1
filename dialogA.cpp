 #include "dialogA.h"
#include "ui_dialogA.h"
#include <QPixmap>
#include "avions.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QDebug>
#include <QSqlQuery>

dialogA::dialogA(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogA)
{
    ui->setupUi(this);
    ui->le_identifiant->setValidator(new QIntValidator(0, 999999, this));
    ui->le_capacite->setValidator(new QIntValidator(0, 99, this));
    ui->le_capacite_2->setValidator(new QIntValidator(0, 99, this));
    ui->le_rechercher->setValidator(new QIntValidator(0, 999999, this));
    ui->tab_afficher->setModel(A.afficher());
    ui->cb_suppression->setModel(A.afficher_ID());
    ui->cb_modifier->setModel(A.afficher_ID());
    //ui->cb_rechercher->setModel(A.afficher_ID());

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

 if(test)
 {QMessageBox::information(nullptr, QObject::tr("OK"),
             QObject::tr("Ajout avec succes\n"
                        "click Cancel to exist."), QMessageBox::Cancel);
     ui->tab_afficher->setModel(A.afficher());
     ui->cb_suppression->setModel(A.afficher_ID());
     ui->cb_modifier->setModel(A.afficher_ID());
     ui->cb_rechercher->setModel(A.afficher_ID());
 }
     else {
     QMessageBox::critical(nullptr, QObject::tr(" Not OK"),
                  QObject::tr("Ajout non effectué\n"
                             "click Cancel to exist."), QMessageBox::Cancel);
 }

     }


void dialogA::on_pb_supprimer_clicked()
{
    Avions A1; A1.setidentifiant(ui->cb_suppression->currentText().toInt());
    bool test=A1.supprimer(A1.getidentifiant());

    if(test)
    {QMessageBox::information(nullptr, QObject::tr("OK"),
                QObject::tr("Supprimé avec succes\n"
                           "click Cancel to exist."), QMessageBox::Cancel);
        ui->tab_afficher->setModel(A.afficher());
        ui->cb_suppression->setModel(A.afficher_ID());
        ui->cb_modifier->setModel(A.afficher_ID());
        ui->cb_rechercher->setModel(A.afficher_ID());

    }
        else {
        QMessageBox::critical(nullptr, QObject::tr(" Not OK"),
                     QObject::tr("Echec de suppression\n"
                                "click Cancel to exist."), QMessageBox::Cancel);
}
}
/*
void dialogA::on_pb_rechercher_clicked()
{
    Avions A1; A1.setidentifiant(ui->cb_rechercher->currentText().toInt());
    int identifiant=ui->cb_rechercher->currentText().toInt();
    ui->tab_afficher->setModel(A1.rechercher(identifiant));
   QString test=ui->cb_rechercher->test();
    if(test=="")
    {
        ui->tab_afficher->setModel(A.afficher());
    }

}*/
void dialogA::on_pb_rechercher_clicked()
{
    Avions A1; A1.setidentifiant(ui->le_rechercher->text().toInt());
    int identifiant=ui->le_rechercher->text().toInt();
    ui->tab_afficher->setModel(A1.rechercher(identifiant));
  /*  QString test=ui->le_rechercher->test();
    if(test=="")
    {
        ui->tab_afficher->setModel(A.afficher());
    }    */

}




void dialogA::on_pb_Afficher_clicked()
{
    ui->tab_afficher->setModel(A.afficher());
}



void dialogA::on_pushButton_modifier_2_clicked()
{
    int identifiant=ui->cb_modifier->currentText().toInt();
    int capacite=ui->le_capacite_2->text().toInt();
    QString type=ui->cb_type_2->currentText();
    QString etat=ui->cb_etat_2->currentText();
    //qDebug()<<capacite;

    Avions A(identifiant,capacite,type,etat);
    bool test=A.modifier();

    if(test)
    {QMessageBox::information(nullptr, QObject::tr("OK"),
                QObject::tr("Modification avec succes\n"
                           "click Cancel to exist."), QMessageBox::Cancel);
        ui->tab_afficher->setModel(A.afficher());
        ui->cb_rechercher->setModel(A.afficher_ID());
    }
        else {
        QMessageBox::critical(nullptr, QObject::tr(" Not OK"),
                     QObject::tr("Modification non effectué\n"
                                "click Cancel to exist."), QMessageBox::Cancel);
    }
}




void dialogA::on_cb_modifier_currentIndexChanged(int index)
{
    index=0;
    int identifiant=ui->cb_modifier->currentText().toInt();
    QSqlQuery query;
    query.prepare("select *from AVION where identifiant=:identifiant");
    query.bindValue(":identifiant",identifiant);
    ui->tab_afficher->setModel(A.afficher());
   // ui->cb_rechercher->setModel(A.afficher_ID());
   // ui->cb_suppression->setModel(A.afficher_ID());


    index++;
    if(query.exec())
    {
        while(query.next())
        {
            ui->le_capacite_2->setText(query.value(1).toString());
            ui->le_type_2->setText(query.value(2).toString());
            ui->le_etat_2->setText(query.value(3).toString());
            ui->tab_afficher->setModel(A.afficher());

        }
    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("Not OK"),
                              QObject::tr("Transfere de donnees non effectue.\n"
                                          "click cancel to exit."),QMessageBox::Cancel);
    }

}




void dialogA::on_cb_suppression_activated(int index)
{
    index ++;
    Avions A1; A1.setidentifiant(ui->cb_suppression->currentText().toInt());
    int identifiant=ui->cb_suppression->currentText().toInt();
    ui->tb_supprimer->setModel(A1.rechercher(identifiant));
}




void dialogA::on_pb_tri_capacite_clicked()
{
    Avions A1;
    ui->tab_afficher->setModel(A1.tri_capacite());
}


void dialogA::on_pb_tri_etat_clicked()
{
    Avions A1;
    ui->tab_afficher->setModel(A1.tri_etat());
}


void dialogA::on_pb_tri_type_clicked()
{
    Avions A1;
    ui->tab_afficher->setModel(A1.tri_type());
}

