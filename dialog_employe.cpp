#include "dialog_employe.h"
#include "chat.h"
#include "ui_dialog_employe.h"
#include "employe.h"
#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QIntValidator>
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QUrl>

Dialog_employe::Dialog_employe(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_employe)
{
    ui->setupUi(this);
    ui->le_matricule->setValidator(new QIntValidator(0,999999,this));
    ui->le_salaire->setValidator(new QIntValidator(0,999999,this));
    //mise à jour de la table des donnée
    ui->tableView->setModel(Etmp.afficher());
    ui->cb_matricule->setModel(Etmp.afficher_id());
}

Dialog_employe::~Dialog_employe()
{
    delete ui;
}

void Dialog_employe::on_pb_ajouter_clicked()
{
    //Récupération des informations saisies
    int matricule=ui->le_matricule->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    QString datenaissance=ui->le_datenaissance->text();
    QString poste=ui->le_poste->text();
    int salaire=ui->le_salaire->text().toInt();

    Employe E(matricule, nom, prenom, datenaissance, poste, salaire);

    bool test=E.ajouter();

    if(test)
    {
        //mise à jour de la table des donnée
        ui->tableView->setModel(Etmp.afficher());
        ui->cb_matricule->setModel(Etmp.afficher_id());

        QMessageBox::information(nullptr, QObject::tr("OK"),QObject::tr("Ajout effectue.\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("Not OK"),QObject::tr("Ajout non effectue.\n" "Click Cancel to exit."),QMessageBox::Cancel);
    }
}


void Dialog_employe::on_pb_supprimer_clicked()
{
    int matricule=ui->cb_matricule->currentText().toInt();
    bool test=Etmp.supprimer(matricule);
        if(test)
        {
            //mise à jour de la table des donnée
            ui->tableView->setModel(Etmp.afficher());
            ui->cb_matricule->setModel(Etmp.afficher_id());

            QMessageBox::information(nullptr,QObject::tr("OK"),
                                     QObject::tr("Supression effectuée.\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);
        }

        else
        {
            QMessageBox::critical(nullptr,QObject::tr("Not OK"),
                                  QObject::tr("Supression non effectuée.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);
        }
}


void Dialog_employe::on_pb_modifier_clicked()
{
    int matricule=ui->cb_matricule->currentText().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    QString datenaissance=ui->le_datenaissance->text();
    QString poste=ui->le_poste->text();
    int salaire=ui->le_salaire->text().toInt();

    Employe A(matricule, nom, prenom, datenaissance, poste, salaire);

    bool test=A.modifier();

    if(test)
    {
        //mise à jour de la table des donnée
        ui->tableView->setModel(Etmp.afficher());
        ui->cb_matricule->setModel(Etmp.afficher_id());

        QMessageBox::information(nullptr, QObject::tr("OK"),QObject::tr("Modification effectue.\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("Not OK"),QObject::tr("Modification non effectue.\n" "Click Cancel to exit."),QMessageBox::Cancel);
    }
}


void Dialog_employe::on_pb_trim_clicked()
{
    ui->tableView->setModel(Etmp.tri_matricule());
    QMessageBox::information(nullptr, QObject::tr("OK"),QObject::tr("Tri avec matricule effectue.\n" "Click Cancel to exit."), QMessageBox::Cancel);
}


void Dialog_employe::on_pb_tris_clicked()
{
    ui->tableView->setModel(Etmp.tri_salaire());
    QMessageBox::information(nullptr, QObject::tr("OK"),QObject::tr("Tri avec matricule effectue.\n" "Click Cancel to exit."), QMessageBox::Cancel);
}


void Dialog_employe::on_pb_trip_clicked()
{
    ui->tableView->setModel(Etmp.tri_poste());
    QMessageBox::information(nullptr, QObject::tr("OK"),QObject::tr("Tri avec matricule effectue.\n" "Click Cancel to exit."), QMessageBox::Cancel);
}


void Dialog_employe::on_le_recherche_textChanged()
{
    Etmp.clearTable(ui->tableView_2);
    int matricule=ui->le_recherche->text().toInt();
    Etmp.rechercher(ui->tableView_2,matricule);
}


void Dialog_employe::on_pb_pdf_clicked()
{
    QPdfWriter pdf("C:/Users/youss/Desktop/ESPRIT/Projet C++/smart_station/Liste.pdf");

    QPainter painter(&pdf);
    QDate date=QDate::currentDate();
    QRect r=painter.viewport();


    int i = 4000;
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 10));
    painter.drawText(r,Qt::AlignRight,date.toString("dd.MM.yyyy"));
    painter.setFont(QFont("Arial", 30));
    painter.drawPixmap(QRect(100,800,2000,2000),QPixmap("C:/Users/youss/Desktop/ESPRIT/Projet C++/smart_station/logo.png"));
    painter.drawText(3000,1800,"LISTE DES EMPLOYES");
    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 50));
    painter.drawRect(2700,700,6300,2000);
    painter.drawRect(0,3000,9600,500);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 9));
    painter.drawText(300,3300,"Matricule");
    painter.drawText(2300,3300,"Nom");
    painter.drawText(4300,3300,"Prenom");
    painter.drawText(6000,3300,"Date de naissance");
    painter.drawText(8300,3300,"Poste");
    painter.drawText(10300,3300,"Salaire");
    QSqlQuery query;
    query.prepare("select * from EMPLOYE");
    query.exec();
    while (query.next())
    {
        painter.drawText(300,i,query.value(0).toString());
        painter.drawText(2300,i,query.value(1).toString());
        painter.drawText(4300,i,query.value(2).toString());
        painter.drawText(6300,i,query.value(3).toString());
        painter.drawText(8000,i,query.value(4).toString());
        painter.drawText(10000,i,query.value(5).toString());
        i = i +500;
    }

    int reponse = QMessageBox::question(this, "PDF généré", "Afficher le PDF ?", QMessageBox::Yes |  QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/youss/Desktop/ESPRIT/Projet C++/smart_station/Liste.pdf"));

        painter.end();
    }
    if (reponse == QMessageBox::No)
    {
        painter.end();
    }
}

void Dialog_employe::on_pb_chat_clicked()
{
  c= new chat();
  c1= new chat1();
  hide();
  c->show();
  c1->show();
}

void Dialog_employe::on_pb_nettoyer_clicked()
{
    bool test=Etmp.nettoyer();
    if(test)
    {
        //mise à jour de la table des donnée
        ui->tableView->setModel(Etmp.afficher());
        ui->cb_matricule->setModel(Etmp.afficher_id());

        QMessageBox::information(nullptr, QObject::tr("OK"),QObject::tr("Nettoyage effectue.\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("Not OK"),QObject::tr("Nettoyage non effectue.\n" "Click Cancel to exit."),QMessageBox::Cancel);
    }
}

void Dialog_employe::on_cb_matricule_currentIndexChanged(int index)
{
    int matricule=ui->cb_matricule->currentIndex();
        QString matricule_string=QString::number(matricule);

        QSqlQuery query;
        query.prepare("SELECT * FROM EMPLOYE where matricule='"+matricule_string+"'");

        if(query.exec())
        {
            while (query.next())
            {
          ui->le_matricule->setText(query.value(0).toString());
              ui->le_nom->setText(query.value(1).toString()) ;
              ui->le_prenom->setText(query.value(2).toString()) ;
              ui->le_datenaissance->setText(query.value(3).toString()) ;
          ui->le_poste->setText(query.value(4).toString()) ;
          ui->le_salaire->setText(query.value(5).toString()) ;
            }
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("NOT OK "),
                        QObject::tr("Echec.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
}
