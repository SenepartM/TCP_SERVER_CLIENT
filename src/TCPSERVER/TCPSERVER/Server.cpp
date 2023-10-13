#include "Server.h"

Server::Server(QObject* parent) : QTcpServer(parent), m_socket(nullptr) {}

void Server::startServer(quint16 port) {                               // quint16 est un type de donn�es sp�cifique � Qt. Il repr�sente un entier non sign� de 16 bits, ce qui signifie qu'il peut stocker des valeurs allant de 0 � 65,535.  Dans le contexte des ports TCP / IP, un num�ro de port est toujours un entier non sign� de 16 bits, avec des valeurs valides allant de 0 � 65535.
    if (this->listen(QHostAddress::AnyIPv4, port))
        qDebug() << "Server started on port" << port;
    else
        qDebug() << "Could not start server";
}

void Server::incomingConnection(qintptr socketDescriptor) {
    m_socket = new QTcpSocket(this);
    m_socket->setSocketDescriptor(socketDescriptor);
    qDebug() << "Client connected: " << m_socket->peerAddress().toString();  // affichage dans la console que l'utilisateur est connect� + son ip

    connect(m_socket, &QTcpSocket::readyRead, this, &Server::readClient);     
    connect(m_socket, &QTcpSocket::disconnected, this, &Server::clientDisconnected); //lorsque le client connect� � m_socket se d�connecte, le signal disconnected est �mis . Donc, chaque fois qu'un client se d�connecte, la fonction clientDisconnected de la classe Server est automatiquement appel�e.
}

void Server::readClient() {
    sendResponse(m_socket->readLine().trimmed());
}

void Server::clientDisconnected() {
    qDebug() << "Client disconnected: " << m_socket->peerAddress().toString();
    m_socket->deleteLater();
    m_socket = nullptr;
}

// GPT : 
void Server::sendResponse(const QString& request) {
    QString type = request.mid(0, 2);
    QString nbCapteur = request.mid(2, 2);

    QString response;
    if (type == "Td") {
        // Fournir une temp�rature en Celsius, pour l'instant je g�n�re une valeur al�atoire
        double tempC = -20.0 + (qrand() % static_cast<int>(55.0 * 100 + 1)) / 100.0;
        response = QString("Temp�rature %1: %2%3 �C").arg(nbCapteur).arg(tempC >= 0 ? '+' : '-').arg(fabs(tempC), 0, 'f', 2);
    }
    else if (type == "Tf") {
        // Fournir une temp�rature en Fahrenheit, pour l'instant je g�n�re une valeur al�atoire
        double tempF = -20.0 + (qrand() % static_cast<int>(55.0 * 100 + 1)) / 100.0;  // Note: This is just for the example, in reality, you would fetch real data
        response = QString("Temp�rature %1: %2%3 �F").arg(nbCapteur).arg(tempF >= 0 ? '+' : '-').arg(fabs(tempF), 0, 'f', 2);
    }
    else if (type == "Hr") {
        // Fournir une hygrom�trie, pour l'instant je g�n�re une valeur al�atoire
        double humidity = (qrand() % 1000) / 10.0;
        response = QString("Hygrom�trie %1: %2 %").arg(nbCapteur).arg(humidity, 0, 'f', 1);
    }
    else {
        qDebug() << "Unknown request type.";
        return;
    }

    m_socket->write(response.toUtf8());
}