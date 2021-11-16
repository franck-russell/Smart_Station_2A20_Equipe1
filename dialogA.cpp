 #include "dialogA.h"
#include "ui_dialogA.h"
#include <QPixmap>
#include "avions.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QDebug>
#include <QSqlQuery>
#include <QQuickItem>
#include <QDialog>
#include <QPainter>
#include <QPdfWriter>
#include <QDesktopServices>
#include <QUrl>

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
    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
    ui->quickWidget->show();

    auto obj = ui->quickWidget->rootObject();
    connect(this,SIGNAL(setCenter(QVariant,QVariant)),obj,SLOT(setCenter(QVarfant,QVariant)));
    //emit setCenter(25.000, 50.000);

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


void dialogA::on_pb_pdf_clicked()
{
        QPdfWriter pdf("D:/Esprit/2eme année/semestre 1/projet cpp/avion.pdf");

          QPainter painter(&pdf);

          int i = 4000;
          painter.setPen(Qt::red);
          painter.setFont(QFont("Arial", 30));
          painter.drawPixmap(QRect(200,200,2000,2000),QPixmap("D:/Esprit/2eme année/semestre 1/projet cpp/logo/logo4.png"));
          painter.drawPixmap(QRect(800,800,10000,2000),QPixmap("D:/Esprit/2eme année/semestre 1/projet cpp/logo/esprit.png"));
          painter.drawText(3000,1500,"INFORMATIONS SUR LES AVIONS");
          painter.setPen(Qt::black);
          painter.setFont(QFont("Arial", 50));
          // painter.drawText(1100,2000,afficheDC);
          painter.drawRect(2700,200,7300,2600);
          //painter.drawRect(1500,200,7300,2600);
          //painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/RH/Desktop/projecpp/image/logopdf.png"));
          painter.drawRect(0,3000,9600,500);
          painter.setFont(QFont("Arial", 9));
          painter.drawText(300,3300,"IDENTIFIANT");
          painter.drawText(2300,3300,"CAPACITE");
          painter.drawText(4300,3300,"TYPE");
          painter.drawText(6300,3300,"ETAT");/*
          painter.drawText(8000,3300,"SEXE");
          painter.drawText(10300,3300,"NATIONALITE");
          painter.drawText(12300,3300,"SPECIALITE");
          painter.drawText(14300,3300,"MAIL");*/
          QSqlQuery query;
          query.prepare("select * from AVION");
          query.exec();
          while (query.next())
          {
              painter.drawText(300,i,query.value(0).toString());
              painter.drawText(2300,i,query.value(1).toString());
              painter.drawText(4300,i,query.value(2).toString());
              painter.drawText(6300,i,query.value(3).toString());/*
              painter.drawText(8000,i,query.value(4).toString());
              painter.drawText(10000,i,query.value(5).toString());
              painter.drawText(12000,i,query.value(6).toString());
              painter.drawText(14000,i,query.value(7).toString());*/
              i = i +500;
          }

          int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
          if (reponse == QMessageBox::Yes)
          {
              QDesktopServices::openUrl(QUrl::fromLocalFile("D:/Esprit/2eme année/semestre 1/projet cpp/avion.pdf"));

              painter.end();
          }
          if (reponse == QMessageBox::No)
          {
              painter.end();
          }

          /*painter.setPen(Qt::black);
          QSqlQuery query;
          query.prepare("select *from employe");

          if(query.exec())
          {

              while(query.next())
              {
                 painter.drawText(100,0,query.value(0).toString());
                 painter.drawText(900,800,query.value(1).toString());
                 painter.drawText(200,200,query.value(2).toString());
                 painter.drawText(300,300,query.value(3).toString());
                 painter.drawText(400,400,query.value(4).toString());
                 painter.drawText(500,500,query.value(5).toString());
              }
          }


          painter.end();

          QMessageBox::information(nullptr, QObject::tr("PDF"),
                   QObject::tr("PDF Créer/Modifier avec succes\n""Click Cancel to exit."),QMessageBox::Cancel);*/

}

