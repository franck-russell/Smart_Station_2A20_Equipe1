#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "vol.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_ajouter_clicked();
    void on_pushButton_supprimer_clicked();
    void on_pushButton_modifier_clicked();
    void on_pushButton_loadlist_clicked();
    void on_comboBox_modifier_currentIndexChanged(int index);
private:
    Ui::MainWindow *ui;
    Vol V;
};
#endif // MAINWINDOW_H
