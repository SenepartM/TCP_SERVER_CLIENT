#pragma once
#include <QTcpServer>
#include <QTcpSocket>

class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server(QObject* parent = nullptr);
    void startServer(quint16 port);
    void incomingConnection(qintptr socketDescriptor) override;

public slots:
    void readClient();
    void clientDisconnected();

private:
    QTcpSocket* m_socket;
    void sendResponse(const QString& request);
};
