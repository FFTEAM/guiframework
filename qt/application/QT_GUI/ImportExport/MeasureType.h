//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   MeasureType.h
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Markus Nebel
  * @date   12.12.2014 14:33:34 GMT
  *
  * @brief  Class definition of MeasureType
  *
  */

#ifndef MEASURETYPE_H
#define MEASURETYPE_H

#include <QtGlobal>

/**
 * @class MeasureType
 * @brief The MeasureType class is a container for static const strings of measurement types
 */
class MeasureType final
{
    /**
     * @brief MeasureType constructor is disabled
     */
    MeasureType() = delete;
public:
    /**
     * @brief numOfTypes number of available types
     */
    static const quint8 numOfTypes;

    /**
     * @brief typeName static const string of earch type name
     */
    static const char* typeName[];
};

#endif // MEASURETYPE_H
