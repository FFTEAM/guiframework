//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   BroadcastReceiver.h
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Markus Nebel
  * @date   12.12.2014 14:33:34 GMT
  *
  * @brief  Class definition of BroadcastReceiver
  *
  */

#ifndef BROADCASTRECEIVER_H
#define BROADCASTRECEIVER_H

#include <QThread>
#include <QUdpSocket>

/**
 * @brief The BroadcastReceiver class implements an UDP-Server for Server-Discovery
 */
class BroadcastReceiver final : public QThread
{
    Q_OBJECT
public:
    /**
     * @brief BroadcastReceiver Constructor initializes all attributes of class
     * @param aParent       Pointer to QObject parent class
     */
    explicit BroadcastReceiver(QObject* aParent = 0);

    /**
     * @brief BroadcastReceiver destructor marks UDP-socket as deleteable
     */
    virtual ~BroadcastReceiver();

    /**
     * @brief run implements the QThread Threadloop
     */
    void run();

signals:
    /**
     * @brief error signal on socket errors
     * @param socketerror exception object
     */
    void error(QUdpSocket::SocketError socketerror);

public slots:
    /**
     * @brief readyRead is called on incoming datagram and handles it
     */
    void readyRead();

private:
    /**
     * @brief private udp socket.
     */
    QUdpSocket* mSocket;
};

#endif // BROADCASTRECEIVER_H
