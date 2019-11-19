#ifndef CPROCESS_H
#define CPROCESS_H

#include "record.h"

class CProcess
{
public:
    CProcess();
    CRecord getRecord();
private:
    CRecord oRecord;
};

#endif // CPROCESS_H
