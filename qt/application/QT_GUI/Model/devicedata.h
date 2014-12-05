#ifndef DEVICEDATA_H
#define DEVICEDATA_H

#include <QString>
#include "RessourceFilePaths.h"


enum DEVICE_STATE {CONNECT, DISCONNECT};

class DeviceData
{
    public:

        DeviceData(const QString& aDeviceName);
        DeviceData(const DeviceData& aDevice);

        QString getDeviceName () const;
        QString getColor () const;
        DEVICE_STATE getCurrentState() const;

        void setDeviceName(const QString& aDeviceName);
        void setColor(const QString& aColor);
        void setCurrentState(const DEVICE_STATE& aState);

    private:

        // member variables
        QString m_deviceName;
        QString m_color;
        DEVICE_STATE m_currentSate;

};

#endif // DEVICEDATA_H
