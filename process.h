#ifndef CPROCESS_H
#define CPROCESS_H

#include <iostream>
#include <string>
#include "record.h"

using namespace std;

class CProcess
{
public:
    CProcess();
    CRecord getRecord();
private:
    CRecord oRecord;
};

#endif // CPROCESS_H
