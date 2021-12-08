#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vol.h"
#include <QApplication>
#include <QMessageBox>
#include <QIntValidator>
#include <QPainter>
#include <QPrinter>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDesktopServices>
#include <QUrl>
#include <QFileDialog>
#include <QFile>
#include <QPrintDialog>
#include "qrcode.h"
#include <QDate>

using namespace qrcodegen ;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lineEdit_numero->setValidator(new QIntValidator (0,999999,this));

    /*Affichage des colonnes de la table */
    ui->tableView->setModel(V.afficher());
    ui->tableView_2->setModel(V.afficher());
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

void MainWindow::on_lineEdit_cherche_numero_textChanged(const QString &arg1)
{
    ui->lineEdit_cherche_numero->setValidator(new QIntValidator (0,999999,this));
    if(ui->lineEdit_cherche_numero->text()!="")
    {
      QString numero=ui->lineEdit_cherche_numero->text();
      ui->tableView->setModel(V.rechercher(numero));
    }
    else
    ui->tableView->setModel(V.afficher());
}


void MainWindow::on_comboBox_tri_currentIndexChanged(const QString &arg1)
{
    QString crit=ui->comboBox_tri->currentText();
    if(crit=="numero")
    {
      ui->tableView->setModel(V.trier_par_numero());
    }
    else if (crit=="destination")
    {
      ui->tableView->setModel(V.trier_par_destination());
    }
    else if(crit=="horaire")
    {
      ui->tableView->setModel(V.trier_par_horaire());
    }
    else
    {
      ui->tableView->setModel(V.trier_par_suivi());
    }
}

QString currDate()
{
    QDate date = QDate::currentDate();
    return date.toString("dd.MM.yyyy");
}

void MainWindow::on_pushButton_PDF_clicked()
{

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("C:/Users/HD/Desktop/ESPRIT/2ème année/Semestre 1/Projet C++/liste_des_vols.pdf");

    QPainter painter(&printer);
    painter.drawPixmap(QRect(100,400,2000,2000),QPixmap("C:/Users/HD/Desktop/ESPRIT/2ème année/Semestre 1/Projet C++/logo.png"));
    int i = 4000;
    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 40));
    painter.drawText(3000,1500,"Liste des vols ");
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 20));
    painter.drawRect(2700,200,6000,2000);
    painter.drawRect(0,3000,9600,500);
    painter.setFont(QFont("Arial",10));
    painter.drawText(200,3300,"numero");
    painter.drawText(1500,3300,"destination");
    painter.drawText(2500,3300,"horaire");
    painter.drawText(3300,3300,"suivi");

    QString date= currDate() ;
    painter.drawText(8500,30,date);

    QSqlQuery query;
    query.prepare("select * from VOL ");
    query.exec();
    while (query.next())
    {
        painter.drawText(200,i,query.value(0).toString());
        painter.drawText(1500,i,query.value(1).toString());
        painter.drawText(2500,i,query.value(2).toString());
        painter.drawText(3500,i,query.value(3).toString());

        i = i + 500;
    }

    int reponse = QMessageBox::question(this, "PDF généré", "Afficher le PDF ?", QMessageBox::Yes |  QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/HD/Desktop/ESPRIT/2ème année/Semestre 1/Projet C++/liste_des_vols.pdf"));

        painter.end();
    }
    if (reponse == QMessageBox::No)
    {
        painter.end();
    }
}


void MainWindow::on_pushButton_imprimer_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(0,"Open File",QString(),"PDF File(*.pdf)");

    QPrinter printer;
    QPrintDialog *dlg = new QPrintDialog(&printer,0);

    if(dlg->exec() == QDialog::Accepted)
    {
        QImage pdf(fileName);
        QPainter painter(&printer);
        painter.drawImage(QPoint(0,0),pdf);
        painter.end();
    }

    delete dlg;
}

void MainWindow::on_pushButton_qrcodegen_clicked()
{
    int tabeq=ui->tableView_2->currentIndex().row();
    QVariant idd=ui->tableView_2->model()->data(ui->tableView_2->model()->index(tabeq,0));
    QString numero= idd.toString();
    QSqlQuery qry;
    qry.prepare("select * from VOL where NUMERO=:numero");
    qry.bindValue(":NUMERO",numero);
    qry.exec();
    QString  destination,horaire,suivi;

    while(qry.next())
    {
        numero=qry.value(1).toString();
        destination=qry.value(2).toString();
        horaire=qry.value(3).toString();
        suivi=qry.value(4).toString();
    }
    numero=QString(numero);
    numero="NUMERO:"+numero+"DESTINATION:"+destination+"HORAIRE:"+horaire+"SUIVI:"+suivi;
    QrCode qr = QrCode::encodeText(numero.toUtf8().constData(), QrCode::Ecc::HIGH);

    // Read the black & white pixels
    QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
    for (int y = 0; y < qr.getSize(); y++)
    {
    for (int x = 0; x < qr.getSize(); x++)
    {
    int color = qr.getModule(x, y);  // 0 for white, 1 for black

    // You need to modify this part
    if(color==0)
       im.setPixel(x, y,qRgb(254, 254, 254));
    else
       im.setPixel(x, y,qRgb(0, 0, 0));
    }
    }
    im=im.scaled(200,200);
    ui->qrcodecommande->setPixmap(QPixmap::fromImage(im));
}


}
