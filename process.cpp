#include "process.h"

CProcess* CProcess::instance = nullptr;

CProcess* CProcess::getInstance()
{
    if(!instance)
        instance = new CProcess();
    return instance;
}

CProcess::CProcess()
{

}

CProcess::~CProcess()
{

}

CRecord* CProcess::getCRecord()
{
    CRecord *oRecord = new CRecord();
    oRecords.push_back(oRecord);
    return oRecord;
}
