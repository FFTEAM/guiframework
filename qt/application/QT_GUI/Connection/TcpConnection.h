//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   TcpConnection.h
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Markus Nebel
  * @date   12.12.2014 14:33:34 GMT
  *
  * @brief  Class definition of TcpConnection
  *
  */

#ifndef DEVICECONNECTOR_H
#define DEVICECONNECTOR_H

#include <QThread>
#include <QTcpSocket>

/**
 * @class TcpConnection
 * @brief Implementation of established connection handler
 */
class TcpConnection : public QThread
{
    Q_OBJECT
public:
    /**
     * @brief TcpConnection
     * @param aSocketDescriptor
     * @param aParent
     */
    TcpConnection(qintptr aSocketDescriptor, QObject* aParent = 0);
    void run();

signals:
    /**
     * @brief error signal on socket errors
     * @param socketerror exception object
     */
    void error(QTcpSocket::SocketError socketerror);

public slots:
    /**
     * @brief readyRead is called on incoming datagram and handles it
     */
    void readyRead();

    /**
     * @brief disconnected is called on TCP-connection disconnect
     *
     * On disconnect of remote host and successful received data, this method is calling ImportExport
     */
    void disconnected();

private:
    /**
     * @brief mSocket holding the TcpSocket
     */
    QTcpSocket *mSocket;

    /**
     * @brief mSocketDescriptor plain file descriptor of mSocket
     */
    qintptr mSocketDescriptor;

    /**
     * @brief mBuffer contains already received bytes by this connection
     *
     * New bytes are append to this array
     */
    QByteArray mBuffer;

    /**
     * @brief TcpConnection copy constructor is disabled
     */
    TcpConnection(const TcpConnection&) = delete;

    /**
     * @brief operator = is disabled
     * @return not implemented
     */
    const TcpConnection& operator=(const TcpConnection&) = delete;
};

#endif // DEVICECONNECTOR_H
