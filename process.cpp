#include "process.h"

CProcess* CProcess::instance = nullptr;

CProcess* CProcess::getInstance()
{
    if(!instance)
        instance = new CProcess();
    return instance;
}

CProcess::CProcess() /*oRecord()*/
{
    /* getCRecord(); */
}

CRecord* CProcess::getCRecord()
{
    CRecord* oRecord = new CRecord();
    return oRecord;
}
