#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vol.h"
#include <QApplication>
#include <QMessageBox>
#include <QIntValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lineEdit_numero->setValidator(new QIntValidator (0,999999,this));

    /*Affichage des colonnes de la table */
    ui->tableView->setModel(V.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_ajouter_clicked()
{
    /*Récupération des informations saisies */
    int numero=ui->lineEdit_numero->text().toInt();
    QString destination=ui->lineEdit_destination->text();
    QString horaire=ui->lineEdit_horaire->text();
    QString suivi=ui->lineEdit_suivi->text();

    Vol V(numero, destination, horaire, suivi);

    bool test=V.ajouter();

    if (test)
    {
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Ajout effectué.\n"
                                             "Click Cancel to exit."),QMessageBox::Cancel);

        ui->tableView->setModel(V.afficher());
    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                              QObject::tr("Ajout non effectué.\n"
                                          "Click Cancel to exit."),QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_loadlist_modif_clicked()
{
     QSqlQueryModel*  model=new QSqlQueryModel();
     QSqlQuery query;
     query.prepare("SELECT numero FROM VOL");
     query.exec();
     model->setQuery(query);
     ui->comboBox_modifier->setModel(model);
}

void MainWindow::on_comboBox_modifier_currentIndexChanged(int index)
{

    int numero=ui->comboBox_modifier->currentIndex();
    QString numero_string=QString::number(numero);
    QSqlQuery query;
    query.prepare("SELECT * FROM VOL where numero='"+numero_string+"'");
    if(query.exec())
    {
        while (query.next())
        {
          ui->lineEdit_modif_destination->setText(query.value(1).toString()) ;
          ui->lineEdit_modif_horaire->setText(query.value(2).toString()) ;
          ui->lineEdit_modif_suivi->setText(query.value(3).toString()) ;
        }
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK "),
                    QObject::tr("Echec.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_supprimer_clicked()
{
    int numero=ui->comboBox_supprimer->currentIndex();
    bool test=V.supprimer(numero);

    if (test)
    {
        ui->tableView->setModel(V.afficher());

        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Suppression effectuée.\n"
                                             "Click to exit."),QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                              QObject::tr("Suppression non effectuée.\n"
                                          "Click Cancel to exit."),QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_modifier_clicked()
{
    int numero=ui->comboBox_modifier->currentText().toInt();
    QString destination=ui->lineEdit_modif_destination ->text();
    QString horaire=ui->lineEdit_modif_horaire->text();
    QString suivi=ui->lineEdit_modif_suivi->text();

    Vol V(numero, destination, horaire, suivi);

    bool test=V.modifier();

    if (test)
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                      QObject::tr("Modification effectuée.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

        ui->tableView->setModel(V.afficher());
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                      QObject::tr("Modification non effectuée.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_loadlist_supp_clicked()
{
     QSqlQueryModel*  model=new QSqlQueryModel();
     QSqlQuery query;
     query.prepare("SELECT numero FROM VOL");
     query.exec();
     model->setQuery(query);
     ui->comboBox_supprimer->setModel(model);
}

void MainWindow::on_comboBox_supprimer_currentIndexChanged(int index)
{
    int numero=ui->comboBox_supprimer->currentIndex();
    QString numero_string=QString::number(numero);
    QSqlQuery query;
    query.prepare("DELETE * FROM VOL where numero='"+numero_string+"'");
}
