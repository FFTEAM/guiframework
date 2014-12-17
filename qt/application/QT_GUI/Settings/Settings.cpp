#include "Settings.h"

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
    mUserDataDirectory(QDir::homePath() + "/HeartRate"),
    mDataTimeFormat("DD.MM.YYYY HH:MM:SS"),
    mDirectory(QDir(mUserDataDirectory)),
    mIsValid(false)
{
    if (!mDirectory.exists())
    {
        if(mDirectory.mkpath(mUserDataDirectory))
        {
            mIsValid = true;
        }
    }
    else
    {
        mIsValid = true;
    }
}
