#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QDir>

class Settings final
{
    static Settings* mInstance;

    Settings();
    Settings(const Settings&);
    const Settings& operator=(const Settings&);

public:
    static Settings& getInstance();
    explicit operator bool() const;

    ~Settings();

    QString mUserDataDirectory;
    QString mDataTimeFormat;

private:
    QDir mDirectory;
    QSettings testSettings;

    bool mIsValid;
};

#endif // SETTINGS_H
