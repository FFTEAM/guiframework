//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   TcpServer.h
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Markus Nebel
  * @date   12.12.2014 14:33:34 GMT
  *
  * @brief  Class definition of TcpServer
  *
  */

#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>

/**
 * @brief The TcpServer class is implementing the TcpServer Threadloop
 */
class TcpServer final : public QTcpServer
{
    Q_OBJECT
public:
    /**
     * @brief TcpServer constructor
     * @param aParent QObject of parent class
     */
    explicit TcpServer(QObject* aParent = 0);

    /**
     * @brief ~TcpServer destructor
     *
     * Is closing socket and marking it for release
     */
    virtual ~TcpServer();

    /**
     * @brief startServer switches socket into listen-mode
     */
    void startServer();

protected:
    /**
     * @brief incomingConnection implementation of QTcpSocket pure virtual method
     * @param aSocketDescriptor filedescriptor of new established connection
     *
     * Is calld by QTcpSocket on new connection
     */
    virtual void incomingConnection(qintptr aSocketDescriptor);

private:
    /**
     * @brief TcpServer copy-constructor is disabled
     */
    TcpServer(const TcpServer&) = delete;

    /**
     * @brief operator = is disabled
     * @return not implemented
     */
    const TcpServer& operator=(const TcpServer&) = delete;
};

#endif // TCPSERVER_H
