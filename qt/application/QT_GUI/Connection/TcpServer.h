#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>

class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TcpServer(QObject* aParent = 0);
    virtual ~TcpServer();
    void startServer();

signals:

public slots:

protected:
    void incomingConnection(qintptr aSocketDescriptor);

private:
    // avoid copy and assignment
    TcpServer(const TcpServer&);
    const TcpServer& operator=(const TcpServer&);
};

#endif // TCPSERVER_H
