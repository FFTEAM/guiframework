#include "TcpConnection.h"
#include "DataReceiver.h"

TcpConnection::TcpConnection(qintptr aSocketDescriptor, QObject* aParent) :
    QThread(aParent),
    mSocketDescriptor(aSocketDescriptor),
    mBuffer()
{
}

void TcpConnection::run()
{
    // thread starts here
    qDebug() << " Thread started";

    mSocket = new QTcpSocket();

    // set the ID
    if(!mSocket->setSocketDescriptor(mSocketDescriptor))
    {
        // something's wrong, we just emit a signal
        emit error(mSocket->error());
        return;
    }

    // connect socket and signal
    // note - Qt::DirectConnection is used because it's multithreaded
    //        This makes the slot to be invoked immediately, when the signal is emitted.

    connect(mSocket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(mSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    // We'll have multiple clients, we want to know which is which
    qDebug() << mSocketDescriptor << " Client connected";

    // make this thread a loop,
    // thread will stay alive so that signal/slot to function properly
    // not dropped out in the middle when thread dies

    exec();
}

void TcpConnection::readyRead()
{
    // get the information
    quint8* buffer = 0;
    qint64 bytesInBuffer = mSocket->bytesAvailable();

    if (0 < bytesInBuffer)
    {
        buffer = new quint8[bytesInBuffer];
        if (buffer)
        {
            qint64 ret = mSocket->read(reinterpret_cast<char*>(buffer), bytesInBuffer);
            if (ret == bytesInBuffer)
            {
                mBuffer.append(reinterpret_cast<char*>(buffer), ret);
            }
            else
            {
                qFatal("tcp read error!");
            }
            delete[] buffer;
            buffer = 0;
        }
        else
        {
            qFatal("memory allocation error!");
        }
    }

    //qDebug() << "[" /*<< mSocket->peerAddress()*/ << ":" << mSocket->peerPort() << "]" << " Data in: " << Data;
}

void TcpConnection::disconnected()
{
    qDebug() << mSocketDescriptor << " Disconnected";
    DataReceiver::getInstance().validateData(reinterpret_cast<const quint8*>(mBuffer.data()), mBuffer.size());

    mSocket->deleteLater();
    exit(0);
}
