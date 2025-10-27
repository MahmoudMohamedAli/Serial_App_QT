#ifndef COMMANDSTRUCTURE_H
#define COMMANDSTRUCTURE_H

#include "qtypes.h"
typedef struct CommandFormat
{
    qint8 Header;
    qint8 type;
    qint8 data;
    qint8 footer;
}CommandFormat_t;


#endif // COMMANDSTRUCTURE_H
