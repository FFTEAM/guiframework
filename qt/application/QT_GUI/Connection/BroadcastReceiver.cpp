//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   BroadcastReceiver.cpp
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Markus Nebel
  * @date   12.12.2014 14:33:34 GMT
  *
  * @brief  Implementation file of BroadcastReceiver class
  *
  */

#include "BroadcastReceiver.h"

BroadcastReceiver::BroadcastReceiver(QObject* aParent) :
    QThread(aParent),
    mSocket(0)
{
}

BroadcastReceiver::~BroadcastReceiver()
{
    mSocket->deleteLater();
}

void BroadcastReceiver::run()
{
    // thread starts here
    qDebug() << " BroadcastReceiver Thread started";

    mSocket = new QUdpSocket();
    mSocket->bind(45454, QUdpSocket::ShareAddress);

    // connect socket and signal
    // note - Qt::DirectConnection is used because it's multithreaded
    //        This makes the slot to be invoked immediately, when the signal is emitted.
    connect(mSocket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);

    // make this thread a loop,
    // thread will stay alive so that signal/slot to function properly
    // not dropped out in the middle when thread dies
    exec();
}

void BroadcastReceiver::readyRead()
{
    // this is the replyer:
    QHostAddress address;
    quint16 port;
    while (mSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(36);
        mSocket->readDatagram(datagram.data(), datagram.size(), &address, &port);

        QString test(datagram);
        QString blaa("86417ce4-4f19-4a59-ae27-f404653e9751");

        if (test.compare(blaa) == 0)
        {
            qDebug() << " got magic broadcast packet from " << address.toString() << ":" << port;
            sleep(1);
            mSocket->writeDatagram(datagram, datagram.size(), address, 45455);
        }
    }
}
