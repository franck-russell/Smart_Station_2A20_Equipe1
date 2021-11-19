#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "clients.h"

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
    void on_pb_ajouter_clicked();

    void on_supprimer_clicked();

    void on_pb_modifier_clicked();


    //void on_chercher_clicked();

   // void on_tri_clicked();

    void on_le_recherche_textChanged();

    void on_tri_cin_clicked();

    void on_tri_num_clicked();

    void on_tri_mail_clicked();

    void on_btn_image_clicked();


    // boton mailing
        void on_browseBtn_clicked();
        void  browse();
        void  mailSent(QString status);
        void on_sendBtn_clicked();

        void on_pdf_bt_clicked();

private:
    Ui::MainWindow *ui;
    clients c;
QStringList files;
    clients Etmp;
};
#endif // MAINWINDOW_H
