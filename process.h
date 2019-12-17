#ifndef CPROCESS_H
#define CPROCESS_H

#include <iostream>
#include <string>
#include "record.h"

using namespace std;

class CProcess
{
public:
    static CProcess *getInstance();
    CRecord* getCRecord();
private:
    static CProcess *instance;
    static CRecord *oRecord;
    vector<CRecord*> oRecords;

    CProcess();
    ~CProcess();
};

#endif
