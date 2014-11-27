#include "searchdevicebuttoncontroler.h"

SearchDeviceButtonControler::SearchDeviceButtonControler(QObject* aParent, DeviceModel* aModel) :    QObject(aParent),
                                                                                                     m_dataList(aModel)
{
    // C'tor
    if(aParent)
    {
        QObject* child =  aParent->findChild<QObject*>("searchDeviceButton");
        if(child)
        {
            QObject::connect(child, SIGNAL(searchDeviceButtonIsPressed()), this, SLOT(clickSearchDeviceButtonSlot()));
        }
        else qDebug() << "No child found";
    }
    else qDebug() << "Signal could not attached to a slot";
}

void SearchDeviceButtonControler::clickSearchDeviceButtonSlot()
{
    // recive Signal from searchDeviceButton

    if(m_dataList)
    {
        QList<DeviceData> list;
        list.append(DeviceData("Device1"));
        list.append(DeviceData("Device2"));
        list.append(DeviceData("Device3"));
        list.append(DeviceData("Device4"));
        list.append(DeviceData("Device5"));
        list.append(DeviceData("Device6"));
        m_dataList->setNewDeviceModel(list);
    }
    else qDebug () << "Null pointer";
}
