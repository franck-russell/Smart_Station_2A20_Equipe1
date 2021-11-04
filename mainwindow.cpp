#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include "dialogA.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix("D:/Esprit/2eme année/semestre 1/projet cpp/logo/image1");
    int w = ui->label_image1->width();
    int h = ui->label_image1->height();
    ui->label_image1->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    //QPixmap pix("D:/Esprit/2eme année/semestre 1/projet cpp/logo/logo4");
    //ui->label_logo4->setPixmap(pix);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_seconnecter_clicked()
{
dialogA d;
d.exec();
}

