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
    mDateFormat((QLocale::system().country() == QLocale::Germany ? "dd.MM.yyyy" : "MM/dd/yyyy")),
    mTimeFormat((QLocale::system().country() == QLocale::Germany ? "hh:mm:ss" : "hh:mm:ss ap")),
    mDataDirectory(mDirectory.path())
{
    qDebug() << mDataDirectory;
    qDebug() << mDateFormat;
    qDebug() << mTimeFormat;

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
