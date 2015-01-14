#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QDir>
#include <QSettings>

/**
 * @class Settings
 * @brief Singleton class container for settings configuration
 */
class Settings final
{
    /**
     * @brief mInstance holding the single instance of this class
     */
    static Settings* mInstance;

    /**
     * @brief mSettings holding the QSettings abstraction
     *
     * for plattform independent key - value settings
     */
    QSettings mSettings;

    /**
     * @brief mDirectory holding the home directory of the operating system user
     */
    QDir mDirectory;

    /**
     * @brief mIsValid flag for operator bool
     */
    bool mIsValid;

    /**
     * @brief Settings private constructor for single instance
     */
    Settings();

    /**
     * @brief Settings copy-constructor is disabled
     */
    Settings(const Settings&) = delete;

    /**
     * @brief operator = is disabled
     * @return not implemented
     */
    const Settings& operator=(const Settings&);

public:
    /**
     * @brief getInstance creates single instance
     * @return object reference to the single instance
     */
    static Settings& getInstance();

    /**
     * @brief operator bool get information about the state of this object
     * @return true when object initialization was successful, false otherwise
     */
    explicit operator bool() const;

    ~Settings();

    /**
     * @brief mDataFormat representing the operating system defined DateFormat
     */
    const QString mDateFormat;

    /**
     * @brief mTimeFormat representing the operating system defined TimeFormat
     */
    const QString mTimeFormat;

    /**
     * @brief mDataDirectory string of the HeartRate2Go user directory
     */
    QString mDataDirectory;
};

#endif // SETTINGS_H
