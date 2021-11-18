#include "emplacement.h"
#include "ui_emplacement.h"

Emplacement::Emplacement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Emplacement)
{
    ui->setupUi(this);
}

Emplacement::~Emplacement()
{
    delete ui;
}
