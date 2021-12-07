 #include "dialogA.h"
#include "ui_dialogA.h"
#include <QPixmap>
#include "avions.h"
#include "arduino.h"
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
#include <QFileDialog>


dialogA::dialogA(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogA)
{
    ui->setupUi(this);
    ui->le_identifiant->setValidator(new QIntValidator(0, 999999, this));
    ui->le_capacite->setValidator(new QIntValidator(0, 99, this));
    ui->le_capacite_2->setValidator(new QIntValidator(0, 99, this));
    ui->le_rechercher->setValidator(new QIntValidator(0, 999999, this));
    ui->le_recherche_avancee->setValidator(new QIntValidator(0, 999999, this));
    ui->tab_afficher->setModel(A.afficher());
    ui->cb_suppression->setModel(A.afficher_ID());
    ui->cb_modifier->setModel(A.afficher_ID());
/////////////arduino/////////////
    int ret=O.connect_arduino();
    switch(ret)
    {
    case(0):qDebug()<<"arduino is available and connected to : "<< O.getarduino_port_name();
        break;
    case(1):qDebug()<<"arduino is available but not connected to:"<<O.getarduino_port_name();
        break;
    case(-1):qDebug()<<"arduino is not available";
    }
    QObject::connect(O.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
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
    }
        else {
        QMessageBox::critical(nullptr, QObject::tr(" Not OK"),
                     QObject::tr("Echec de suppression\n"
                                "click Cancel to exist."), QMessageBox::Cancel);
}
}

void dialogA::on_pb_rechercher_clicked()
{
    Avions A1; A1.setidentifiant(ui->le_rechercher->text().toInt());
    int identifiant=ui->le_rechercher->text().toInt();
    ui->tab_afficher->setModel(A1.rechercher(identifiant));
    QString test=ui->le_rechercher->text();
    if(test=="")
    {
        ui->tab_afficher->setModel(A.afficher());
    }

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

    Avions A(identifiant,capacite,type,etat);
    bool test=A.modifier();

    if(test)
    {QMessageBox::information(nullptr, QObject::tr("OK"),
                QObject::tr("Modification avec succes\n"
                           "click Cancel to exist."), QMessageBox::Cancel);
        ui->tab_afficher->setModel(A.afficher());
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


void dialogA::on_pb_pdf_clicked()
{
        QPdfWriter pdf("D:/Esprit/2eme année/semestre 1/projet cpp/avion.pdf");

          QPainter painter(&pdf);

          int i = 5000;
          painter.setPen(Qt::blue);
          painter.setFont(QFont("time new roman", 25));
          painter.drawPixmap(QRect(200,200,2000,2000),QPixmap("D:/Esprit/2eme année/semestre 1/projet cpp/logo/logo4.png"));
          painter.drawPixmap(QRect(7800,150,1700,1700),QPixmap("D:/Esprit/2eme année/semestre 1/projet cpp/logo/esprit.png"));
          painter.drawText(1900,3500,"INFORMATIONS SUR LES AVIONS");
          painter.drawText(3400,2500,"SMART STATION");
          painter.drawText(3900,3000,"SOLID'AIR");
          painter.setPen(Qt::black);
          painter.setFont(QFont("time new roman", 25));
          painter.drawRect(1750,2000,6700,1600);
          painter.drawRect(200,4000,9000,500);
          painter.setFont(QFont("time new roman", 11));
          painter.drawText(700,4300,"IDENTIFIANT");
          painter.drawText(2600,4300,"CAPACITE");
          painter.drawText(4500,4300,"TYPE");
          painter.drawText(7000,4300,"ETAT");
          QSqlQuery query;
          query.prepare("select * from AVION");
          query.exec();
          while (query.next())
          {
              painter.drawText(700,i,query.value(0).toString());
              painter.drawText(2600,i,query.value(1).toString());
              painter.drawText(4500,i,query.value(2).toString());
              painter.drawText(7000,i,query.value(3).toString());
              i = i +500;
          }

          int reponse = QMessageBox::question(this, "Génerer PDF", "PDF Enregistré"
                                                                   "voulez-vous l'afficher?", QMessageBox::Yes |  QMessageBox::No);
          if (reponse == QMessageBox::Yes)
          {
              QDesktopServices::openUrl(QUrl::fromLocalFile("D:/Esprit/2eme année/semestre 1/projet cpp/avion.pdf"));

              painter.end();
          }
          if (reponse == QMessageBox::No)
          {
              painter.end();
          }

}


void dialogA::on_pb_docExel_clicked()
{
    QTableView *table;
          table = ui->tab_afficher;

          QString filters("csv files (.csv);;All files (.*)");
          QString defaultFilter("All files ("".*)");
          QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                             filters, &defaultFilter);
          QFile file(fileName);

          QAbstractItemModel *model =  table->model();
          if (file.open(QFile::WriteOnly | QFile::Truncate)) {
              QTextStream data(&file);
              QStringList strList;
              for (int i = 0; i < model->columnCount(); i++) {
                  if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                      strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                  else
                      strList.append("");
              }
              data << strList.join(";") << "\n";
              for (int i = 0; i < model->rowCount(); i++) {
                  strList.clear();
                  for (int j = 0; j < model->columnCount(); j++) {

                      if (model->data(model->index(i, j)).toString().length() > 0)
                          strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                      else
                          strList.append("");
                  }
                  data << strList.join(";") + "\n";
              }
              file.close();
              QMessageBox::information(this,"Exporter To Excel","Exporté avec succées ");
          }
}


void dialogA::on_cb_trie_currentIndexChanged(int index)
{
    switch(index){
    case 0:
        ui->tab_afficher->setModel(A.afficher());
        break;
    case 1:
        ui->tab_afficher->setModel(A.tri_capacite());
        break;
    case 2 :
        ui->tab_afficher->setModel(A.tri_type());
        break;
    case 3:
        ui->tab_afficher->setModel(A.tri_etat());
        break;
    }

}


void dialogA::on_le_recherche_avancee_textChanged()
{
    A.clearTable(ui->tab_afficher);
        int identifiant=ui->le_recherche_avancee->text().toInt();
        A.recherche_avancee(ui->tab_afficher,identifiant);

}


void dialogA::on_pb_pageWeb_clicked()
{
    QDesktopServices::openUrl(QUrl("https://esprit-tn.com/esponline/online/default.aspx",QUrl::TolerantMode));
}


void dialogA::on_pb_pageweb_3_clicked()
{
      QDesktopServices::openUrl(QUrl("https://www.facebook.com/esprit.tn",QUrl::TolerantMode));
}


void dialogA::on_pb_pageweb_2_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.jumia.com.tn/",QUrl::TolerantMode));
}

void dialogA::update_label()
{

    QString data;
    data=O.read_from_arduino();
    ui->temp->setText(data);
}




void dialogA::on_activer_clicked()
{
    O.write_to_arduino("1"); //envoyer 1 à arduino
}


void dialogA::on_arreter_clicked()
{
    O.write_to_arduino("2");
}

