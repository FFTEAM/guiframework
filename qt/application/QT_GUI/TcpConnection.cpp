#include "TcpConnection.h"

TcpConnection::TcpConnection(qintptr aSocketDescriptor, QObject* aParent) :
    QThread(aParent),
    mSocketDescriptor(aSocketDescriptor)
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
    qDebug() << "readyRead(): " << mSocket->bytesAvailable() << " bytes in buffer...";
    char buffer[2048];
    memset(buffer, 0, 2048);

    qint64 ret = mSocket->read(buffer, sizeof(buffer));
    if (ret)
    {
        qDebug() << "read " << ret << buffer;
    }

    // will write on server side window
    //qDebug() << "[" /*<< mSocket->peerAddress()*/ << ":" << mSocket->peerPort() << "]" << " Data in: " << Data;

    //mSocket->write(Data);
}

void TcpConnection::disconnected()
{
    qDebug() << mSocketDescriptor << " Disconnected";

    mSocket->deleteLater();
    exit(0);
}
