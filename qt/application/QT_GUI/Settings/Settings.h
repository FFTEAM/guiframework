#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QDir>
#include <QSettings>

class Settings final
{
    static Settings* mInstance;
    QSettings mSettings;
    QDir mDirectory;

    bool mIsValid;

    Settings();
    Settings(const Settings&);
    const Settings& operator=(const Settings&);

public:
    static Settings& getInstance();
    explicit operator bool() const;

    ~Settings();

    QString mDataTimeFormat;
    QString mDataDirectory;
};

#endif // SETTINGS_H
