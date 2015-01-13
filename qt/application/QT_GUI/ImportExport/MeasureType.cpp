//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   MeasureType.cpp
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Markus Nebel
  * @date   12.12.2014 14:33:34 GMT
  *
  * @brief  Implementation file of MeasureType class
  *
  */

#include "MeasureType.h"

const quint8 MeasureType::numOfTypes = 2;
const char* MeasureType::typeName[] = {
    "activity",
    "rest"
};
