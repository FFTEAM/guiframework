#include "devicedata.h"

DeviceData::DeviceData(const QString& aDevicename) :  m_deviceName(aDevicename),
                                                      m_color(OFFLINE_BUTTON_PATH),
                                                      m_currentSate(DISCONNECT)
{
    // C'tor
}

QString DeviceData::getDeviceName() const
{
    return m_deviceName;
}

QString DeviceData::getColor() const
{
    return m_color;
}

DEVICE_STATE DeviceData::getCurrentState() const
{
    return m_currentSate;
}

void DeviceData::setDeviceName(const QString& aDeviceName)
{
    m_deviceName = aDeviceName;
}

void DeviceData::setColor(const QString& aColor)
{
    m_color = aColor;
}

void DeviceData::setCurrentState(const DEVICE_STATE& aState)
{
    if(aState == CONNECT)
    {
        m_currentSate = aState;
        m_color = ONLINE_BUTTON_PATH;
    }
    else
    {
        m_currentSate = aState;
        m_color = OFFLINE_BUTTON_PATH;
    }
}
