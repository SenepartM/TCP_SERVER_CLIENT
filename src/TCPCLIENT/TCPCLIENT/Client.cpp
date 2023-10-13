#include "Client.h"

Client::Client(QWidget *parent)
    : QMainWindow(parent)
{

    ui.setupUi(this);
    ui.AWNS->setReadOnly(true);
    socket = new QTcpSocket(this);
   QObject::connect(socket, SIGNAL(connected()), this, SLOT(onSocketConnected()));
   QObject::connect(socket, SIGNAL(disconnected()), this, SLOT(onSocketDisconnected()));
   QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(onSocketDataReceived()));

}
void Client::onConnectButtonClicked()
{
    QString ip = ui.IPLineEdit->text();
    QString port = ui.portLineEdit->text();

    bool ok;
    int portAsInt = port.toInt(&ok);
    if (ok) {
        socket->connectToHost(ip, portAsInt);
    }
}
void Client::onDisconnectButtonClicked()
{
    if (socket->state() == QAbstractSocket::ConnectedState) {
        socket->disconnectFromHost();
    }
}
void Client::onSocketConnected()
{
    ui.IPLineEdit->hide();
    ui.portLineEdit->hide();
    ui.label_2->hide();
    ui.label_3->hide();
     ui.connectionStatusLabel->setText("Vous êtes bien connecté");

}

void Client::onSocketDisconnected()
{
    ui.IPLineEdit->show();
    ui.portLineEdit->show();
    ui.label_2->show();
    ui.label_3->show();
    ui.connectionStatusLabel->setText("Vous êtes déconnecté");
}
void Client::onCelsiusButtonClicked()
{
    QString nCapteurStr = ui.ASK->text();
    int nCapteur = nCapteurStr.toInt();

    if (nCapteur >= 1 && nCapteur <= 99) {
        QString message = QString("Td%1?").arg(nCapteur, 2, 10, QChar('0'));  // %1 est un marqueur de position, nCapteur est ce qui sera a la place de %1 , 2 est la largeur minimale de la valeur(si on entre 1 ca mettra 01), 10 est la base (base 10 (decimale)) ,QChar('0') indique le caractère à utiliser pour le remplissage. Si nCapteur a moins de 2 chiffres, il sera précédé d'un zéro pour s'assurer qu'il occupe deux places.
        socket->write(message.toUtf8());
    }
    else {
        ui.AWNS->setText("Numéro de capteur invalide");
    }
}
void Client::onFahrenheitButtonClicked()
{
    QString nCapteurStr = ui.ASK->text();
    int nCapteur = nCapteurStr.toInt();

    if (nCapteur >= 1 && nCapteur <= 99) {
        QString message = QString("Tf%1?").arg(nCapteur, 2, 10, QChar('0'));
        socket->write(message.toUtf8());
    }
    else {
        ui.AWNS->setText("Numéro de capteur invalide");
    }
}
void Client::onHygrometrieButtonClicked()
{
    QString nCapteurStr = ui.ASK->text();
    int nCapteur = nCapteurStr.toInt();

    if (nCapteur >= 1 && nCapteur <= 99) {
        QString message = QString("Hr%1?").arg(nCapteur, 2, 10, QChar('0'));
        socket->write(message.toUtf8());
    }
    else {
        ui.AWNS->setText("Numéro de capteur invalide");
    }
}
void Client::onSocketDataReceived()
{
    QString dataReceived = socket->readAll();
    ui.AWNS->setText(dataReceived); 
}