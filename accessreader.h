#include "indicatorsmodel.h"

#ifndef ACCSESSREADER_H
#define ACCSESSREADER_H

class AccessReader
{
private:
    bool createConnection();

public:
    AccessReader();
    IndicatorsModel getData();

};

#endif // ACCESSREADER_H
