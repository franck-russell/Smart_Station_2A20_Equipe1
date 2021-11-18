#ifndef EMPLACEMENT_H
#define EMPLACEMENT_H

#include <QDialog>

namespace Ui {
class Emplacement;
}

class Emplacement : public QDialog
{
    Q_OBJECT

public:
    explicit Emplacement(QWidget *parent = nullptr);
    ~Emplacement();

private:
    Ui::Emplacement *ui;
};

#endif // EMPLACEMENT_H
