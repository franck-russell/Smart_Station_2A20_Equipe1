#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clients.h"
#include <QMessageBox>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QApplication>
#include <QIntValidator>
#include <QFileDialog>
#include"smtp.h"
#include <QFileDialog>
#include<QFile>
#include<QStringList>
#include<QPainter>
#include<QPdfWriter>
#include<QWriteLocker>
#include <QDesktopServices>
#include <QUrl>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{  //------------------------------------------------------------------affichage-------------------------------------------------------------------
    ui->setupUi(this);
    ui->table_clients->setModel(c.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

//----------------------------------------------------------------------ajouter---------------------------------------------------------------------
void MainWindow::on_pb_ajouter_clicked()
{
    int CIN=ui->la_cin->text().toInt();
    QString NOM=ui->le_nom->text();
    QString PRENOM=ui->le_prenom->text();
    QString DATE_DE_NAISSANCE=ui->date->text();
    QString NATIONALITE=ui->la_nationalite->text();
    int NUMERO_TELEPHONE=ui->le_num->text().toInt();
    QString ADRESSE_MAIL=ui->adresse_mail->text();


    clients c(CIN,NOM,PRENOM,DATE_DE_NAISSANCE,NATIONALITE,NUMERO_TELEPHONE,ADRESSE_MAIL);
    if(c.controlSaisiecin(CIN,"CIN")&&c.controlSaisienom(NOM,"NOM")&&c.controlsaisieprenom(PRENOM,"PRENOM")&&c.controlsaisieDate(DATE_DE_NAISSANCE)&&c.controlSaisienationalite(NATIONALITE,"NATIONALITE")&&c.controlsaisieMail(ADRESSE_MAIL)&&c.controlSaisienum(NUMERO_TELEPHONE,"NUMERO_TELEPHONE"))
    {
    bool test=c.ajouter();
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
    QObject::tr("Ajout  effectué\n"
    "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    QMessageBox::critical(nullptr, QObject::tr("Not OK"),
    QObject::tr("Ajout non effectué.\n"
    "Click Cancel to exit."),QMessageBox::Cancel);
    ui->la_cin->clear();

}
}
//------------------------------------------------------------------supprimer----------------------------------------------------------------------------

void MainWindow::on_supprimer_clicked()
{
    int CIN=ui->la_cin->text().toInt();
    bool test=Etmp.supprimer(CIN);

    if(test)
    {

        QMessageBox::information(nullptr, QObject::tr("OK"),
    QObject::tr("Suppression  effectuée\n"
    "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    QMessageBox::critical(nullptr, QObject::tr("Not OK"),
    QObject::tr("Suppression non effectuée.\n"
    "Click Cancel to exit."),QMessageBox::Cancel);
}


//------------------------------------------------------------------modifier------------------------------------------------------------------------------------------
void MainWindow::on_pb_modifier_clicked()
{



       int CIN=ui->la_cin->text().toInt();
       QString NOM=ui->le_nom->text();
       QString PRENOM=ui->le_prenom->text();
       QString DATE_DE_NAISSANCE=ui->date->text();
       QString NATIONALITE=ui->la_nationalite->text();
       int NUMERO_TELEPHONE=ui->le_num->text().toInt();
       QString ADRESSE_MAIL=ui->adresse_mail->text();

       clients c(CIN,NOM,PRENOM,DATE_DE_NAISSANCE,NATIONALITE,NUMERO_TELEPHONE,ADRESSE_MAIL);
       bool test=c.modifier(CIN,NOM,PRENOM,DATE_DE_NAISSANCE,NATIONALITE,NUMERO_TELEPHONE,ADRESSE_MAIL);

                       if(test)
                       {
                           ui->table_clients->setModel(Etmp.afficher());
                           QMessageBox::information(nullptr, QObject::tr("modifier un client"),
                                             QObject::tr("client  modifié.\n"
                                                         "Click Cancel to exit."), QMessageBox::Cancel);
                        }

                             else
                                 QMessageBox::critical(nullptr, QObject::tr("Modifier client"),
                                             QObject::tr("Erreur !.\n"
                                                         "Click Cancel to exit."), QMessageBox::Cancel);



                       QMessageBox::information(0,qApp->tr("erreur"),qApp->tr(" L'client a été modifiée."),QMessageBox::Yes);
                        ui->la_cin->clear();
                         ui->le_nom->clear();
                           ui->le_prenom->clear();
                             ui->date->clear();
                               ui->la_nationalite->clear();
                               ui->le_num->clear();

                               ui->adresse_mail->clear();




}


//-------------------------------------------------------------------recherche--------------------------------------------------------

void MainWindow::on_le_recherche_textChanged()
{

    Etmp.clearTable(ui->table_clients);
    int CIN=ui->le_recherche->text().toInt();
    Etmp.rechercher(ui->table_clients,CIN);
}
//------------------------------------------------------------------TRI------------------------------------------------------------------
void MainWindow::on_tri_cin_clicked()
{
    ui->table_clients->setModel(Etmp.tri_CIN());
    QMessageBox::information(nullptr, QObject::tr("OK"),QObject::tr("Tri avec carte d identite effectue.\n" "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_tri_num_clicked()
{
    ui->table_clients->setModel(Etmp.tri_NUM());
    QMessageBox::information(nullptr, QObject::tr("OK"),QObject::tr("Tri avec numero telephone effectue.\n" "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_tri_mail_clicked()
{ ui->table_clients->setModel(Etmp.tri_MAIL());
    QMessageBox::information(nullptr, QObject::tr("OK"),QObject::tr("Tri avec adresse mail effectue.\n" "Click Cancel to exit."), QMessageBox::Cancel);




}
//----------------------------------------------------------image----------------------------------------------------------------------------
void MainWindow::on_btn_image_clicked()
{
    QString filename=QFileDialog::getOpenFileName(this, tr("choose"), "", tr("image (*.png *.jpg *.jpeg *.bmp *.gif)"));
       if(QString::compare(filename,QString())!=0)
       {
           QImage image;
           bool valid = image.load(filename);
           if(valid)
           {
               ui->image_place->setPixmap(QPixmap::fromImage(image));
           }
           else
           {
               QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                     QObject::tr("Image non effectué.\n"
                                                 "Click Cancel to exit."),QMessageBox::Cancel);
           }
       }
}


//---------------------------------------------------------MAILLING----------------------------------------------------------------------------------------
void MainWindow::on_browseBtn_clicked()
{
    files.clear();

        QFileDialog dialog(this);
        dialog.setDirectory(QDir::homePath());
        dialog.setFileMode(QFileDialog::ExistingFiles);

        if (dialog.exec())
            files = dialog.selectedFiles();

        QString fileListString;
        foreach(QString file, files)
            fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

        ui->file->setText( fileListString );
}



void   MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Mail envoyé!\n\n" ) );
    ui->rcpt->clear();
    ui->sujet->clear();
    ui->file->clear();
    ui->msg->clear();
    ui->mail_pass->clear();
}

void MainWindow::on_sendBtn_clicked()
{
    Smtp* smtp = new Smtp("chabbar.oumaima.14@gmail.com",ui->mail_pass->text(), "Smtp.gmail.com");
        connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
    //(const QString &from, const QString &to, const QString &subject, const QString &body)
        if( !files.isEmpty() )
            smtp->sendMail("chabbar.oumaima.14@gmail.com", ui->rcpt->text() ,ui->sujet->text(), ui->msg->toPlainText(), files );
        else
            smtp->sendMail("chabbar.oumaima.14@gmail.com", ui->rcpt->text() ,ui->sujet->text(),ui->msg->toPlainText());
}

//--------------------------------------------------------------exp PDF--------------------------------------------------------------------



void MainWindow::on_pdf_bt_clicked()
{
    QPdfWriter pdf("C:/Users/User/Documents/clients/Liste.pdf");

        QPainter painter(&pdf);


        int i = 4000;
        painter.setPen(Qt::black);
        painter.setFont(QFont("Arial", 30));
        painter.drawPixmap(QRect(100,400,2000,2000),QPixmap("C:/Users/User/Documents/clients/logo.png"));
        painter.drawText(3000,1500,"LISTE DES CLIENTS");
        painter.setPen(Qt::blue);
        painter.setFont(QFont("Arial", 50));
        painter.drawRect(2700,200,6300,2600);
        painter.drawRect(0,3000,9600,500);
        painter.setPen(Qt::black);
        painter.setFont(QFont("Arial", 9));
        painter.drawText(300,3300,"CIN");
        painter.drawText(2300,3300,"NOM");
        painter.drawText(4300,3300,"PRENOM");
        painter.drawText(6000,3300,"DATE_DE_NAISSANCE");
        painter.drawText(8300,3300,"NATIONALITE");
        painter.drawText(10300,3300,"NUMERO_TELEPHONE");
        painter.drawText(10300,3300,"ADRESSE_MAIL");
        QSqlQuery query;
        query.prepare("select * from CLIENT");
        query.exec();
        while (query.next())
        {
            painter.drawText(300,i,query.value(0).toString());
            painter.drawText(2300,i,query.value(1).toString());
            painter.drawText(4300,i,query.value(2).toString());
            painter.drawText(6300,i,query.value(3).toString());
            painter.drawText(8000,i,query.value(4).toString());
            painter.drawText(10000,i,query.value(5).toString());
            painter.drawText(12000,i,query.value(6).toString());

            i = i +500;
        }

        int reponse = QMessageBox::question(this, "PDF généré", "Afficher le PDF ?", QMessageBox::Yes |  QMessageBox::No);
        if(reponse == QMessageBox::Yes)
        {
            QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/User/Documents/clients/Liste.pdf"));

            painter.end();
        }
        if(reponse == QMessageBox::No)
        {
            painter.end();
        }

}

