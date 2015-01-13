//#########################################################################################
// Projekt: Heart Rate 2 go
// Copyright: 2014
//#########################################################################################

/**
  * @file   MoodType.cpp
  * @author Patrick Mathias, Markus Nebel
  * @author responsible: Markus Nebel
  * @date   12.12.2014 14:33:34 GMT
  *
  * @brief  Implementation file of MoodType class
  *
  */

#include "MoodType.h"

const quint8 MoodType::numOfTypes = 3;
const char* MoodType::typeName[] = {
    "good",
    "average",
    "bad"
};
