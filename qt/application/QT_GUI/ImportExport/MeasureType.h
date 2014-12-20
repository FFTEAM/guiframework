#ifndef MEASURETYPE_H
#define MEASURETYPE_H

#include <QtGlobal>

class MeasureType
{
    MeasureType() = delete;
public:
    static const quint8 numOfTypes;
    static const char* typeName[];
};

#endif // MEASURETYPE_H
