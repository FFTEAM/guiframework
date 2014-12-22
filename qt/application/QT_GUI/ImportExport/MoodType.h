#ifndef MOODTYPE_H
#define MOODTYPE_H

#include <QtGlobal>

class MoodType
{
    MoodType() = delete;
public:
    static const quint8 numOfTypes;
    static const char* typeName[];
};

#endif // MOODTYPE_H
