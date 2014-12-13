#include "TcpServer.h"
#include "TcpConnection.h"

TcpServer::TcpServer(QObject *aParent) :
    QTcpServer(aParent)
{
}

void TcpServer::startServer()
{
    int port = 1234;

    if(!this->listen(QHostAddress::Any, port))
    {
        qDebug() << "Could not start server";
    }
    else
    {
        qDebug() << "Listening to port " << port << "...";
    }
}

// This function is called by QTcpServer when a new connection is available.
void TcpServer::incomingConnection(qintptr aSocketDescriptor)
{
    // We have a new connection
    qDebug() << aSocketDescriptor << " Connecting...";

    // Every new connection will be run in a newly created thread
    TcpConnection* thread = new TcpConnection(aSocketDescriptor, this);

    // connect signal/slot
    // once a thread is not needed, it will be beleted later
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    thread->start();
}
