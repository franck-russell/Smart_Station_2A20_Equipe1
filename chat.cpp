#include "chat.h"
#include "ui_chat.h"
#include <QString>


chat::chat()
{
    setupUi(this);

    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(donneesrecues()));
    connect(socket, SIGNAL(connected()), this, SLOT(connecter()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(deconnecter()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(erreursocket(QAbstractSocket::SocketError)));

    tailleMessage = 0;
}

void chat::on_pb_connexion_clicked()
{
    // On annonce sur la fenêtre qu'on est en train de se connecter
    textEdit->append(tr("<em>Tentative de connexion en cours...</em>"));
    pb_connexion->setEnabled(false);

    socket->abort(); // On désactive les connexions précédentes s'il y en a
    socket->connectToHost(le_ip->text(), le_port->text().toInt()); // On se connecte au serveur demandé
}

void chat::on_pb_envoyer_clicked()
{
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    // On prépare le paquet à envoyer
    QString messageAEnvoyer = tr("<strong>") + le_pseudo->text() +tr("</strong> : ") + le_message->text();

    out << (quint16) 0;
    out << messageAEnvoyer;
    out.device()->seek(0);
    out << (quint16) (paquet.size() - sizeof(quint16));

    socket->write(paquet); // On envoie le paquet

    le_message->clear(); // On vide la zone d'écriture du message
    le_message->setFocus(); // Et on remet le curseur à l'intérieur
}

void chat::on_le_message_returnPressed()
{
    on_pb_envoyer_clicked();
}

void chat::donneesrecues()
{
    /* Même principe que lorsque le serveur reçoit un paquet :
    On essaie de récupérer la taille du message
    Une fois qu'on l'a, on attend d'avoir reçu le message entier (en se basant sur la taille annoncée tailleMessage)
    */
    QDataStream in(socket);

    if (tailleMessage == 0)
    {
        if (socket->bytesAvailable() < (int)sizeof(quint16))
             return;

        in >> tailleMessage;
    }

    if (socket->bytesAvailable() < tailleMessage)
        return;


    // Si on arrive jusqu'à cette ligne, on peut récupérer le message entier
    QString messageRecu;
    in >> messageRecu;

    // On affiche le message sur la zone de Chat
    textEdit->append(messageRecu);

    // On remet la taille du message à 0 pour pouvoir recevoir de futurs messages
    tailleMessage = 0;
}

void chat::connecter()
{
    textEdit->append(tr("<em>Connexion réussie !</em>"));
    pb_connexion->setEnabled(true);
}

void chat::deconnecter()
{
    textEdit->append(tr("<em>Déconnecté du serveur</em>"));
}

void chat::erreursocket(QAbstractSocket::SocketError erreur)
{
    switch(erreur) // On affiche un message différent selon l'erreur qu'on nous indique
    {
        case QAbstractSocket::HostNotFoundError:
            textEdit->append(tr("<em>ERREUR : le serveur n'a pas pu être trouvé. Vérifiez l'IP et le port.</em>"));
            break;
        case QAbstractSocket::ConnectionRefusedError:
            textEdit->append(tr("<em>ERREUR : le serveur a refusé la connexion. Vérifiez si le programme \"serveur\" a bien été lancé. Vérifiez aussi l'IP et le port.</em>"));
            break;
        case QAbstractSocket::RemoteHostClosedError:
            textEdit->append(tr("<em>ERREUR : le serveur a coupé la connexion.</em>"));
            break;
        default:
            textEdit->append(tr("<em>ERREUR : ") + socket->errorString() + tr("</em>"));
    }

    pb_connexion->setEnabled(true);
}
