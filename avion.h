#ifndef AVION_H
#define AVION_H

#include <QDialog>

namespace Ui {
class avion;
}

class avion : public QDialog
{
    Q_OBJECT

public:
    explicit avion(QWidget *parent = nullptr);
    ~avion();

private:
    Ui::avion *ui;
};

#endif // AVION_H
