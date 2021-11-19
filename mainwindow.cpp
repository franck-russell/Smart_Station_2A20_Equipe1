#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog_employe.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_connecter_clicked()
{
    Dialog_employe E;
        QSqlQuery query;

        query.prepare("select * from PERSONNEL where utilisateur=? and mdp=?");

        query.addBindValue(ui->le_utilisateur->text());
        query.addBindValue(ui->le_mdp->text());

        if(query.exec())
            {
                int count=0;
                while(query.next())
                {
                    count++;
                }
                if(count==1)
                {
                    QMessageBox::information(nullptr, QObject::tr("OK"),QObject::tr("Connexion avec succées.\n" "Click Cancel to exit."), QMessageBox::Cancel);
                    hide();
                    E.setModal(true);
                    E.exec();
                }
                if(count<1)
                {
                    QMessageBox::critical(nullptr, QObject::tr("Connexion échouée"),QObject::tr("Login/Mot de passe incorrecte.\n" "Click Cancel to exit."), QMessageBox::Cancel);
                }

            }
            else
            {
                 QMessageBox::critical(nullptr, QObject::tr("Erreur"),QObject::tr("Une erreur s'est produite.\n" "Click Cancel to exit."), QMessageBox::Cancel);
            }
}

void MainWindow::on_pb_inscrire_clicked()
{
    QSqlQuery query;
    QString utilisateur=ui->le_utilisateur->text();
    QString mdp=ui->le_mdp->text();

     query.prepare("insert into PERSONNEL (utilisateur, mdp)" "values(:utilisateur, :mdp)");

     query.bindValue(":utilisateur",utilisateur);
     query.bindValue(":mdp",mdp);

     if(query.exec())
        {
            QMessageBox::information(nullptr, QObject::tr("OK"),
                     QObject::tr("Inscrit avec succes\n""Click Cancel to exit."),QMessageBox::Cancel);
        }
        else
        {
            QMessageBox::critical(nullptr,QObject::tr("Not OK"),
                     QObject::tr("Inscription non effectué.\n""Click Cancel to exit."),QMessageBox::Cancel);
        }
}
