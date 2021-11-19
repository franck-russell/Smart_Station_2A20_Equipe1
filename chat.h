#ifndef CHAT_H
#define CHAT_H

#include <QDialog>
#include "ui_chat.h"
#include <QtNetwork>

namespace Ui {
class chat;
}

class chat : public QDialog, private Ui::chat
{
    Q_OBJECT

public:
    chat();
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

#endif // CHAT_H
