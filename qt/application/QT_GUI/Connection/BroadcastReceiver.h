#ifndef BROADCASTRECEIVER_H
#define BROADCASTRECEIVER_H

#include <QThread>
#include <QUdpSocket>

class BroadcastReceiver : public QThread
{
    Q_OBJECT
public:
    explicit BroadcastReceiver(QObject* aParent = 0);
    virtual ~BroadcastReceiver();
    void run();

signals:
    void error(QUdpSocket::SocketError socketerror);

public slots:
    void readyRead();

private:
    QUdpSocket* mSocket;
};

#endif // BROADCASTRECEIVER_H
