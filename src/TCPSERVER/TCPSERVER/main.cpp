#include <QCoreApplication>
#include "Server.h"

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    Server server;
    server.startServer(667);  // D�marrage du serveur sur le port 667

    return a.exec();
}

