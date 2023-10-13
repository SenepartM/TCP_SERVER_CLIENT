#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Client.h"
#include <qtcpsocket.h>

class Client : public QMainWindow
{
    Q_OBJECT

public:
    Client(QWidget *parent = Q_NULLPTR);

private:
    Ui::TCPCLIENTClass ui;
    QTcpSocket* socket;

public slots:
    void onConnectButtonClicked();
    void onDisconnectButtonClicked();
    void onSocketConnected();
    void onSocketDisconnected();
    void onCelsiusButtonClicked();
    void onFahrenheitButtonClicked();
    void onHygrometrieButtonClicked();
    void onSocketDataReceived();
};
