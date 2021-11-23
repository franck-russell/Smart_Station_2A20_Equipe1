#ifndef CHAT1_H
#define CHAT1_H

#include <QDialog>
#include "ui_chat1.h"
#include <QtNetwork>

namespace Ui {
class chat1;
}

class chat1 : public QDialog, private Ui::chat1
{
    Q_OBJECT

public:
    chat1();

private slots:
    void on_pb_connexion_clicked();
    void on_pb_envoyer_clicked();
    void on_le_message_returnPressed();
    void donneesrecues();
    void connecter();
    void deconnecter();
    void erreursocket(QAbstractSocket::SocketError erreur);

private:
    QTcpSocket *socket; // Représente le serveur
    quint16 tailleMessage;
};

#endif // CHAT1_H
