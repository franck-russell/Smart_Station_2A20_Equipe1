#include "avion.h"
#include "ui_avion.h"
#include <QPixmap>

avion::avion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::avion)
{
    ui->setupUi(this);
    QPixmap pix("D:/Esprit/2eme année/semestre 1/projet cpp/logo/image2");
    int w = ui->label_image2->width();
    int h = ui->label_image2->height();
    ui->label_image2->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
}

avion::~avion()
{
    delete ui;
}
