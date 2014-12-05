#include "connectionbuttoncontroler.h"


ConnectionButtonControler::ConnectionButtonControler(QObject* aParent, DeviceModel *aModel) :   QObject(aParent),
                                                                                                m_dataList(aModel)
{
    // C'tor
    if(aParent)
    {
        QObject* child =  aParent->findChild<QObject*>("connectionButton");
        if(child)
        {
            QObject::connect(child, SIGNAL(connectionButtonIsPressed(int)), this, SLOT(clickConnectionButtonSlot(const int)));
        }
        else qDebug() << "No child found";
    }
    else qDebug() << "Signal could not attached to a slot";
}

void ConnectionButtonControler::clickConnectionButtonSlot(const int aCurrentIndex)
{
    if(m_dataList)
    {
        const DeviceData* checkDevice = m_dataList->getDevice(aCurrentIndex);
        if(checkDevice != 0)
        {
            DeviceData currentDevice = *checkDevice;
            if(currentDevice.getCurrentState() == DISCONNECT)
            {
                currentDevice.setCurrentState(CONNECT);
                m_dataList->clearDeviceModel();
                m_dataList->addDevice(currentDevice);
            }
            else
            {
                currentDevice.setCurrentState(DISCONNECT);
                m_dataList->updateDevice(aCurrentIndex, currentDevice);
            }
            parent()->findChild<QObject*>("listViewName")->setProperty("currentIndex",0);
        }
        else
        {
            qDebug() << "Null pointer";
        }
    }
    else qDebug() << "Null pointer";
}
