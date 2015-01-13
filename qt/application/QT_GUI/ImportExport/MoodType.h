//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   MoodType.h
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Markus Nebel
  * @date   12.12.2014 14:33:34 GMT
  *
  * @brief  Class definition of MoodType
  *
  */

#ifndef MOODTYPE_H
#define MOODTYPE_H

#include <QtGlobal>

/**
 * @class MoodType
 * @brief The MoodType class is a container for static const strings of mood types
 */
class MoodType
{
    /**
     * @brief MoodType constructor is disabled
     */
    MoodType() = delete;
public:
    /**
     * @brief numOfTypes number of available mood types
     */
    static const quint8 numOfTypes;

    /**
     * @brief typeName static const string of earch type name
     */
    static const char* typeName[];
};

#endif // MOODTYPE_H
