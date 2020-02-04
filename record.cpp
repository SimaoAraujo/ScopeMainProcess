#include "record.h"

CRecord* CRecord::instance = nullptr;

CRecord* CRecord::getInstance()
{
    if(!instance)
        instance = new CRecord();
    return instance;
}

int CRecord::recordCount = 0;

CRecord::CRecord()
{

}

CRecord::~CRecord()
{

}

CImage* CRecord::getCImage()
{
    CImage* oImage = CImage::getInstance();
    return oImage;
}

CText* CRecord::getCText()
{
    CText* oText = CText::getInstance();
    return oText;
}

CAudio* CRecord::getCAudio()
{
    CAudio* oAudio = CAudio::getInstance();
    return oAudio;
}

void CRecord::create()
{
    string directory = "/etc/SCOPE/records/record";
    string createDirectory = "mkdir " + directory + to_string(recordCount);
    system(createDirectory.c_str());
}

int CRecord::getRecord()
{
    string sLastRecordCount;
    int iLastRecordCount;

    ifstream lastRecord_in("/etc/SCOPE/lastRecord.txt");
    if(lastRecord_in.is_open())
    {
        getline(lastRecord_in, sLastRecordCount);
        lastRecord_in.close();
        iLastRecordCount = stoi(sLastRecordCount);
        recordCount = iLastRecordCount;
        return recordCount;
    }
    else
    {
        cout << "Unable to open file";
    }
}

void CRecord::createRecord()
{
    string sLastRecordCount;
    int iLastRecordCount;

    recordCount = CRecord::getInstance()->getRecord();
    CRecord::getInstance()->create();
}
