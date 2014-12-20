#ifndef DEVICECONNECTOR_H
#define DEVICECONNECTOR_H

#include <QThread>
#include <QTcpSocket>

class TcpConnection : public QThread
{
    Q_OBJECT
public:
    TcpConnection(qintptr aSocketDescriptor, QObject* aParent = 0);
    void run();

signals:
    void error(QTcpSocket::SocketError socketerror);

public slots:
    void readyRead();
    void disconnected();

private:
    QTcpSocket *mSocket;
    qintptr mSocketDescriptor;
    QByteArray mBuffer;

    TcpConnection(const TcpConnection&);
    const TcpConnection& operator=(const TcpConnection&);
};

#endif // DEVICECONNECTOR_H