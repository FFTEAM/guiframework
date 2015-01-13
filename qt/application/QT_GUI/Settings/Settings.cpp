//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   Settings.cpp
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Markus Nebel
  * @date   12.12.2014 14:33:34 GMT
  *
  * @brief  Implementation file of Settings class
  *
  */

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
    mDirectory(QDir::homePath() + "/HeartRate"),
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
