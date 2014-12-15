#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>

class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TcpServer(QObject* aParent = 0);
    void startServer();

signals:

public slots:

protected:
    void incomingConnection(qintptr aSocketDescriptor);
};

#endif // TCPSERVER_H
