#include "Settings.h"

#include <QDebug>

Settings* Settings::mInstance = 0;

Settings& Settings::getInstance()
{
    if (!mInstance)
    {
        mInstance = new Settings();
    }

    return *mInstance;
}

Settings::operator bool() const
{
    return mIsValid;
}

Settings::Settings() :
    mSettings(),
    mDirectory(QFileInfo(mSettings.fileName()).path()),
    mIsValid(false),
    mDataTimeFormat("DD.MM.YYYY HH:MM:SS"),
    mDataDirectory(mDirectory.path())
{
    qDebug() << mDirectory.path();

    if (!mDirectory.exists())
    {
        if(mDirectory.mkpath(mDataDirectory))
        {
            mIsValid = true;
        }
    }
    else
    {
        mIsValid = true;
    }
}
